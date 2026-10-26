#include <bsp.h>

volatile uint32_t msTicks;

void SysTick_Handler(void) {
    msTicks++;
}

uint32_t GetTick(void) {
    return msTicks;
}
