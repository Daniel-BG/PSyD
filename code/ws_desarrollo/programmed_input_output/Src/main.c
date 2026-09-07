

#include <stdint.h>
#include <bsp.h>

#define CLOCK_RATE 16000000
#define BAUD_RATE 115200
#define UART_BRR_SAMPLING16 ((CLOCK_RATE + BAUD_RATE/2) / BAUD_RATE)



int main(void)
{
	/* Enable GPIOE and set port 0 to 0 to light up LED0 */
	RCC_AHB1ENR->bits.GPIOAEN = 1;
	GPIO_MODE_SET(GPIOA, 7, GPIO_MODE_OUTPUT);
	GPIO_OTYPE_SET(GPIOA, 7, GPIO_OTYPE_PP);
	GPIO_OSPEED_SET(GPIOA, 7, GPIO_OSPEED_HIGH);
	GPIO_PUPD_SET(GPIOA, 7, GPIO_PUPD_NONE);
	GPIO_PIN_WRITE(GPIOA, 7, GPIO_STATE_ZERO);

	/* Enable GPIOC for UART TX pin (Table 10 of DS11853)*/
	RCC_AHB1ENR->bits.GPIOCEN = 1;
	GPIO_MODE_SET(GPIOC, 6, GPIO_MODE_ALT);
	// ... completar

	//Configure UART6
	// ... completar enable UART clock
	// ... completar configure UART

	/* Loop forever */
	for(;;) {
		//SEND DATA
		UART_TransmitByte(USART6, 'A');
		UART_TransmitByte(USART6, 'B');
		UART_TransmitByte(USART6, 'C');
		GPIO_PIN_WRITE(GPIOA, 7, GPIO_STATE_ONE);
		delay(1000000);
		GPIO_PIN_WRITE(GPIOA, 7, GPIO_STATE_ZERO);
		delay(1000000);
		Debug_Printf("XYZ");
	}
}

