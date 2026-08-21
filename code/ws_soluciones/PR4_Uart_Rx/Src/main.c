

#include <stdint.h>
#include <bsp.h>

#define CLOCK_RATE 16000000
#define BAUD_RATE 115200
#define UART_BRR_SAMPLING16 ((CLOCK_RATE + BAUD_RATE/2) / BAUD_RATE)


#include <stdint.h>




int main(void)
{
	/* Enable GPIOE and set port 0 to 0 to light up LED0 */
	RCC_AHB1ENR->bits.GPIOAEN = 1;
	GPIO_MODE_SET(GPIOA, 7, GPIO_MODE_OUTPUT);
	GPIO_OTYPE_SET(GPIOA, 7, GPIO_OTYPE_PP);
	GPIO_OSPEED_SET(GPIOA, 7, GPIO_OSPEED_HIGH);
	GPIO_PUPD_SET(GPIOA, 7, GPIO_PUPD_NONE);
	GPIO_PIN_WRITE(GPIOA, 7, GPIO_STATE_ZERO);

	/* Enable GPIOC for UART RX pin (Table 10 of DS11853)*/
	RCC_AHB1ENR->bits.GPIOCEN = 1;
	GPIO_MODE_SET(GPIOC, 6, GPIO_MODE_ALT);
	GPIO_OTYPE_SET(GPIOC, 6, GPIO_OTYPE_PP);
	GPIO_PUPD_SET(GPIOC, 6, GPIO_PUPD_PU);
	GPIO_OSPEED_SET(GPIOC, 6, GPIO_OSPEED_HIGH);
	GPIO_AF_SET(GPIOC, 6, GPIO_AF8_USART6);
	/* Enable GPIOA for UART TX pin */
	RCC_AHB1ENR->bits.GPIOCEN = 1;
	GPIO_MODE_SET(GPIOC, 7, GPIO_MODE_ALT);
	GPIO_OTYPE_SET(GPIOC, 7, GPIO_OTYPE_PP);
	GPIO_PUPD_SET(GPIOC, 7, GPIO_PUPD_PU);
	GPIO_OSPEED_SET(GPIOC, 7, GPIO_OSPEED_HIGH);
	GPIO_AF_SET(GPIOC, 7, GPIO_AF8_USART6);

	/* Enable push button as input (GPIOA0)*/
	RCC_AHB1ENR->bits.GPIOAEN = 1;
	GPIO_MODE_SET(GPIOA, 0, GPIO_MODE_INPUT);
	GPIO_OTYPE_SET(GPIOA, 0, GPIO_OTYPE_PP);
	GPIO_OSPEED_SET(GPIOA, 0, GPIO_OSPEED_HIGH);
	GPIO_PUPD_SET(GPIOA, 0, GPIO_PUPD_PD);

	//Configure UART6
	RCC_APB2ENR->bits.USART6EN = 1; 		//enable UART clock
	UART_ENABLE_SET(USART6, UART_ENABLE);	//enable UART peripheral
	UART_WORDLENGTH_SET(USART6, UART_WORD_8B);	//set word length (8 bit)
	UART_STOPBIT_SET(USART6, UART_STOP_ONEBIT);	//set stop bits (1 bit)
	UART_PARITY_SET(USART6, UART_PARITY_NONE);	//set parity (enabled - odd)
	UART_OVERSAMPLING_SET(USART6, UART_OVERSAMPLING_16);	//set oversampling to 16
	UART_BRR_SET(USART6, UART_BRR_SAMPLING16);						//set BRR (Baud rate register) to CLK/BAUD
	UART_TX_MODE_SET(USART6, UART_TX_ENABLE);	//enable transmission

	//Configure UART for reception and interrupt enable (30.3.3)
	//rest of UART already configured (common for tx and rx)
	UART_RX_MODE_SET(USART6, UART_RX_ENABLE);
	UART_RX_INT_SET(USART6, UART_RX_INT_ENABLE);

	//Activate SYSCFG peripheral to be able to enable interrupt lines
	RCC_APB2ENR->bits.SYSCFGEN = 1;
	//Activate, for EINT0, the line corresponding to PORT A
	SYSCFG_EINT_MAP_PORT(0, 0); //port a (0) to eint0
	EXTI_ENABLE_RISING_TRIGGER(0, 1); 	//enable on port a
	EXTI_UNMASK_INTERRUPT(0, 1);		//unmask on port a

	//Enable interrupts
	NVIC_ENABLE_INT(EXTI0_LINE_IRQn);
	NVIC_ENABLE_INT(USART6_INT_IRQn);


	/* Loop forever */
	for(;;) {
		//SEND DATA
		UART_TransmitByte(USART6, 'X');
		UART_TransmitByte(USART6, 'Y');
		UART_TransmitByte(USART6, 'Z');
		GPIO_PIN_WRITE(GPIOA, 7, GPIO_STATE_ONE);
		delay(1000000);
		GPIO_PIN_WRITE(GPIOA, 7, GPIO_STATE_ZERO);
		delay(1000000);
	}
}


void USART6_IRQHandler(void)
{
    // Check if the RXNE (Receive Data Register Not Empty) interrupt flag is set
    // For STM32F412, status flags are in the SR register (bit 5 is RXNE)
    if (UART_STATUS_RXNE(USART6)) {
        // Reading the DR (Data Register) automatically clears the RXNE flag in hardware
        uint8_t received_byte = UART_ReadDataRegister(USART6);
        UART_TransmitByte(USART6, received_byte);
    //a framing error or overrun error also trigger interrupts. Clear them to avoid infinite loops
    } else if (UART_STATUS_PE(USART6) | UART_STATUS_ORE(USART6)) {
    	volatile uint32_t dummy = UART_ReadDataRegister(USART6); //interrupts are cleared by reading the DR register
		(void)dummy; // Prevent compiler "unused variable" warning
	}
}


void EXTI0_IRQHandler(void)
{
    // Check if position 0 triggered the interrupt
    if (EXTI->PR & (1U)) {
        // 1. Clear the pending flag for line 0 by writing a 1 to it
        EXTI->PR = (1U);
        GPIO_PIN_TOGGLE(GPIOA, 7);
    }
}
