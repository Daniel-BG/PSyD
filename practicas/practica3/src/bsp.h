/*
 * bsp.h
 *
 *  Created on: Jul 9, 2026
 *      Author: dani
 */

#ifndef BSP_H_
#define BSP_H_

#include <stdint.h>

/*************************************************************
 * PERIPHERAL BASE ADDRESSES
 ************************************************************/

//GPIOS (General purpose Input Output)
#define GPIO_BASE_ADDR 0x40020000
#define GPIOA_BASE_ADDR (GPIO_BASE_ADDR + 0x0000)
#define GPIOB_BASE_ADDR (GPIO_BASE_ADDR + 0x0400)
#define GPIOC_BASE_ADDR (GPIO_BASE_ADDR + 0x0800)
#define GPIOD_BASE_ADDR (GPIO_BASE_ADDR + 0x0C00)
#define GPIOE_BASE_ADDR (GPIO_BASE_ADDR + 0x1000)
#define GPIOF_BASE_ADDR (GPIO_BASE_ADDR + 0x1400)
#define GPIOG_BASE_ADDR (GPIO_BASE_ADDR + 0x1800)
#define GPIOH_BASE_ADDR (GPIO_BASE_ADDR + 0x1C00)

//USER UARTS
#define USART6_BASE_ADDR 0x40011400

//RCC (Reset and clock control)
#define RCC_AHB1EN_BASE_ADDR 0x40023830 //AHB1 clock control register
#define RCC_APB1EN_BASE_ADDR 0x40023840 //APB1 clock control register
#define RCC_APB2EN_BASE_ADDR 0x40023844 //APB2 clock control register




/*************************************************************
 * REGISTER STRUCTURES
 ************************************************************/

//Structure for GPIO controllers
typedef struct
{
	volatile uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
	volatile uint32_t OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
	volatile uint32_t OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
	volatile uint32_t PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
	volatile uint32_t IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
	volatile uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
	volatile uint32_t BSRR;     /*!< GPIO port bit set/reset register,      Address offset: 0x18      */
	volatile uint32_t LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
	volatile uint32_t AFR[2];   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
} GPIO_TypeDef;

//Structure for UART handlers
typedef struct
{
	volatile uint32_t CR1;        /*!< USART Control register 1,                Address offset: 0x00 */
	volatile uint32_t CR2;        /*!< USART Control register 2,                Address offset: 0x04 */
	volatile uint32_t CR3;        /*!< USART Control register 3,                Address offset: 0x08 */
	volatile uint32_t BRR;        /*!< USART Baud rate register,                Address offset: 0x0C */
	volatile uint32_t GTPR;       /*!< USART Guard time and prescaler register, Address offset: 0x10 */
	volatile uint32_t RTOR;       /*!< USART receiver timeout register,         Address offset: 0x14 */
	volatile uint32_t RQR;        /*!< USART Request register, 					Address offset: 0x18 */
	volatile uint32_t ISR;        /*!< USART Interrupt and status register, 	Address offset: 0x1C */
	volatile uint32_t ICR;        /*!< USART Interrupt clean register, 			Address offset: 0x20 */
	volatile uint32_t RDR;        /*!< USART Received Data Register,            Address offset: 0x24 */
	volatile uint32_t TDR;        /*!< USART Transmit Data Register,            Address offset: 0x24 */
} USART_TypeDef;

//Structure for Clock Control peripheral clock register AHB1
typedef union {
    volatile uint32_t reg;

    // 2. Access individual bits or bit-groups for the register above
    struct {
    	volatile uint32_t GPIOAEN   	: 1;  // Bit 0: Enable peripheral (1 bit)
    	volatile uint32_t GPIOBEN   	: 1;  // Bit 1: Enable peripheral (1 bit)
    	volatile uint32_t GPIOCEN   	: 1;  // Bit 2: Enable peripheral (1 bit)
    	volatile uint32_t GPIODEN   	: 1;  // Bit 3: Enable peripheral (1 bit)
    	volatile uint32_t GPIOEEN   	: 1;  // Bit 4: Enable peripheral (1 bit)
    	volatile uint32_t GPIOFEN   	: 1;  // Bit 5: Enable peripheral (1 bit)
    	volatile uint32_t GPIOGEN   	: 1;  // Bit 6: Enable peripheral (1 bit)
    	volatile uint32_t GPIOHEN   	: 1;  // Bit 7: Enable peripheral (1 bit)
    	volatile uint32_t GPIOIEN   	: 1;  // Bit 8: Enable peripheral (1 bit)
    	volatile uint32_t GPIOJEN   	: 1;  // Bit 9: Enable peripheral (1 bit)
    	volatile uint32_t GPIOKEN   	: 1;  // Bit 10: Enable peripheral (1 bit)
    	volatile uint32_t RES1  		: 1;  // Bit 11: Reserved (1 bit)
    	volatile uint32_t CRCEN	    	: 1;  // Bit 12: CRC Clock Enable (1 bit)
    	volatile uint32_t RES2  		: 5;  // Bit 13-17: Reserved (5 bit)
    	volatile uint32_t BKPSRAMEN 	: 1;  // Bit 18: Backup SRAM enable (1 bit)
    	volatile uint32_t RES3  		: 1;  // Bit 19: Reserved (1 bit)
    	volatile uint32_t CCMDATARAMEN	: 1;  // Bit 20: CCM Data RAM enable (1 bit)
    	volatile uint32_t DMA1EN  		: 1;  // Bit 21: DMA1 enable (1 bit)
    	volatile uint32_t DMA2EN  		: 1;  // Bit 22: DMA2 enable (1 bit)
    	volatile uint32_t DMA2DEN  		: 1;  // Bit 23: DMA2D enable (1 bit)
    	volatile uint32_t RES4  		: 1;  // Bit 24: Reserved (1 bit)
    	volatile uint32_t ETHMACEN  	: 1;  // Bit 25: Ethernet MAC enable (1 bit)
    	volatile uint32_t ETHMACTXEN  	: 1;  // Bit 26: Ethernet Transmission enable (1 bit)
    	volatile uint32_t ETHMACRXEN  	: 1;  // Bit 27: Ethernet reception enable (1 bit)
    	volatile uint32_t ETHMACPTPEN  	: 1;  // Bit 28: Ethernet PTP enable (1 bit)
    	volatile uint32_t OTGHSEN  		: 1;  // Bit 29: USB OTG HS enable (1 bit)
    	volatile uint32_t OTGHSULPIEN  	: 1;  // Bit 30: USB OTG HSULPI enable (1 bit)
    	volatile uint32_t RES5  		: 1;  // Bit 31: Reserved (1 bit)
    } bits;
} RCC_AHB1ENR_TypeDef;

//Structure for Reset Control peripheral register APB1
typedef union {
    volatile uint32_t reg;

    // 2. Access individual bits or bit-groups for the register above
    struct {
    	volatile uint32_t TIM2EN	   	: 1;  // Bit 0: TIM2
    	volatile uint32_t TIM3EN	   	: 1;  // Bit 1: TIM3
    	volatile uint32_t TIM4EN	   	: 1;  // Bit 2: TIM4
    	volatile uint32_t TIM5EN	   	: 1;  // Bit 3: TIM5
    	volatile uint32_t TIM6EN 	  	: 1;  // Bit 4: TIM6
    	volatile uint32_t TIM7EN	   	: 1;  // Bit 5: TIM7
    	volatile uint32_t TIM12EN	  	: 1;  // Bit 6: TIM12
    	volatile uint32_t TIM13EN	  	: 1;  // Bit 7: TIM13
    	volatile uint32_t TIM14EN	 	: 1;  // Bit 8: TIM14
    	volatile uint32_t RES1EN	  	: 2;  // Bit 9-10: Reserved
    	volatile uint32_t WWDGEN		: 1;  // Bit 11: Window watchdog reset
    	volatile uint32_t RES2EN    	: 2;  // Bit 12-13: Reserved
    	volatile uint32_t SPI2EN		: 1;  // Bit 14: SPI2
    	volatile uint32_t SPI3EN	 	: 1;  // Bit 15: SPI3
    	volatile uint32_t RES3EN		: 1;  // Bit 16: Reserved
    	volatile uint32_t USART2EN		: 1;  // Bit 17: UART2
    	volatile uint32_t USART3EN	  	: 1;  // Bit 18: UART3
    	volatile uint32_t USART4EN	 	: 1;  // Bit 19: UART4
    	volatile uint32_t USART5EN	 	: 1;  // Bit 20: UART5
    	volatile uint32_t I2C1EN		: 1;  // Bit 21: I2C1
    	volatile uint32_t I2C2EN	  	: 1;  // Bit 22: I2C2
    	volatile uint32_t I2C3EN	  	: 1;  // Bit 23: I2C3
    	volatile uint32_t RES4EN	  	: 1;  // Bit 24: Reserved
    	volatile uint32_t CAN1EN	  	: 1;  // Bit 25: CAN1
    	volatile uint32_t CAN2EN		: 1;  // Bit 26: CAN2
    	volatile uint32_t RES5EN		: 1;  // Bit 27: Reserved
    	volatile uint32_t PWREN  		: 1;  // Bit 28: Power interface
    	volatile uint32_t DACEN  		: 1;  // Bit 29: DAC
    	volatile uint32_t UART7EN		: 1;  // Bit 30: UART 7
    	volatile uint32_t UART8EN		: 1;  // Bit 31: UART 8
    } bits;
} RCC_APB1R_TypeDef;

//Structure for Reset Control peripheral register APB1
typedef union {
    volatile uint32_t reg;

    // 2. Access individual bits or bit-groups for the register above
    struct {
    	volatile uint32_t TIM1EN	   	: 1;  // Bit 0:
    	volatile uint32_t TIM8EN	   	: 1;  // Bit 1:
    	volatile uint32_t RES1		   	: 2;  // Bit 2-3:
    	volatile uint32_t USART1EN	   	: 1;  // Bit 4:
    	volatile uint32_t USART6EN	  	: 1;  // Bit 5:
    	volatile uint32_t RES2		   	: 1;  // Bit 6:
    	volatile uint32_t SDMMC2EN	   	: 1;  // Bit 7:
    	volatile uint32_t ADC1EN	   	: 1;  // Bit 8:
    	volatile uint32_t ADC2EN	   	: 1;  // Bit 9:
    	volatile uint32_t ADC3EN	   	: 1;  // Bit 10:
    	volatile uint32_t SDMMC1EN	   	: 1;  // Bit 11:
    	volatile uint32_t SPI1EN	   	: 1;  // Bit 12:
    	volatile uint32_t SPI4EN	   	: 1;  // Bit 13:
    	volatile uint32_t SYSCFGEN	   	: 1;  // Bit 14:
    	volatile uint32_t RES3		   	: 1;  // Bit 15:
    	volatile uint32_t TIM9EN	   	: 1;  // Bit 16:
    	volatile uint32_t TIM10EN	   	: 1;  // Bit 17:
    	volatile uint32_t TIM11EN	   	: 1;  // Bit 18:
    	volatile uint32_t RES4		   	: 1;  // Bit 19:
    	volatile uint32_t SPI5EN	   	: 1;  // Bit 20:
    	volatile uint32_t RES5		   	: 1;  // Bit 21:
    	volatile uint32_t SAI1EN		: 1;  // Bit 22:
    	volatile uint32_t SAI2EN		: 1;  // Bit 23:
    	volatile uint32_t RES6		   	: 7;  // Bit 24-30:
    	volatile uint32_t OTGPHYCEN		: 1;  // Bit 31:
    } bits;
} RCC_APB2R_TypeDef;


/*************************************************************
 * PERIPHERAL INSTANCES TO BE USED
 ************************************************************/

#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE_ADDR)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE_ADDR)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE_ADDR)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE_ADDR)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE_ADDR)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE_ADDR)
#define GPIOG               ((GPIO_TypeDef *) GPIOG_BASE_ADDR)
#define GPIOH               ((GPIO_TypeDef *) GPIOH_BASE_ADDR)

#define RCC_AHB1ENR 		((RCC_AHB1ENR_TypeDef *) RCC_AHB1EN_BASE_ADDR)
#define RCC_APB1ENR			((RCC_APB1R_TypeDef *) RCC_APB1EN_BASE_ADDR)
#define RCC_APB2ENR			((RCC_APB2R_TypeDef *) RCC_APB2EN_BASE_ADDR)

#define USART6				((USART_TypeDef *) USART6_BASE_ADDR)



/*************************************************************
 * MACROS
 ************************************************************/

static inline void _REGISTER_SET(volatile uint32_t * reg, uint32_t mask, uint32_t value, uint32_t shift) {
    uint32_t temp = *reg;
    temp &= ~(mask << shift);
    temp |= (value << shift);
    *reg = temp;
}

static inline void _GPIO_REG_SET(volatile uint32_t *reg_ptr, uint32_t pin, uint32_t mask, uint32_t value, uint32_t shift_mult) {
	_REGISTER_SET(reg_ptr, mask, value, pin*shift_mult);
}


/*************************************************************
 * API FUNCTIONS
 ************************************************************/

/************************** GPIO ****************************/
// GPIO MODE SET
typedef enum {
    GPIO_MODE_INPUT  = 0x00,
    GPIO_MODE_OUTPUT = 0x01,
    GPIO_MODE_ALT    = 0x02,
    GPIO_MODE_ANALOG = 0x03
} GPIO_Mode_t;
static inline void GPIO_MODE_SET(volatile GPIO_TypeDef *GPIOx, uint32_t pin, GPIO_Mode_t mode) {
    _GPIO_REG_SET(&(GPIOx)->MODER, pin, 0x03, (uint32_t)mode, 2);
}

// GPIO OUTPUT TYPE SET
typedef enum {
    GPIO_OTYPE_PP = 0x00,
    GPIO_OTYPE_OD = 0x01
} GPIO_OType_t;
static inline void GPIO_OTYPE_SET(volatile GPIO_TypeDef *GPIOx, uint32_t pin, GPIO_OType_t otype) {
    _GPIO_REG_SET(&(GPIOx)->OTYPER, pin, 0x01, (uint32_t)otype, 1);
}

// GPIO OUTPUT SPEED SET
typedef enum {
    GPIO_OSPEED_LOW    = 0x00,
    GPIO_OSPEED_MEDIUM = 0x01,
    GPIO_OSPEED_HIGH   = 0x02,
    GPIO_OSPEED_VHIGH  = 0x03
} GPIO_OSpeed_t;
static inline void GPIO_OSPEED_SET(volatile GPIO_TypeDef *GPIOx, uint32_t pin, GPIO_OSpeed_t ospeed) {
    _GPIO_REG_SET(&(GPIOx)->OSPEEDR, pin, 0x03, (uint32_t)ospeed, 2);
}

// GPIO PULLUP/DOWN SET
typedef enum {
    GPIO_PUPD_NONE = 0x00,
    GPIO_PUPD_PU   = 0x01,
    GPIO_PUPD_PD   = 0x02
} GPIO_PuPd_t;
static inline void GPIO_PUPD_SET(volatile GPIO_TypeDef *GPIOx, uint32_t pin, GPIO_PuPd_t pupd) {
    _GPIO_REG_SET(&(GPIOx)->PUPDR, pin, 0x03, (uint32_t)pupd, 2);
}

// GPIO ALTERNATE FUNCTIONS
#define GPIO_AF8_USART6 0x8
static inline void GPIO_AF_SET(volatile GPIO_TypeDef *GPIOx, uint32_t pin, uint32_t af) {
	if (pin < 8) {
		_GPIO_REG_SET(&(GPIOx)->AFR[0], pin, 0x0F, (uint32_t)af, 4);
	} else {
		_GPIO_REG_SET(&(GPIOx)->AFR[1], pin-8, 0x0F, (uint32_t)af, 4);
	}
}

// ATOMIC GPIO WRITE VIA BSRR
typedef enum {
    GPIO_STATE_ZERO= 0x00,
    GPIO_STATE_ONE = 0x01
} GPIO_State_t;
static inline void GPIO_PIN_WRITE(volatile GPIO_TypeDef *GPIOx, uint32_t pin, GPIO_State_t state) {
    if (state) {
        GPIOx->BSRR = (1 << pin);
    } else {
        GPIOx->BSRR = (1 << (pin + 16));
    }
}

// GPIO READ
static inline uint32_t GPIO_PIN_READ(volatile GPIO_TypeDef *GPIOx, uint32_t pin) {
    return (GPIOx->IDR >> pin) & 0x01;
}





/************************** UART ****************************/

// UART STOP BITS
typedef enum {
    UART_STOP_ONEBIT = 0x00,
    UART_STOP_HALFBIT = 0x01,
    UART_STOP_TWOBIT   = 0x02,
	UART_STOP_ONEHALFBIT = 0x03
} UART_Stop_t;
#define UART_STOP_MASK 0b11
#define UART_STOP_SHIFT 12

static inline void UART_STOPBIT_SET(volatile USART_TypeDef *USARTx, UART_Stop_t stopbits) {
	_REGISTER_SET(&USARTx->CR2, UART_STOP_MASK, stopbits, UART_STOP_SHIFT);
}

// UART ENABLE
typedef enum {
	UART_DISABLE = 0x00,
    UART_ENABLE = 0x01
} UART_Enable_t;
#define UART_ENABLE_MASK 0b1
#define UART_ENABLE_SHIFT 0

static inline void UART_ENABLE_SET(volatile USART_TypeDef *USARTx, UART_Enable_t enable) {
	_REGISTER_SET(&USARTx->CR1, UART_ENABLE_MASK, enable, UART_ENABLE_SHIFT);
}

// UART WORD LENGTH
typedef enum {
    UART_WORD_8B = 0x00,
    UART_WORD_9B = 0x01,
	UART_WORD_7B = 0x02
} UART_WordLength_t;
#define UART_WORD_MASK  0b1
#define UART_WORD_SHIFT 12

static inline void UART_WORDLENGTH_SET(volatile USART_TypeDef *USARTx, UART_WordLength_t length) {
    _REGISTER_SET(&USARTx->CR1, UART_WORD_MASK, length, UART_WORD_SHIFT);
}

// UART PARITY
typedef enum {
    UART_PARITY_NONE = 0x00, // PCE = 0
    UART_PARITY_EVEN = 0x02, // PCE = 1, PS = 0
    UART_PARITY_ODD  = 0x03  // PCE = 1, PS = 1
} UART_Parity_t;
#define UART_PARITY_MASK  0b11
#define UART_PARITY_SHIFT 9

static inline void UART_PARITY_SET(volatile USART_TypeDef *USARTx, UART_Parity_t parity) {
    _REGISTER_SET(&USARTx->CR1, UART_PARITY_MASK, parity, UART_PARITY_SHIFT);
}

// UART OVERSAMPLING
typedef enum {
    UART_OVERSAMPLING_16 = 0x00,
    UART_OVERSAMPLING_8  = 0x01
} UART_Oversampling_t;
#define UART_OVER_MASK  0b1
#define UART_OVER_SHIFT 15

static inline void UART_OVERSAMPLING_SET(volatile USART_TypeDef *USARTx, UART_Oversampling_t over) {
    _REGISTER_SET(&USARTx->CR1, UART_OVER_MASK, over, UART_OVER_SHIFT);
}

// TRANSMIT enable
typedef enum {
    UART_TX_DISABLE = 0x00,
    UART_TX_ENABLE  = 0x01
} UART_TX_Mode_t;
#define UART_TX_MODE_MASK  0b1
#define UART_TX_MODE_SHIFT 3

static inline void UART_TX_MODE_SET(volatile USART_TypeDef *USARTx, UART_TX_Mode_t mode) {
    _REGISTER_SET(&USARTx->CR1, UART_TX_MODE_MASK, mode, UART_TX_MODE_SHIFT);
}

// Transmit a single byte
static inline void UART_TransmitByte(volatile USART_TypeDef *USARTx, uint8_t data)
{
    while (!(USARTx->ISR & (1U << 7U))); //Wait until we can push data (TXE bit enabled)
    USARTx->TDR = data; //push data (this clears TXE bit)
}


void delay(int loops) {
	for (int i = 0; i < loops; i++) {
		__asm("nop");
	}
}


#endif /* BSP_H_ */
