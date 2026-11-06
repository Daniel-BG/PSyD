#ifndef ESP01S_H_
#define ESP01S_H_

#include <stdint.h>
#include <RingBuffer.h>
#include <bsp.h>

//Structure for UART handlers
typedef struct
{
	USART_TypeDef * UARTx;
	RingBuffer buffer;
	uint8_t initialized;
} ESP01S_TypeDef;

#define IDLE_TIMEOUT_MS 50
#define RESPONSE_BUF_SIZE 512

void ESP01S_UART_IRQHandler(ESP01S_TypeDef * esp01s);
uint8_t ESP01S_SendCommand(ESP01S_TypeDef * esp01s, const char *cmd, const char *expected_resp, uint32_t timeout_ms);
uint8_t ESP01S_Init(ESP01S_TypeDef * esp01s, USART_TypeDef * UARTx);
uint8_t ESP01S_ConnectWiFi(ESP01S_TypeDef * esp01s);
uint8_t ESP01S_WaitCONNACK(ESP01S_TypeDef * esp01s, uint32_t timeout_ms);
uint8_t ESP01S_WaitSUBACK(ESP01S_TypeDef * esp01s, uint32_t timeout_ms);
uint8_t ESP01S_StartMQTT(ESP01S_TypeDef * esp01s);
uint8_t ESP01S_SendTelemetry_MQTT(ESP01S_TypeDef * esp01s, float temp, uint32_t counter, uint16_t touch_x, uint16_t touch_y);
void ESP01S_ProcessMQTT(ESP01S_TypeDef * esp01s);

#endif /* ESP01S_H_ */
