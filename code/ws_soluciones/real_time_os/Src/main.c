#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "bsp.h"

#include "stdio.h"

void Task1_LED(void *pvParameters) {
    for (;;) {
        // Toggle Board LED (e.g., User LED on PJ13)
        //GPIOJ->ODR ^= (1 << 13);
    	GPIO_PIN_TOGGLE(GPIOA, 5);
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay 500 ms
    }
}

void Task2_Worker(void *pvParameters) {
    for (;;) {
        // Do processing work here
    	GPIO_PIN_TOGGLE(GPIOA, 7);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void GPIO_Init(void) {
	// 1. Enable AHB1 peripheral clocks for GPIOA and GPIOB
	RCC_AHB1ENR->bits.GPIOAEN = 1;
	RCC_AHB1ENR->bits.GPIOBEN = 1;

	// 2. Configure PA7 (Red LED) and PA5 (Blue LED) and PB1 (Green LED) as General Purpose Outputs
	GPIO_CONFIG(GPIOA, 5, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_OSPEED_LOW, GPIO_PUPD_NONE, 0);
	GPIO_CONFIG(GPIOA, 7, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_OSPEED_LOW, GPIO_PUPD_NONE, 0);
	GPIO_CONFIG(GPIOB, 1, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_OSPEED_LOW, GPIO_PUPD_NONE, 0);
}


int main(void) {
    // 1. Initialize System Clock & Hardware Pins
	//SysTick_Init();
    GPIO_Init();

    //init_nvic_priority_grouping();

    // 2. Create FreeRTOS Tasks
    xTaskCreate(Task1_LED, "LED_Task", 128, NULL, 1, NULL);
    xTaskCreate(Task2_Worker, "Work_Task", 256, NULL, 2, NULL);

    // 3. Start Scheduler (never returns)
    vTaskStartScheduler();

    while (1); // Reached only if heap memory was insufficient
}



