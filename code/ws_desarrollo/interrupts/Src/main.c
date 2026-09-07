

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
	// ... completar Activar el modo RX de la UART
	// ... completar Activar las interrupciones de la UART

	// ... completar Activar el reloj de SYSCFGEN
	// ... completar mapear puerto A (0) a eint0
	// ... completar activar rising trigger on port A (0)
	// ... completar desenmascarar interrupción en puerto A (0)

	// ... completar activar las líneas de interrupción EXTI0 y USART6


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
    //... completar comprobar si el flag de interrupción está activo
    if () {
        //... completar leer el byte y retransmitirlo
    }
}


void EXTI0_IRQHandler(void)
{
    //... comprobar en EXTI->PR si la línea 0 generó interrupción
    if () {
        //... limpiar línea 0 escribiendo la posición 0 de EXTI->PR
        //... completar funcionalidad
    }
}
