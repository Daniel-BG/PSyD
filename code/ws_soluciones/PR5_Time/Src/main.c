

#include <stdint.h>
#include <bsp.h>

#define CLOCK_RATE 16000000
#define BAUD_RATE 115200
#define UART_BRR_SAMPLING16 ((CLOCK_RATE + BAUD_RATE/2) / BAUD_RATE)


#include <stdint.h>


int main(void)
{
	/* Enable GPIOA port 7 (red led) */
	RCC_AHB1ENR->bits.GPIOAEN = 1;
	GPIO_CONFIG(GPIOA, 7, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PUPD_NONE, 0);
	/* Enable GPIOB port 1 (green led) */
	RCC_AHB1ENR->bits.GPIOBEN = 1;
	GPIO_CONFIG(GPIOB, 1, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PUPD_NONE, 0);
	/* Enable GPIOC for UART RX and TX pins (Table 10 of DS11853)*/
	RCC_AHB1ENR->bits.GPIOCEN = 1;
	GPIO_CONFIG(GPIOC, 6, GPIO_MODE_ALT, GPIO_OTYPE_PP, GPIO_PUPD_PU, GPIO_OSPEED_HIGH, GPIO_AF8_USART6);
	GPIO_CONFIG(GPIOC, 7, GPIO_MODE_ALT, GPIO_OTYPE_PP, GPIO_PUPD_PU, GPIO_OSPEED_HIGH, GPIO_AF8_USART6);

	/* Enable push button as input (GPIOA0)*/
	RCC_AHB1ENR->bits.GPIOAEN = 1;
	GPIO_CONFIG(GPIOA, 0, GPIO_MODE_INPUT, GPIO_OTYPE_PP, GPIO_PUPD_PD, GPIO_OSPEED_HIGH, 0);

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

	RCC_APB1ENR->bits.TIM2EN = 1;
	RCC_APB1ENR->bits.TIM3EN = 1;
	TIM_INIT(TIM2, 15999, 500, 1, 0);
	TIM_INIT(TIM3, 15999,  10, 0, 1);

	//Enable interrupts
	NVIC_ENABLE_INT(TIM2_IRQn);
	NVIC_ENABLE_INT(TIM3_IRQn);
	NVIC_ENABLE_INT(EXTI0_LINE_IRQn);
	NVIC_ENABLE_INT(USART6_INT_IRQn);

	/* Loop forever */
	for(;;) {
		//SEND DATA
		UART_TransmitByte(USART6, 'X');
		UART_TransmitByte(USART6, 'Y');
		UART_TransmitByte(USART6, 'Z');
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
    // Verify if EXTI Line 0 is pending
    if (EXTI_IS_PENDING(0)) {
        // Clear pending bit
        EXTI_CLEAR_PENDING(0);

        // Lockout further bounces: Disable EXTI0 Interrupt Line
        EXTI_UNMASK_INTERRUPT(0, 0);

        // Trigger TIM3 (Reset counter and Enable counter)
        TIM3->CNT = 0;
        TIM_ENABLE_COUNTER(TIM3, 1);
    }
}

// Handles Task 1: Blink LED1 (Green) each 0.5 seconds
void TIM2_IRQHandler(void) {
    if (TIM_CHECK_FLAG(TIM2)) {
        TIM_CLEAR_FLAG(TIM2);    // Clear flag via BSP
        GPIO_PIN_TOGGLE(GPIOB, 1); // Toggle PB1
    }
}

// Handles Task 2: Samples & Software Debounces Button Inputs (10ms steps)
// 2. Debounce Lockout Timer Handler (Fires 50ms after initial edge)
void TIM3_IRQHandler(void) {
    // Check if Update Interrupt flag is set
    if (TIM_CHECK_FLAG(TIM3)) {
        // Clear the timer interrupt flag
    	TIM_CLEAR_FLAG(TIM3);

        // Verify the stable state of PA0 (High = Button is still pressed)
        if (GPIO_PIN_READ(GPIOA, 0) == GPIO_STATE_ONE) {
            // Toggle red led
        	GPIO_PIN_TOGGLE(GPIOA, 7);
        }

        // Clear any messy edge-triggers that occurred in EXTI0 during the 50ms lockout
        EXTI_CLEAR_PENDING(0);

        // Re-enable EXTI0 Interrupts to handle the next actual press
        EXTI_UNMASK_INTERRUPT(0, 1);
    }
}
