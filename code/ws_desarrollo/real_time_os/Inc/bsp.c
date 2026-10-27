#include "bsp.h"

volatile uint32_t msTicks = 0;

__attribute__((weak)) void SysTick_UserCallback(void) {
    // Default empty implementation
}

void SysTick_Handler(void) {
    msTicks++;
    SysTick_UserCallback();
}
