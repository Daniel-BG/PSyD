/*
 * ESP01S.h
 *
 *  Created on: Aug 17, 2026
 *      Author: dani
 */

#ifndef ESP01S_H_
#define ESP01S_H_

/*********************** USER CONFIG *******************************/
#include <ESP01S_config.h>

//Where to place the app. It must be compiled to be loaded here, otherwise won't work
#define ADDR_FLASH_SECTOR_4 0x08010000          // Target Flash Sector (0x08040000)
#define FLASH_TARGET_SECTOR 4                   // Flash Sector 4



#define RX_BUFFER_SIZE      2048
uint8_t rx_buffer[RX_BUFFER_SIZE];

uint8_t ESP01S_SendCommand(const char *cmd, const char *expected_resp, uint32_t timeout_ms)
{
    // Drain/Flush any leftover garbage bytes from hardware register
    UART_FlushRX(UART5);

    memset(rx_buffer, 0, RX_BUFFER_SIZE);
    UART_WriteString(UART5, cmd);

    uint32_t start = GetTick();
    uint16_t idx = 0;

    while ((GetTick() - start) < timeout_ms) {
        uint8_t byte;
        if (UART_ReadDataRegisterNonBlocking(UART5, &byte)) {
            if (idx < RX_BUFFER_SIZE - 1) {
                rx_buffer[idx++] = byte;
                rx_buffer[idx] = '\0'; // Keep null-terminated
            }
            if (strstr((char *)rx_buffer, expected_resp) != NULL) {
                //Delay_ms(50); // Small settle delay
                return 1;
            }
        }
    }

    // On failure, print what the ESP actually sent back
    Debug_Printf("[ESP RAW RX]: %s\r\n", rx_buffer);
    return 0; // Timeout
}

uint8_t ESP01S_Init(void)
{
    Debug_Printf("[ESP] Testing AT Communication...\r\n");
    if (!ESP01S_SendCommand("AT\r\n", "OK\r\n", 2000)) return 0;

    Debug_Printf("[ESP] Disabling Command Echo...\r\n");
    if (!ESP01S_SendCommand("ATE0\r\n", "OK\r\n", 1000)) return 0;

    Debug_Printf("[ESP] Setting Station Mode...\r\n");
    if (!ESP01S_SendCommand("AT+CWMODE=1\r\n", "OK\r\n", 2000)) return 0;

    Debug_Printf("[ESP] Enabling Single Connection Mode (CIPMUX=0)...\r\n");
    return ESP01S_SendCommand("AT+CIPMUX=0\r\n", "OK\r\n", 2000);
}

uint8_t ESP01S_ConnectWiFi(void)
{
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "AT+CWJAP=\"%s\",\"%s\"\r\n", WIFI_SSID, WIFI_PASSWORD);

    Debug_Printf("[ESP] Connecting to SSID: %s...\r\n", WIFI_SSID);
    return ESP01S_SendCommand(cmd, "OK\r\n", 15000);
}

uint8_t ESP01S_DownloadAndFlash(void)
{
    char cmd[256];

    // 1. Establish TCP Connection
    snprintf(cmd, sizeof(cmd), "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", SERVER_IP, SERVER_PORT);
    Debug_Printf("[TCP] Connecting to %s:%d...\r\n", SERVER_IP, SERVER_PORT);
    if (!ESP01S_SendCommand(cmd, "OK\r\n", 10000)) return 0;

    // 2. Prepare HTTP GET Request
    char http_req[256];
    snprintf(http_req, sizeof(http_req), "GET /"FILE_PATH" HTTP/1.1\r\nHost: "SERVER_IP"\r\nUser-Agent: esp8266/stm32\r\nAccept: */*\r\nConnection: keep-alive\r\n\r\n");
    snprintf(cmd, sizeof(cmd), "AT+CIPSEND=%d\r\n", (int)strlen(http_req));
    Debug_Printf("[HTTP] Requesting Transfer...\r\n");
    if (!ESP01S_SendCommand(cmd, "OK\r\n>", 2000)) return 0;

    // 3. Send HTTP Request
    Debug_Printf("[HTTP] Requesting Payload...\r\n");
    if (!ESP01S_SendCommand(http_req, "SEND OK\r\n", 2000)) return 0;

    // 4. Stream HTTP Response Body Directly into Internal Flash
    uint32_t current_flash_addr = ADDR_FLASH_SECTOR_4;
    uint32_t bytes_written = 0;
    uint32_t last_byte_tick = GetTick();

    uint8_t initial_pattern[4] = {0};
    uint8_t init_skipped = 0;

    uint8_t chunk_pattern[5] = {0};
    uint8_t chunk_matched = 0;
    uint8_t chunk_matched_index = 0;
    uint8_t chunk_length_string[4];
    uint32_t chunk_length_value = 0;
    uint8_t last_chunk = 0;

    // Unlock once before streaming starts
	Flash_Unlock();
	Flash_ClearErrors();

    while ((GetTick() - last_byte_tick) < 15000) { // 15-second data timeout
        uint8_t byte;
        if (chunk_length_value == 0 && last_chunk)
        	break;

        if (UART_ReadDataRegisterNonBlocking(UART5, &byte)) {
        	//If reading a chunk's length
            if (chunk_matched) {
            	if (byte == ':') {
            		chunk_length_value = atoi((char *)chunk_length_string);
            		chunk_matched = 0;
            		if (chunk_length_value < 1460)
            			last_chunk = 1;
            	} else {
            		chunk_length_string[chunk_matched_index++] = byte;
            	}
            	continue;
            }

        	//If reading a chunk:
        	if (chunk_length_value > 0) {
        		chunk_length_value--;
        		if (!init_skipped) {
        			initial_pattern[0] = initial_pattern[1];
        			initial_pattern[1] = initial_pattern[2];
                	initial_pattern[2] = initial_pattern[3];
                	initial_pattern[3] = byte;

                    if (initial_pattern[0] == '\r' && initial_pattern[1] == '\n' && initial_pattern[2] == '\r' && initial_pattern[3] == '\n') {
                    	init_skipped = 1;
        			}
        			continue;
        		}

        		//write as data is received
        		Flash_WriteByteRaw(current_flash_addr++, byte);
        		bytes_written++;
				continue;
        	}

            // Look for chunk delimiter sequence "+IPD,"
        	chunk_pattern[0] = chunk_pattern[1];
        	chunk_pattern[1] = chunk_pattern[2];
        	chunk_pattern[2] = chunk_pattern[3];
        	chunk_pattern[3] = chunk_pattern[4];
        	chunk_pattern[4] = byte;

            if (chunk_pattern[0] == '+' && chunk_pattern[1] == 'I' && chunk_pattern[2] == 'P' && chunk_pattern[3] == 'D' && chunk_pattern[4] == ',') {
            	chunk_matched = 1;
            	chunk_matched_index = 0;
                memset(chunk_pattern, '\0', 5);
                memset(chunk_length_string, '\0', 4);
			}
        }
    }

    // Lock once when streaming ends
    Flash_Lock();

    Debug_Printf("[FLASH] Download Complete. Total Size: %lu bytes\r\n", bytes_written);


    return (bytes_written > 0);
}

#endif /* ESP01S_H_ */
