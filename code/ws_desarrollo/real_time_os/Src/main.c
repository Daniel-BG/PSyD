#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "bsp.h"
#include "stdio.h"

void Task1(void *pvParameters) {
    for (;;) {
        //... completar hacer toggle a un LED (por ejemplo PA5)
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay 500 ms
    }
}


void GPIO_Init(void) {
    //... completar inicializar los GPIOs que se vayan a utilizar
}

int main(void) {
    // 1. Initialize peripherals
    GPIO_Init();


    // 2. Create FreeRTOS Tasks
    xTaskCreate(Task1, "LED_Task1", 128, NULL, 1, NULL);
    //... completar crear más tareas que enciendan por ejemplo otros leds

    // 3. Start Scheduler (never returns)
    vTaskStartScheduler();

    while (1); // aquí no debería llegar nunca
}