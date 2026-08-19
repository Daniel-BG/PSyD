/**
  ******************************************************************************
  * @file    main.c
  * @brief   Bare-Metal Minimal ESP-01S IAP Client
  *          Target: STM32F723E-Discovery
  ******************************************************************************
  */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <bsp.h>
#include <ESP01S.h>


void Peripherals_Init(void) {
    // Enable USARTs and their GPIOs
	RCC_AHB1ENR->bits.GPIOCEN = 1;
	RCC_AHB1ENR->bits.GPIODEN = 1;
	RCC_APB1ENR->bits.USART5EN = 1;	// comm with espressif
	RCC_APB2ENR->bits.USART6EN = 1; // comm with computer (stlink)

    /* --- USART6 Pin Configuration (ST-LINK VCP: PC6=TX, PC7=RX) --- */
	GPIO_CONFIG(GPIOC, 6, GPIO_MODE_ALT, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PUPD_PU, GPIO_AF8_USART6);
	GPIO_CONFIG(GPIOC, 7, GPIO_MODE_ALT, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PUPD_PU, GPIO_AF8_USART6);

    /* --- UART5 Pin Configuration (ESP8266: PC12=TX, PD2=RX) --- */
	GPIO_CONFIG(GPIOC, 12, GPIO_MODE_ALT, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PUPD_PU, GPIO_AF8_USART5);
	GPIO_CONFIG(GPIOD,  2, GPIO_MODE_ALT, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PUPD_PU, GPIO_AF8_USART5);

    /* --- Baud Rate Setup ---
     * Default HSI Clock = 16 MHz. Target Baud Rate = 115200.
     * USARTDIV = 16,000,000 / 115200 = 138.88 => BRR = 139 (0x8B)
     */
	UART_BRR_SET(USART6, 139);
	UART_BRR_SET(UART5, 139);
	// enable UARTS + TX + RX
	UART_ENABLE_SET(USART6, 1);
	UART_TX_MODE_SET(USART6, 1);
	UART_RX_MODE_SET(USART6, 1);
	UART_ENABLE_SET(UART5, 1);
	UART_TX_MODE_SET(UART5, 1);
	UART_RX_MODE_SET(UART5, 1);
}

void UserButton_Init(void) {
	RCC_AHB1ENR->bits.GPIOAEN = 1;
	GPIO_CONFIG(GPIOA, 0, GPIO_MODE_INPUT, GPIO_OTYPE_PP, GPIO_OSPEED_LOW, GPIO_PUPD_PD, 0);
}

void JumpToApplication(uint32_t address) {
    // Disable any active interrupts (only SysTick in our case)
    SysTick_Disable();

    // Disable the peripherals we were using
    RCC_AHB1ENR->bits.GPIOAEN = 1;
	RCC_AHB1ENR->bits.GPIOCEN = 1;
	RCC_AHB1ENR->bits.GPIODEN = 1;
	RCC_APB1ENR->bits.USART5EN = 1;	// comm with espressif
	RCC_APB2ENR->bits.USART6EN = 1; // comm with computer (stlink)

    // Relocate Vector Table
    SCB->VTOR = address;

    // Set Main Stack Pointer (MSP)
    __asm volatile ("msr msp, %0" : : "r" (*(volatile uint32_t *)address) : );

    // Branch to reset handler of target firmware
    typedef void (*pFunction)(void);
    uint32_t JumpAddress = *(volatile uint32_t *)(address + 4);
    pFunction JumpToApp = (pFunction)JumpAddress;
    JumpToApp();
}

//Check for app presence at a given location
uint8_t IsApplicationValid(uint32_t address) {
    uint32_t sp = *(volatile uint32_t *)address;

    // Check if initial Stack Pointer points into valid SRAM range (0x20000000)
    if ((sp & 0x2FF00000) == 0x20000000) {
        return 1;
    }
    return 0;
}



int main(void) {
    // Initialize bare-metal timers and UART peripherals
    SysTick_Init();
    Peripherals_Init();
    UserButton_Init();

    Debug_Printf("\r\n=========================================\r\n");
    Debug_Printf("  STM32F7 Bare-Metal ESP8266 IAP Boot   \r\n");
    Debug_Printf("=========================================\r\n");


    uint8_t app_valid = IsApplicationValid(ADDR_FLASH_SECTOR_4);
    uint8_t button_pressed = GPIO_PIN_READ(GPIOA, 0);
    // Boot decision
	if (button_pressed) {
		Debug_Printf("[BOOT] User button pressed! Overriding automatic boot ...\r\n");
		Debug_Printf("[BOOT] Keep pressing for flash erase...\r\n");
		Delay_ms(2000);
		uint8_t button_pressed = GPIO_PIN_READ(GPIOA, 0);
		if (button_pressed) {
			Debug_Printf("[BOOT] Erasing flash\r\n");
		    // Erase Flash sector 4
		    Debug_Printf("[FLASH] Erasing Sector %d...\r\n", FLASH_TARGET_SECTOR);
		    Flash_EraseSector(FLASH_TARGET_SECTOR);
		    Debug_Printf("[FLASH] Sector Erased.\r\n");
		    while(1);
		} else {
			Debug_Printf("[BOOT] Entering Download Mode\r\n");
		}
	} else {
		if (app_valid) {
			Debug_Printf("[BOOT] Valid application found at 0x%08X....\r\n", ADDR_FLASH_SECTOR_4);
			Debug_Printf("[BOOT] Starting...\r\n");
			JumpToApplication(ADDR_FLASH_SECTOR_4);
		}
		Debug_Printf("[BOOT] No valid application at 0x%08X. Entering Download Mode...\r\n", ADDR_FLASH_SECTOR_4);
	}

    // Initialize ESP8266
    if (!ESP01S_Init()) {
        Debug_Printf("[ERROR] ESP8266 Init failed!\r\n");
        while (1);
    }

    // Connect Wi-Fi
    if (!ESP01S_ConnectWiFi()) {
        Debug_Printf("[ERROR] Wi-Fi Connection failed!\r\n");
        while (1);
    }

    // We must erase before flashing new stuff, since bits only
    // change from 1 to 0 and not vice versa when flashing.
    // This ensures initial state is 0xffffffff
    Debug_Printf("[FLASH] Erasing Sector %d...\r\n", FLASH_TARGET_SECTOR);
    Flash_EraseSector(FLASH_TARGET_SECTOR);
    Debug_Printf("[FLASH] Sector Erased.\r\n");

    // Download over TCP and Flash directly
    if (ESP01S_DownloadAndFlash()) {
        Debug_Printf("[SUCCESS] Booting Application at 0x%08X...\r\n", ADDR_FLASH_SECTOR_4);
        Delay_ms(500);
        JumpToApplication(ADDR_FLASH_SECTOR_4);
    } else {
        Debug_Printf("[ERROR] Firmware Update Failed!\r\n");
    }

    while (1) {
        // Halt loop
    }
}
