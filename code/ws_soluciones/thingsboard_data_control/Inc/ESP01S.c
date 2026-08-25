#include "ESP01S.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <bsp.h>

/*********************** PAHO MQTT INCLUDES *******************************/
#include "MQTTPacket.h"

/*********************** USER CONFIG *******************************/
#include <ESP01S_config.h>
#include "RingBuffer.h"

void ESP01S_UART_IRQHandler(ESP01S_TypeDef * esp01s) {
    uint8_t byte;
    if (esp01s->initialized && UART_ReadDataRegisterNonBlocking(esp01s->UARTx, &byte)) {
        RingBuffer_Put(&esp01s->buffer, byte);
    }
}

/*********************** AT COMMAND INTERFACE *******************************/

/*
 * Send a command to the ESP-01S over the UART interface
 * the time to receive the information back after the command
 * is sent is given by timeout_ms. If a response starts, a second
 * timer is started given by the IDLE_TIMEOUT timing. If the channel
 * stays silent for that amount of time, the response is assumed
 * complete, otherwise new bytes are waited for.
 */
uint8_t ESP01S_SendCommand(ESP01S_TypeDef * esp01s, const char *cmd, const char *expected_resp, uint32_t timeout_ms) {
	//flush bytes remaining in the buffer
    RingBuffer_Flush(&esp01s->buffer);

    if (cmd != NULL && strlen(cmd) > 0) {
        UART_WriteString(esp01s->UARTx, cmd);
    }

    char response_buf[RESPONSE_BUF_SIZE];
    memset(response_buf, 0, RESPONSE_BUF_SIZE);
    uint16_t idx = 0;

    uint32_t start_tick = GetTick();
    uint32_t last_byte_tick = GetTick();
    uint8_t match_found = 0;

    while ((GetTick() - start_tick) < timeout_ms) {
        uint8_t byte;
        if (RingBuffer_Read(&esp01s->buffer, &byte)) {
            last_byte_tick = GetTick();
            if (idx < RESPONSE_BUF_SIZE - 1) {
                response_buf[idx++] = byte;
                response_buf[idx] = '\0';
            }
        }
        else {
            if (!match_found && strstr((char *)response_buf, expected_resp) != NULL) {
                match_found = 1;
            }
            if (match_found && ((GetTick() - last_byte_tick) >= IDLE_TIMEOUT_MS)) {
                break;
            }
        }
    }

    if (match_found) return 1;

    //Debug_Printf("[ESP FAIL] Sent: %s | RX: %s\r\n", cmd ? cmd : "", response_buf);
    return 0;
}

/*
 * Initialize the ESP01S module.
 * If it does not work (normally because it is stuck on a previous
 * connection since a board reset does not reset the module) then
 * reset it via software
 */
uint8_t ESP01S_Init(ESP01S_TypeDef * esp01s, USART_TypeDef * UARTx) {
	esp01s->UARTx = UARTx;
	RingBuffer_Flush(&esp01s->buffer);
	esp01s->initialized = 1;

    Debug_Printf("[ESP] Testing ESP01S AT Communication...\r\n");

    // First check to see if it receives commands
    if (!ESP01S_SendCommand(esp01s, "AT\r\n", "OK\r\n", 500)) {
        Debug_Printf("[ESP] No AT response (MCU reset in passthrough?). Attempting '+++' escape...\r\n");

        Delay_ms(1000);
        UART_WriteString(esp01s->UARTx, "+++"); //special command to take it out
        Delay_ms(1000);

        Debug_Printf("[ESP] Terminating leftover connection...\r\n");
        if (!ESP01S_SendCommand(esp01s, "AT\r\n", "OK\r\n", 1000) || !ESP01S_SendCommand(esp01s, "AT+CIPCLOSE\r\n", "OK\r\n", 1000) || ! ESP01S_SendCommand(esp01s, "AT+CIPMODE=0\r\n", "OK\r\n", 1000)) {
        	Debug_Printf("[ESP] Failed to restart...\r\n");
        	return 0;
        }
        Debug_Printf("[ESP] Restart succesful...\r\n");
    }

    // Second check to see if it works
    if (!ESP01S_SendCommand(esp01s, "AT\r\n", "OK\r\n", 1000)) {
        Debug_Printf("[ESP] Soft resetting module (AT+RST)...\r\n");
        ESP01S_SendCommand(esp01s, "AT+RST\r\n", "ready\r\n", 3000);
        Delay_ms(500);
    }

    // Third check after two failed attemps, give up
    if (!ESP01S_SendCommand(esp01s, "AT\r\n", "OK\r\n", 2000)) {
        Debug_Printf("[ESP ERROR] Hardware communication failure!\r\n");
        return 0;
    }


    // Start the real config
    Debug_Printf("[ESP] Disabling Echo...\r\n");
    ESP01S_SendCommand(esp01s, "ATE0\r\n", "OK\r\n", 1000);

    Debug_Printf("[ESP] Setting Station Mode...\r\n");
    ESP01S_SendCommand(esp01s, "AT+CWMODE=1\r\n", "OK\r\n", 2000);

    Debug_Printf("[ESP] Disabling MUX (Single Conn Mode)...\r\n");
    ESP01S_SendCommand(esp01s, "AT+CIPMUX=0\r\n", "OK\r\n", 2000);

    Debug_Printf("[ESP] Enabling Transparent Passthrough Mode...\r\n");
    return ESP01S_SendCommand(esp01s, "AT+CIPMODE=1\r\n", "OK\r\n", 2000);
}

// simple command send to connect to the given SSID and PASSWORD
uint8_t ESP01S_ConnectWiFi(ESP01S_TypeDef * esp01s) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "AT+CWJAP=\"%s\",\"%s\"\r\n", WIFI_SSID, WIFI_PASSWORD);
    Debug_Printf("[ESP] Connecting to SSID: %s...\r\n", WIFI_SSID);
    return ESP01S_SendCommand(esp01s, cmd, "OK\r\n", 15000);
}

/*
 * Wait for the specific MQTT response with the connection
 * ACKknowledged code
 */
uint8_t ESP01S_WaitCONNACK(ESP01S_TypeDef * esp01s, uint32_t timeout_ms) {
    uint32_t start = GetTick();
    uint8_t packet[32];
    uint16_t idx = 0;
    uint8_t byte;

    while ((GetTick() - start) < timeout_ms) {
        if (RingBuffer_Read(&esp01s->buffer, &byte)) {
            packet[idx++] = byte;
            if (idx >= 4) {
                unsigned char sessionPresent, connack_rc;
                if (MQTTDeserialize_connack(&sessionPresent, &connack_rc, packet, idx) == 1) {
                    if (connack_rc == 0) {
                        Debug_Printf("[MQTT RX] CONNACK 0x00: Connection Accepted!\r\n");
                        return 1;
                    } else {
                        Debug_Printf("[MQTT ERROR] CONNACK Rejected Code: 0x%02X\r\n", connack_rc);
                        return 0;
                    }
                }
            }
        }
    }
    Debug_Printf("[MQTT ERROR] CONNACK Timeout!\r\n");
    return 0;
}

uint8_t ESP01S_WaitSUBACK(ESP01S_TypeDef * esp01s, uint32_t timeout_ms) {
    uint32_t start = GetTick();
    uint8_t packet[32];
    uint16_t idx = 0;
    uint8_t byte;

    while ((GetTick() - start) < timeout_ms) {
        if (RingBuffer_Read(&esp01s->buffer, &byte)) {
            if (idx < sizeof(packet)) {
                packet[idx++] = byte;
            }
            if (idx >= 5) {
                unsigned short suback_id = 0;
                int maxcount = 1;        // Max items allowed in array
                int subcount = 0;        // Returned count of QoS items
                int grantedQoSs[1] = {0}; // Output array for QoS responses

                if (MQTTDeserialize_suback(&suback_id, maxcount, &subcount, grantedQoSs, packet, idx) == 1) {
                    Debug_Printf("[MQTT RX] SUBACK Received! Granted QoS: %d\r\n", grantedQoSs[0]);
                    return 1;
                }
            }
        }
    }
    Debug_Printf("[MQTT ERROR] SUBACK Timeout\r\n");
    return 0;
}

/*
 * Since we are implementing our own MQTT stack (since the ESP01S may have older
 * firmware with no support) we put the radio in passthrough mode to be in control
 * as a UART RX/TX modem.
 * After that, just send the MQTT packets over the open TCP MQTT connection.
 */
uint8_t ESP01S_StartMQTT(ESP01S_TypeDef * esp01s) {
    char cmd[256];
    uint8_t buf[256];

    //connect and enable passthrough mode
    Debug_Printf("[MQTT] Connecting to %s:1883...\r\n", TB_HOST);
    snprintf(cmd, sizeof(cmd), "AT+CIPSTART=\"TCP\",\"%s\",1883\r\n", TB_HOST);
    if (!ESP01S_SendCommand(esp01s, cmd, "OK\r\n", 5000)) return 0;

    Debug_Printf("[MQTT] Entering passthrough streaming...\r\n");
    if (!ESP01S_SendCommand(esp01s, "AT+CIPSEND\r\n", ">", 2000)) return 0;

    MQTTPacket_connectData options = MQTTPacket_connectData_initializer;
    options.MQTTVersion = 4;
    options.clientID.cstring = "STM32F7_Client";
    options.username.cstring = TB_ACCESS_TOKEN;
    options.keepAliveInterval = 60;

    int len = MQTTSerialize_connect(buf, sizeof(buf), &options);
    UART_WriteBytes(esp01s->UARTx, buf, len);

    if (!ESP01S_WaitCONNACK(esp01s, 3000)) return 0;

    // 1. Subscribe to Attributes AND Firmware Response topics
	MQTTString topicFilters[1];
	topicFilters[0].cstring = "v1/devices/me/attributes";
	int req_qos[1] = {0};

	len = MQTTSerialize_subscribe(buf, sizeof(buf), 0, 1, 1, topicFilters, req_qos);
	UART_WriteBytes(esp01s->UARTx, buf, len);
	ESP01S_WaitSUBACK(esp01s, 3000);

    Debug_Printf("[MQTT] Connected & Subscribed successfully!\r\n");
    return 1;
}

/*
 * Generic publish telemetry over MQTT
 */
uint8_t ESP01S_SendTelemetry_MQTT(ESP01S_TypeDef * esp01s, float temp, uint32_t counter, uint16_t touch_x, uint16_t touch_y) {
    uint8_t buf[256];
    char payload[256];

    int temp_int = (int)temp;
    int temp_frac = (int)(abs((int)(temp * 100.0f)) % 100);

    snprintf(payload, sizeof(payload),
             "{\"temp\":%d.%02d,\"counter\":%lu,\"touch_x\":%u,\"touch_y\":%u}",
             temp_int, temp_frac, (unsigned long)counter, touch_x, touch_y);

    MQTTString topicString = MQTTString_initializer;
    topicString.cstring = "v1/devices/me/telemetry";

    int len = MQTTSerialize_publish(buf, sizeof(buf), 0, 0, 0, 0,
                                    topicString, (unsigned char *)payload, strlen(payload));

    UART_WriteBytes(esp01s->UARTx, buf, len);
    Debug_Printf("[MQTT TX] %s\r\n", payload);
    return 1;
}

/*
 * MQTT reception process.
 * Since we receive bytes asyncrhonously, we make sure that
 * 1) We are receiving a correct MQTT header
 * 2) We have received the full MQTT packet before processing
 * 3) If errors occur, we restart the packet parsing
 */
void ESP01S_ProcessMQTT(ESP01S_TypeDef * esp01s) {
	uint8_t packet[1024];
	//make sure we got stuff, otherwise don't bother
    if (!RingBuffer_Count(&esp01s->buffer)) return;

    uint8_t header;
    RingBuffer_Peek(&esp01s->buffer, 0, &header);

    // Filter non-PUBLISH frames (discard random UART noise)
    if ((header & 0xF0) != 0x30) {
        RingBuffer_Discard(&esp01s->buffer, 1);
        return;
    }

    // Here we start decoding MQTT.
    // Peek ahead to extract remaining length header bytes
	uint8_t len_bytes[4];
	for (uint8_t i = 0; i < 4; i++) {
		if (!RingBuffer_Peek(&esp01s->buffer, 1 + i, &len_bytes[i])) return;
	}

	// Paho decodes the variable-length remaining size integer
	int remaining_len = 0;
	int len_bytes_consumed = MQTTPacket_decodeBuf(len_bytes, &remaining_len);
	if (len_bytes_consumed <= 0) {
		RingBuffer_Discard(&esp01s->buffer, 1); // Drop invalid byte to resync
		return;
	}

	uint16_t total_packet_len = 1 + len_bytes_consumed + remaining_len;

	// Check if full frame is ready in buffer
	if (RingBuffer_Count(&esp01s->buffer) < total_packet_len) return;



    // Now we got the full package. Decode It using the library
    // Read exact payload frame out of ring buffer

    uint16_t copy_len = (total_packet_len < sizeof(packet)) ? total_packet_len : sizeof(packet);
    for (uint16_t i = 0; i < copy_len; i++) {
        RingBuffer_Read(&esp01s->buffer, &packet[i]);
    }

    // Flush any overflow bytes if payload exceeded local parsing array
    if (total_packet_len > copy_len) {
        RingBuffer_Discard(&esp01s->buffer, total_packet_len - copy_len);
    }

    // Paho Deserializer
    unsigned char dup, retained;
	int qos, payloadlen;
	unsigned char* payload;
	MQTTString receivedTopic;

	if (MQTTDeserialize_publish(&dup, &qos, &retained, NULL, &receivedTopic,
								 &payload, &payloadlen, packet, copy_len) == 1)
	{
		Debug_Printf("[MQTT RX] %s\r\n", receivedTopic.lenstring.data);

		char json_str[128] = {0};
		uint16_t str_len = (payloadlen < sizeof(json_str) - 1) ? payloadlen : sizeof(json_str) - 1;
		memcpy(json_str, payload, str_len);

		// LED command processing
		if (strstr(json_str, "\"ledState\":true"))        GPIO_PIN_WRITE(GPIOA, 7, GPIO_STATE_ONE);
		else if (strstr(json_str, "\"ledState\":false"))   GPIO_PIN_WRITE(GPIOA, 7, GPIO_STATE_ZERO);

	}
}
