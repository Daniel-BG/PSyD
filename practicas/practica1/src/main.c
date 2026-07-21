#include <stdint.h>

#define GPIOA_BASE_ADDR 0x40020000
#define RCC_AHB1ENR 0x40023830

void delay(int loops) {
    for (int i = 0; i < loops; i++) {
        __asm("nop");
    }
}

int main(void)
{
    //activate clock for GPIOA to work
    * ((uint32_t *) RCC_AHB1ENR) |= 0x01; 	//set bit 0 to 1 to enable clock on GPIOA

    * ((uint32_t *) (GPIOA_BASE_ADDR + 0x00)) &= ~(0b11 << 14); //clear
    * ((uint32_t *) (GPIOA_BASE_ADDR + 0x00)) |=   0b01 << 14; 	//output
    * ((uint32_t *) (GPIOA_BASE_ADDR + 0x04)) &= ~(0b0 << 7);	//clear
    * ((uint32_t *) (GPIOA_BASE_ADDR + 0x04)) |=   0b0 << 7;	//push-pull
    * ((uint32_t *) (GPIOA_BASE_ADDR + 0x08)) &= ~(0b10 << 14);	//clear
    * ((uint32_t *) (GPIOA_BASE_ADDR + 0x08)) |=   0b10 << 14;	//high speed
    * ((uint32_t *) (GPIOA_BASE_ADDR + 0x0C)) &= ~(0b00 << 14);	//clear
    * ((uint32_t *) (GPIOA_BASE_ADDR + 0x0C)) |=   0b00 << 14;	//disable pullup and down

    /* Loop forever */
    for(;;) {
        * ((uint32_t *) (GPIOA_BASE_ADDR + 0x14)) |=   0b1 << 7;	//turn on
        delay(1000000);
        * ((uint32_t *) (GPIOA_BASE_ADDR + 0x14)) &= ~(0b1 << 7);	//turn off
        delay(1000000);
    }
}