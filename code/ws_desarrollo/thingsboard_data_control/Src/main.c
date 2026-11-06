#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <bsp.h>
#include <ESP01S.h>



void Peripherals_Init(void) {
    RCC_AHB1ENR->bits.GPIOAEN = 1;
    RCC_AHB1ENR->bits.GPIOCEN = 1;
    RCC_AHB1ENR->bits.GPIODEN = 1;
    RCC_APB1ENR->bits.USART5EN = 1;
    RCC_APB2ENR->bits.USART6EN = 1;

    GPIO_CONFIG(GPIOC, 6, GPIO_MODE_ALT, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PUPD_PU, GPIO_AF8_USART6);
    GPIO_CONFIG(GPIOC, 7, GPIO_MODE_ALT, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PUPD_PU, GPIO_AF8_USART6);

    GPIO_CONFIG(GPIOC, 12, GPIO_MODE_ALT, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PUPD_PU, GPIO_AF8_USART5);
    GPIO_CONFIG(GPIOD,  2, GPIO_MODE_ALT, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PUPD_PU, GPIO_AF8_USART5);

    GPIO_CONFIG(GPIOA, 7, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_OSPEED_LOW, GPIO_PUPD_NONE, 0);

    UART_BRR_SET(USART6, 139);
    UART_BRR_SET(UART5, 139);

    UART_ENABLE_SET(USART6, 1);
    UART_TX_MODE_SET(USART6, 1);
    UART_RX_MODE_SET(USART6, 1);
    UART_ENABLE_SET(UART5, 1);
    UART_TX_MODE_SET(UART5, 1);
    UART_RX_MODE_SET(UART5, 1);

    UART_RX_INT_SET(UART5, UART_RX_INT_ENABLE);
    NVIC_ENABLE_INT(USART5_INT_IRQn);
}

ESP01S_TypeDef esp01s = {0};
void UART5_IRQHandler(void) {
	uint8_t byte;
	if (!esp01s.initialized)
		UART_ReadDataRegisterNonBlocking(UART5, &byte);

    ESP01S_UART_IRQHandler(&esp01s);
}


void System_Init(void) {
    // Enable Hardware FPU
    FPU->CPACR |= ((3UL << 10*2) | (3UL << 11*2));
}


int main(void) {
	System_Init();
    SysTick_Init();
    Peripherals_Init();

    float synth_temp = 20.0f;
    uint32_t synth_counter = 0;
    uint16_t synth_touch_x = 0;
    uint16_t synth_touch_y = 0;
    uint32_t last_telemetry_tick = 0;

    if (!ESP01S_Init(&esp01s, UART5) || !ESP01S_ConnectWiFi(&esp01s) || !ESP01S_StartMQTT(&esp01s)) {
        Debug_Printf("[SYSTEM ERROR] MQTT Passthrough setup failed!\r\n");
        while (1);
    }

    Debug_Printf("[SYSTEM] Ready! Streaming over MQTT...\r\n");

    while (1)
    {
        // 1. Instantly process incoming MQTT attribute packets from server
        ESP01S_ProcessMQTT(&esp01s);

        // 2. Send Telemetry every 3 seconds over active MQTT socket
        if ((GetTick() - last_telemetry_tick) >= 3000)
        {
            synth_temp += 0.5f;
            if (synth_temp > 40.0f) synth_temp = 20.0f;
            synth_counter++;
            synth_touch_x = (synth_touch_x + 15) % 240;
            synth_touch_y = (synth_touch_y + 20) % 240;

            ESP01S_SendTelemetry_MQTT(&esp01s, synth_temp, synth_counter, synth_touch_x, synth_touch_y);

            last_telemetry_tick = GetTick();
        }
    }
}
