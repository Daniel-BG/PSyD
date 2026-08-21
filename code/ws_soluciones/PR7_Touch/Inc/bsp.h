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

//CONFIG
#define EXTI_BASE_ADDR 		0x40013C00UL
#define SYSCFG_BASE_ADDR    0x40013800UL

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
#define GPIOI_BASE_ADDR (GPIO_BASE_ADDR + 0x2000)


#define I2C3_BASE_ADDR 0x40005C00UL

//USER UARTS
#define USART6_BASE_ADDR 0x40011400

//RCC (Reset and clock control)
#define RCC_AHB3RST_BASE_ADDR 0x40023818 //AHB3 reset register
#define RCC_APB1RST_BASE_ADDR 0x40023820 //APB1 reset register

#define RCC_AHB1EN_BASE_ADDR 0x40023830 //AHB1 clock control register
#define RCC_AHB3EN_BASE_ADDR 0x40023838 //AHB3 clock control register
#define RCC_APB1EN_BASE_ADDR 0x40023840 //APB1 clock control register
#define RCC_APB2EN_BASE_ADDR 0x40023844 //APB2 clock control register



//NVIC
#define NVIC_BASE_ADDR 0xE000E100

//TIMERS
#define TIM2_BASE_ADDR   0x40000000UL
#define TIM3_BASE_ADDR   0x40000400UL

//FMC
#define FMC_BANK2_BASE_ADDR  ((uint32_t)(0x60000000 | 0x04000000))

//FSMC (Flexible memory controller)
#define FMC_BASE_ADDR				0xA0000000UL /*!< FMC registers base address                                                */

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

//Structure for Reset Control peripheral register APB2
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

//Structure for Reset Control peripheral register AHB3
typedef union {
    volatile uint32_t reg;

    // 2. Access individual bits or bit-groups for the register above
    struct {
    	volatile uint32_t FMCEN		   	: 1;  // Bit 0:
    	volatile uint32_t QSPIEN	   	: 1;  // Bit 1:
    	volatile uint32_t RES			: 30; // rest of bits
    } bits;
} RCC_AHB3ENR_TypeDef;

typedef struct
{
	volatile uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
	uint32_t RESERVED0[24U];
	volatile uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
	uint32_t RESERVED1[24U];
	volatile uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
	uint32_t RESERVED2[24U];
	volatile uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
	uint32_t RESERVED3[24U];
	volatile uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
	uint32_t RESERVED4[56U];
	volatile uint8_t  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
	uint32_t RESERVED5[644U];
	volatile  uint32_t STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}  NVIC_TypeDef;

typedef struct
{
	volatile uint32_t MEMRMP;       /*!< SYSCFG memory remap register,                      Address offset: 0x00      */
	volatile uint32_t PMC;          /*!< SYSCFG peripheral mode configuration register,     Address offset: 0x04      */
	volatile uint32_t EXTICR[4];    /*!< SYSCFG external interrupt configuration registers, Address offset: 0x08-0x14 */
			 uint32_t RESERVED[2];  /*!< Reserved, 0x18-0x1C                                                          */
	volatile uint32_t CMPCR;        /*!< SYSCFG Compensation cell control register,         Address offset: 0x20      */
} SYSCFG_TypeDef;

typedef struct
{
	volatile uint32_t IMR;    /*!< EXTI Interrupt mask register,            Address offset: 0x00 */
	volatile uint32_t EMR;    /*!< EXTI Event mask register,                Address offset: 0x04 */
	volatile uint32_t RTSR;   /*!< EXTI Rising trigger selection register,  Address offset: 0x08 */
	volatile uint32_t FTSR;   /*!< EXTI Falling trigger selection register, Address offset: 0x0C */
	volatile uint32_t SWIER;  /*!< EXTI Software interrupt event register,  Address offset: 0x10 */
	volatile uint32_t PR;     /*!< EXTI Pending register,                   Address offset: 0x14 */
} EXTI_TypeDef;

//Structure for Timers (TIM2 / TIM3)
typedef struct
{
	volatile uint32_t CR1;        /*!< TIM control register 1,                  Address offset: 0x00 */
	volatile uint32_t CR2;        /*!< TIM control register 2,                  Address offset: 0x04 */
	volatile uint32_t SMCR;       /*!< TIM slave mode control register,         Address offset: 0x08 */
	volatile uint32_t DIER;       /*!< TIM DMA/Interrupt enable register,       Address offset: 0x0C */
	volatile uint32_t SR;         /*!< TIM status register,                     Address offset: 0x10 */
	volatile uint32_t EGR;        /*!< TIM event generation register,           Address offset: 0x14 */
	volatile uint32_t CCMR1;      /*!< TIM capture/compare mode register 1,     Address offset: 0x18 */
	volatile uint32_t CCMR2;      /*!< TIM capture/compare mode register 2,     Address offset: 0x1C */
	volatile uint32_t CCER;       /*!< TIM capture/compare enable register,     Address offset: 0x20 */
	volatile uint32_t CNT;        /*!< TIM counter,                             Address offset: 0x24 */
	volatile uint32_t PSC;        /*!< TIM prescaler,                           Address offset: 0x28 */
	volatile uint32_t ARR;        /*!< TIM auto-reload register,                Address offset: 0x2C */
	uint32_t RESERVED;
	volatile uint32_t CCR1;       /*!< TIM capture/compare register 1,          Address offset: 0x34 */
	volatile uint32_t CCR2;       /*!< TIM capture/compare register 2,          Address offset: 0x38 */
	volatile uint32_t CCR3;       /*!< TIM capture/compare register 3,          Address offset: 0x3C */
	volatile uint32_t CCR4;       /*!< TIM capture/compare register 4,          Address offset: 0x40 */
	uint32_t RESERVED2;
	volatile uint32_t DCR;        /*!< TIM DMA control register,                Address offset: 0x48 */
	volatile uint32_t DMAR;       /*!< TIM DMA address for full transfer,       Address offset: 0x4C */
	volatile uint32_t OR;         /*!< TIM Option Register,			       		Address offset: 0x4C */
} TIM_TypeDef;

typedef struct
{
	volatile uint16_t REG;
	volatile uint16_t RAM;
} FMC_CONTROLLER_TypeDef;

typedef struct
{
	volatile uint32_t BCR1; 	/* 0x00 */
	volatile uint32_t BTR1; 	/* 0x04 */
	volatile uint32_t BCR2; 	/* 0x08 */
	volatile uint32_t BTR2; 	/* 0x0C */
	volatile uint32_t BCR3; 	/* 0x10 */
	volatile uint32_t BTR3; 	/* 0x14 */
	volatile uint32_t BCR4; 	/* 0x18 */
	volatile uint32_t BTR4; 	/* 0x1C */
	uint32_t RES0[24];			/* 0x20-0x7C */
	volatile uint32_t PCR;		/* 0x80 */
	volatile uint32_t SR;		/* 0x84 */
	volatile uint32_t PMEM;		/* 0x88 */
	volatile uint32_t PATT;		/* 0x8C */
	uint32_t RES1;				/* 0x90 */
	volatile uint32_t ECCR;		/* 0x94 */
	uint32_t RES2[3];			/* 0x100 */
	volatile uint32_t BWTR1; 	/* 0x104 */
	uint32_t RES3;				/* 0x108 */
	volatile uint32_t BWTR2; 	/* 0x10C */
	uint32_t RES4;				/* 0x110 */
	volatile uint32_t BWTR3; 	/* 0x114 */
	uint32_t RES5;				/* 0x118 */
	volatile uint32_t BWTR4; 	/* 0x11C */
	uint32_t RES6[8];			/* 0x120-0x13C */
	volatile uint32_t SDCR1; 	/* 0x140 */
	volatile uint32_t SDCR2; 	/* 0x144 */
	volatile uint32_t SDTR1; 	/* 0x148 */
	volatile uint32_t SDTR2; 	/* 0x14C */
	volatile uint32_t SDCMR; 	/* 0x150 */
	volatile uint32_t SDRTR; 	/* 0x154 */
	volatile uint32_t SDSR; 	/* 0x158 */
} FMC_TypeDef;

typedef struct
{
	volatile uint32_t CR1;      /*!< I2C Control register 1,            Address offset: 0x00 */
	volatile uint32_t CR2;      /*!< I2C Control register 2,            Address offset: 0x04 */
	volatile uint32_t OAR1;     /*!< I2C Own address 1 register,        Address offset: 0x08 */
	volatile uint32_t OAR2;     /*!< I2C Own address 2 register,        Address offset: 0x0C */
	volatile uint32_t TIMINGR;  /*!< I2C Timing register,               Address offset: 0x10 */
	volatile uint32_t TIMEOUTR; /*!< I2C Timeout register,              Address offset: 0x14 */
	volatile uint32_t ISR;      /*!< I2C Interrupt and status register, Address offset: 0x18 */
	volatile uint32_t ICR;      /*!< I2C Interrupt clear register,      Address offset: 0x1C */
	volatile uint32_t PECR;     /*!< I2C PEC register,                  Address offset: 0x20 */
	volatile uint32_t RXDR;     /*!< I2C Receive data register,         Address offset: 0x24 */
	volatile uint32_t TXDR;     /*!< I2C Transmit data register,        Address offset: 0x28 */
} I2C_TypeDef;

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
#define GPIOI               ((GPIO_TypeDef *) GPIOI_BASE_ADDR)

#define RCC_AHB3RSTR		((RCC_AHB3ENR_TypeDef *) RCC_AHB3RST_BASE_ADDR)
#define RCC_AHB1ENR 		((RCC_AHB1ENR_TypeDef *) RCC_AHB1EN_BASE_ADDR)
#define RCC_AHB3ENR 		((RCC_AHB3ENR_TypeDef *) RCC_AHB3EN_BASE_ADDR)
#define RCC_APB1ENR			((RCC_APB1R_TypeDef *) RCC_APB1EN_BASE_ADDR)
#define RCC_APB2ENR			((RCC_APB2R_TypeDef *) RCC_APB2EN_BASE_ADDR)

#define RCC_APB1RST			((RCC_APB1R_TypeDef *) RCC_APB1RST_BASE_ADDR)

#define USART6				((USART_TypeDef *) USART6_BASE_ADDR)
#define USART6_INT_IRQn 	71

#define EXTI                ((EXTI_TypeDef *) EXTI_BASE_ADDR)
#define EXTI0_LINE_IRQn 	6
#define EXTI9_5_IRQn		23

#define NVIC 				((NVIC_TypeDef *) NVIC_BASE_ADDR)

#define SYSCFG              ((SYSCFG_TypeDef *) SYSCFG_BASE_ADDR)

#define TIM2                ((TIM_TypeDef *) TIM2_BASE_ADDR)
#define TIM3                ((TIM_TypeDef *) TIM3_BASE_ADDR)
#define TIM2_IRQn           28
#define TIM3_IRQn           29

#define FMC_BANK2       	((FMC_CONTROLLER_TypeDef *) FMC_BANK2_BASE_ADDR)

#define FMC			        ((FMC_TypeDef *) FMC_BASE_ADDR)

#define I2C3				((I2C_TypeDef *) I2C3_BASE_ADDR)
#define I2C3_EV_IRQn        72
#define I2C3_ER_IRQn        73



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

__attribute__((always_inline)) static inline void __DSB(void)
{
	__asm volatile ("dsb 0xF":::"memory");
}

__attribute__((always_inline)) static inline void __DMB(void)
{
	__asm volatile ("dmb 0xF":::"memory");
}

__attribute__((always_inline)) static inline void __ISB(void)
{
	__asm volatile ("isb 0xF":::"memory");
}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
#define __NVIC_PRIO_BITS          4U       /*!< CM7 uses 4 Bits for the Priority Levels       */

typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;


volatile uint32_t uwTick;
uint32_t uwTickPrio   = (1UL << __NVIC_PRIO_BITS); /* Invalid PRIO */
HAL_TickFreqTypeDef uwTickFreq = HAL_TICK_FREQ_DEFAULT;  /* 1KHz */
uint32_t SystemCoreClock = 16000000;
#define HAL_MAX_DELAY      0xFFFFFFFFU

void HAL_Delay(uint32_t Delay)
{
  uint32_t tickstart = uwTick;
  uint32_t wait = Delay;

  /* Add a freq to guarantee minimum wait */
  if (wait < HAL_MAX_DELAY)
  {
    wait += (uint32_t)(uwTickFreq);
  }

  while ((uwTick - tickstart) < wait)
  {
  }
}

void DELAY(uint32_t Delay)
{
	//HAL_Delay(Delay);
	for (uint32_t i = 0; i < 16000*Delay/8; i++);
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
#define GPIO_AF4_I2C 0x4
#define GPIO_AF8_USART6 0x8
#define GPIO_AF12_FSMC 0xC
static inline void GPIO_AF_SET(volatile GPIO_TypeDef *GPIOx, uint32_t pin, uint32_t af) {
	if (pin < 8) {
		_GPIO_REG_SET(&(GPIOx)->AFR[0], pin, 0x0F, (uint32_t)af, 4);
	} else {
		_GPIO_REG_SET(&(GPIOx)->AFR[1], pin-8, 0x0F, (uint32_t)af, 4);
	}
}

// GPIO full inline config
static inline void GPIO_CONFIG(volatile GPIO_TypeDef *GPIOx, uint32_t pin, GPIO_Mode_t mode, GPIO_OType_t otype, GPIO_OSpeed_t ospeed, GPIO_PuPd_t pupd, uint32_t af) {
	GPIO_MODE_SET(GPIOx, pin, mode);
	GPIO_OTYPE_SET(GPIOx, pin, otype);
	GPIO_OSPEED_SET(GPIOx, pin, ospeed);
	GPIO_PUPD_SET(GPIOx, pin, pupd);
	GPIO_AF_SET(GPIOx, pin, af);
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

// GPIO TOGGLE
static inline void GPIO_PIN_TOGGLE(volatile GPIO_TypeDef *GPIOx, uint32_t pin) {
	GPIO_PIN_WRITE(GPIOx, pin, (!GPIO_PIN_READ(GPIOx, pin)) & 0x1);
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

// RECEIVE enable
typedef enum {
    UART_RX_DISABLE = 0x00,
    UART_RX_ENABLE  = 0x01
} UART_RX_Mode_t;
#define UART_RX_MODE_MASK  0b1
#define UART_RX_MODE_SHIFT 2

static inline void UART_RX_MODE_SET(volatile USART_TypeDef *USARTx, UART_RX_Mode_t mode) {
    _REGISTER_SET(&USARTx->CR1, UART_RX_MODE_MASK, mode, UART_RX_MODE_SHIFT);
}

// RECEIVE interrupt enable
typedef enum {
    UART_RX_INT_DISABLE = 0x00,
    UART_RX_INT_ENABLE  = 0x01
} UART_RX_INT_t;
#define UART_RX_INT_MASK  0b1
#define UART_RX_INT_SHIFT 5

static inline void UART_RX_INT_SET(volatile USART_TypeDef *USARTx, UART_RX_INT_t mode) {
    _REGISTER_SET(&USARTx->CR1, UART_RX_INT_MASK, mode, UART_RX_INT_SHIFT);
}

static inline void UART_BRR_SET(volatile USART_TypeDef *USARTx, uint32_t brr) {
	USARTx->BRR = brr;
}

// Transmit a single byte
static inline void UART_TransmitByte(volatile USART_TypeDef *USARTx, uint8_t data)
{
    while (!(USARTx->ISR & (1U << 7U))); //Wait until we can push data (TXE bit enabled)
    USARTx->TDR = data; //push data (this clears TXE bit)
}
// Read byte buffer
static inline uint8_t UART_ReadDataRegister(volatile USART_TypeDef *USARTx) {
	return (uint8_t)(USARTx->RDR & 0xFFU);
}

//STATUS READ FUNCTIONS
static inline uint32_t UART_STATUS_RXNE(volatile USART_TypeDef *USARTx) {
	return USARTx->ISR & (0x1 << 5);
}
static inline uint32_t UART_STATUS_ORE(volatile USART_TypeDef *USARTx) {
	return USARTx->ISR & (0x1 << 3);
}
static inline uint32_t UART_STATUS_PE(volatile USART_TypeDef *USARTx) {
	return USARTx->ISR & (0x1 << 0);
}



/************************** NVIC ****************************/

static inline void NVIC_ENABLE_INT(uint32_t line) {
	NVIC->ISER[line >> 5] |= (1U << (line & 0x1F));
}

static inline void NVIC_DISABLE_INT(uint32_t line) {
	NVIC->ISER[line >> 5] &= ~(1U << (line & 0x1F));
}



/************************* SYSCFG & EXTI *********************/

static inline void SYSCFG_EINT_MAP_PORT(uint32_t eintno, uint32_t portno) {
	uint32_t index = (eintno >> 2) & 0x3;
	SYSCFG->EXTICR[index] &= ~(0b1111 << ((eintno & 0x3)*4));
	SYSCFG->EXTICR[index] |=  (portno & 0xf) << ((eintno & 0x3)*4);
}

static inline void EXTI_ENABLE_RISING_TRIGGER(uint32_t eintno, uint32_t enable) {
	if (enable)
		EXTI->RTSR |=   0b1 << (eintno & 0xf);
	else
		EXTI->RTSR &= ~(0b1 << (eintno & 0xf));
}

static inline void EXTI_ENABLE_FALLING_TRIGGER(uint32_t eintno, uint32_t enable) {
	if (enable)
		EXTI->FTSR |=   0b1 << (eintno & 0xf);
	else
		EXTI->FTSR &= ~(0b1 << (eintno & 0xf));
}

static inline void EXTI_UNMASK_INTERRUPT(uint32_t eintno, uint32_t unmask) {
	if (unmask)
		EXTI->IMR |=   0b1 << (eintno & 0xf);
	else
		EXTI->IMR &= ~(0b1 << (eintno & 0xf));
}

static inline void EXTI_CLEAR_PENDING(uint32_t eintno) {
	EXTI->PR = (1U << (eintno));
}

static inline uint32_t EXTI_IS_PENDING(uint32_t eintno) {
	return EXTI->PR & (1U << (eintno));
}

/************************** TIMERS **************************/
static inline void TIM_ENABLE_COUNTER(volatile TIM_TypeDef *TIMx, uint32_t enable) {
	if (enable) TIMx->CR1 |= (1U << 0);
	else TIMx->CR1 &= ~(1U << 0);
}

static inline void TIM_ENABLE_ONESHOT(volatile TIM_TypeDef *TIMx, uint32_t enable) {
	if (enable) TIMx->CR1 |= (1U << 3);
	else TIMx->CR1 &= ~(1U << 3);
}

static inline void TIM_ENABLE_INT(volatile TIM_TypeDef *TIMx) {
	TIMx->DIER |= 1;
}

static inline void TIM_CLEAR_FLAG(volatile TIM_TypeDef *TIMx) {
	TIMx->SR &= ~1;
}

static inline uint32_t TIM_CHECK_FLAG(volatile TIM_TypeDef *TIMx) {
	return TIMx->SR & 1;
}

static inline void TIM_SET_PRESCALER(volatile TIM_TypeDef *TIMx, uint32_t value) {
    TIMx->PSC = value;
}

static inline void TIM_SET_AUTO_RELOAD(volatile TIM_TypeDef *TIMx, uint32_t value) {
    TIMx->ARR = value;
}

static inline void TIM_INIT(TIM_TypeDef *TIMx, uint32_t preescaler, uint32_t autoreload, uint32_t enable_counter, uint32_t enable_oneshot) {
    // Prescaler: Downscale clock to 1 kHz (assuming default 16 MHz internal HSI)
    TIM_SET_PRESCALER(TIMx, preescaler);
    // Auto-reload value: 500 ticks = 500 ms (0.5 seconds)
    TIM_SET_AUTO_RELOAD(TIMx, autoreload);
    // Enable the Update Interrupt (Bit 0)
    TIM_ENABLE_INT(TIMx);
    // Fire up the timer counter and enable oneshot if requested
    if (enable_counter)
    	TIM_ENABLE_COUNTER(TIMx, 1);
    if (enable_oneshot)
    	TIM_ENABLE_ONESHOT(TIMx, 1);
}



/***************************** FMC *************************/

static inline void FMC_BANK2_WriteReg(uint8_t Reg)
{
	/* Write 16-bit Index, then write register */
	FMC_BANK2->REG = Reg;
	__DSB();
}

static inline void FMC_BANK2_WriteData(uint16_t Data)
{
	/* Write 16-bit Reg */
	FMC_BANK2->RAM = Data;
	__DSB();
}

static void FSMC_NORSRAM_DISABLE(FMC_TypeDef * fsmc, uint32_t bank_number) {
	switch(bank_number) {
		case 1: fsmc->BCR1 &= ~0x1; break;
		case 2: fsmc->BCR2 &= ~0x1; break;
		case 3: fsmc->BCR3 &= ~0x1; break;
		case 4: fsmc->BCR4 &= ~0x1; break;
	}
}

static void FSMC_NORSRAM_ENABLE(FMC_TypeDef * fsmc, uint32_t bank_number) {
	switch(bank_number) {
		case 1: fsmc->BCR1 |=  0x1; break;
		case 2: fsmc->BCR2 |=  0x1; break;
		case 3: fsmc->BCR3 |=  0x1; break;
		case 4: fsmc->BCR4 |=  0x1; break;
	}
}

/* Each bank gets two uint32_t for configuration */
#define FSMC_NORSRAM_BANK1                       (0x00000000U)
#define FSMC_NORSRAM_BANK2                       (0x00000002U)
#define FSMC_NORSRAM_BANK3                       (0x00000004U)
#define FSMC_NORSRAM_BANK4                       (0x00000006U)

/******************  Bit definition for FSMC_BCR1 register  ******************/
#define FSMC_BCR1_MBKEN              (0x00000001U) /*!<Memory bank enable bit                 */
#define FSMC_BCR1_MUXEN              (0x00000002U) /*!<Address/data multiplexing enable bit   */
#define FSMC_BCR1_MTYP               (0x0000000CU) /*!<MTYP[1:0] bits (Memory type)           */
#define FSMC_BCR1_MWID               (0x00000030U) /*!<MWID[1:0] bits (Memory data bus width) */
#define FSMC_BCR1_FACCEN             (0x00000040U) /*!<Flash access enable                    */
#define FSMC_BCR1_BURSTEN            (0x00000100U) /*!<Burst enable bit                       */
#define FSMC_BCR1_WAITPOL            (0x00000200U) /*!<Wait signal polarity bit               */
#define FSMC_BCR1_WAITCFG            (0x00000800U) /*!<Wait timing configuration              */
#define FSMC_BCR1_WREN               (0x00001000U) /*!<Write enable bit                       */
#define FSMC_BCR1_WAITEN             (0x00002000U) /*!<Wait enable bit                        */
#define FSMC_BCR1_EXTMOD             (0x00004000U) /*!<Extended mode enable                   */
#define FSMC_BCR1_ASYNCWAIT          (0x00008000U) /*!<Asynchronous wait                      */
#define FSMC_BCR1_CPSIZE             (0x00070000U) /*!<CRAM page size 						  */
#define FSMC_BCR1_CBURSTRW           (0x00080000U) /*!<Write burst enable                     */
#define FSMC_BCR1_CCLKEN             (0x00100000U) /*!<Continuous clock enable     			  */
#define FSMC_BCR1_WFDIS              (0x00200000U) /*!<Write FIFO Disable         			  */

#define FSMC_DATA_ADDRESS_MUX_DISABLE            (0x00000000U)
#define FSMC_DATA_ADDRESS_MUX_ENABLE             (0x00000002U)

#define FSMC_MEMORY_TYPE_SRAM                    (0x00000000U)
#define FSMC_MEMORY_TYPE_PSRAM                   (0x00000004U)
#define FSMC_MEMORY_TYPE_NOR                     (0x00000008U)

#define FSMC_NORSRAM_MEM_BUS_WIDTH_8             (0x00000000U)
#define FSMC_NORSRAM_MEM_BUS_WIDTH_16            (0x00000010U)
#define FSMC_NORSRAM_MEM_BUS_WIDTH_32            (0x00000020U)

#define FSMC_NORSRAM_FLASH_ACCESS_EN         	 (0x00000040U)
#define FSMC_NORSRAM_FLASH_ACCESS_DIS			 (0x00000000U)

#define FSMC_BURST_ACCESS_MODE_DISABLE           (0x00000000U)
#define FSMC_BURST_ACCESS_MODE_ENABLE            (0x00000100U)

#define FSMC_WAIT_SIGNAL_POLARITY_LOW            (0x00000000U)
#define FSMC_WAIT_SIGNAL_POLARITY_HIGH           (0x00000200U)

#define FSMC_WRAP_MODE_DISABLE                   (0x00000000U)
#define FSMC_WRAP_MODE_ENABLE                    (0x00000400U)

#define FSMC_WAIT_TIMING_BEFORE_WS               (0x00000000U)
#define FSMC_WAIT_TIMING_DURING_WS               (0x00000800U)

#define FSMC_WRITE_OPERATION_DISABLE             (0x00000000U)
#define FSMC_WRITE_OPERATION_ENABLE              (0x00001000U)

#define FSMC_WAIT_SIGNAL_DISABLE                 (0x00000000U)
#define FSMC_WAIT_SIGNAL_ENABLE                  (0x00002000U)

#define FSMC_EXTENDED_MODE_DISABLE               (0x00000000U)
#define FSMC_EXTENDED_MODE_ENABLE                (0x00004000U)

#define FSMC_ASYNCHRONOUS_WAIT_DISABLE           (0x00000000U)
#define FSMC_ASYNCHRONOUS_WAIT_ENABLE            (0x00008000U)

#define FSMC_PAGE_SIZE_NONE                      (0x00000000U)
#define FSMC_PAGE_SIZE_128                       FSMC_BCR1_CPSIZE_0
#define FSMC_PAGE_SIZE_256                       FSMC_BCR1_CPSIZE_1
#define FSMC_PAGE_SIZE_512                       (FSMC_BCR1_CPSIZE_0\
                                                 | FSMC_BCR1_CPSIZE_1)
#define FSMC_PAGE_SIZE_1024                      FSMC_BCR1_CPSIZE_2

#define FSMC_WRITE_BURST_DISABLE                 (0x00000000U)
#define FSMC_WRITE_BURST_ENABLE                  (0x00080000U)

#define FSMC_CONTINUOUS_CLOCK_SYNC_ONLY          (0x00000000U)
#define FSMC_CONTINUOUS_CLOCK_SYNC_ASYNC         (0x00100000U)

#define FSMC_WRITE_FIFO_DISABLE                  FSMC_BCR1_WFDIS
#define FSMC_WRITE_FIFO_ENABLE                   (0x00000000U)

#define FSMC_ACCESS_MODE_A                       (0x00000000U)
#define FSMC_ACCESS_MODE_B                       (0x10000000U)
#define FSMC_ACCESS_MODE_C                       (0x20000000U)
#define FSMC_ACCESS_MODE_D                       (0x30000000U)

/******************  Bit definition for FSMC_BTR1 register  ******************/
#define FSMC_BTR1_ADDSET_Pos         (0U)
#define FSMC_BTR1_ADDSET_Msk         (0xFUL << FSMC_BTR1_ADDSET_Pos)            /*!< 0x0000000F */
#define FSMC_BTR1_ADDSET             FSMC_BTR1_ADDSET_Msk                      /*!<ADDSET[3:0] bits (Address setup phase duration) */

#define FSMC_BTR1_ADDHLD_Pos         (4U)
#define FSMC_BTR1_ADDHLD_Msk         (0xFUL << FSMC_BTR1_ADDHLD_Pos)            /*!< 0x000000F0 */
#define FSMC_BTR1_ADDHLD             FSMC_BTR1_ADDHLD_Msk                      /*!<ADDHLD[3:0] bits (Address-hold phase duration) */

#define FSMC_BTR1_DATAST_Pos         (8U)
#define FSMC_BTR1_DATAST_Msk         (0xFFUL << FSMC_BTR1_DATAST_Pos)           /*!< 0x0000FF00 */
#define FSMC_BTR1_DATAST             FSMC_BTR1_DATAST_Msk                      /*!<DATAST [7:0] bits (Data-phase duration) */

#define FSMC_BTR1_BUSTURN_Pos        (16U)
#define FSMC_BTR1_BUSTURN_Msk        (0xFUL << FSMC_BTR1_BUSTURN_Pos)           /*!< 0x000F0000 */
#define FSMC_BTR1_BUSTURN            FSMC_BTR1_BUSTURN_Msk                     /*!<BUSTURN[3:0] bits (Bus turnaround phase duration) */

#define FSMC_BTR1_CLKDIV_Pos         (20U)
#define FSMC_BTR1_CLKDIV_Msk         (0xFUL << FSMC_BTR1_CLKDIV_Pos)            /*!< 0x00F00000 */
#define FSMC_BTR1_CLKDIV             FSMC_BTR1_CLKDIV_Msk                      /*!<CLKDIV[3:0] bits (Clock divide ratio) */

#define FSMC_BTR1_DATLAT_Pos         (24U)
#define FSMC_BTR1_DATLAT_Msk         (0xFUL << FSMC_BTR1_DATLAT_Pos)            /*!< 0x0F000000 */
#define FSMC_BTR1_DATLAT             FSMC_BTR1_DATLAT_Msk                      /*!<DATLA[3:0] bits (Data latency) */

#define FSMC_BTR1_ACCMOD_Pos         (28U)
#define FSMC_BTR1_ACCMOD_Msk         (0x3UL << FSMC_BTR1_ACCMOD_Pos)            /*!< 0x30000000 */
#define FSMC_BTR1_ACCMOD             FSMC_BTR1_ACCMOD_Msk                      /*!<ACCMOD[1:0] bits (Access mode) */


/******************  Bit definition for FSMC_BWTR1 register  ******************/
#define FSMC_BWTR1_ADDSET_Pos        (0U)
#define FSMC_BWTR1_ADDSET_Msk        (0xFUL << FSMC_BWTR1_ADDSET_Pos)           /*!< 0x0000000F */
#define FSMC_BWTR1_ADDSET            FSMC_BWTR1_ADDSET_Msk                     /*!<ADDSET[3:0] bits (Address setup phase duration) */

#define FSMC_BWTR1_ADDHLD_Pos        (4U)
#define FSMC_BWTR1_ADDHLD_Msk        (0xFUL << FSMC_BWTR1_ADDHLD_Pos)           /*!< 0x000000F0 */
#define FSMC_BWTR1_ADDHLD            FSMC_BWTR1_ADDHLD_Msk                     /*!<ADDHLD[3:0] bits (Address-hold phase duration) */

#define FSMC_BWTR1_DATAST_Pos        (8U)
#define FSMC_BWTR1_DATAST_Msk        (0xFFUL << FSMC_BWTR1_DATAST_Pos)          /*!< 0x0000FF00 */
#define FSMC_BWTR1_DATAST            FSMC_BWTR1_DATAST_Msk                     /*!<DATAST [7:0] bits (Data-phase duration) */

#define FSMC_BWTR1_BUSTURN_Pos       (16U)
#define FSMC_BWTR1_BUSTURN_Msk       (0xFUL << FSMC_BWTR1_BUSTURN_Pos)          /*!< 0x000F0000 */
#define FSMC_BWTR1_BUSTURN           FSMC_BWTR1_BUSTURN_Msk                    /*!<BUSTURN[3:0] bits (Bus turnaround duration) */

#define FSMC_BWTR1_ACCMOD_Pos        (28U)
#define FSMC_BWTR1_ACCMOD_Msk        (0x3UL << FSMC_BWTR1_ACCMOD_Pos)           /*!< 0x30000000 */
#define FSMC_BWTR1_ACCMOD            FSMC_BWTR1_ACCMOD_Msk                     /*!<ACCMOD[1:0] bits (Access mode) */


/***************************** I2C FUNCTIONS *********************************/


static inline void I2C_Disable(I2C_TypeDef * I2Cx) {
	I2Cx->CR1 &= ~(0x1);
}

static inline void I2C_Enable(I2C_TypeDef * I2Cx) {
	I2Cx->CR1 |=  (0x1);
}

static inline void I2C_Set_Timing(I2C_TypeDef * I2Cx, uint32_t presc, uint32_t scldel, uint32_t sdadel, uint32_t sclh, uint32_t scll) {
	I2Cx->TIMINGR = (presc << 28) | (scldel << 20) | (sdadel << 16) | (sclh << 8) | (scll);
}

typedef enum {
    I2C_WRITE = 0U,
    I2C_READ  = 1U
} I2C_Direction;


static inline void I2C_Start(I2C_TypeDef *I2Cx, uint8_t slave_addr, I2C_Direction direction, uint32_t len) {
    uint32_t cr2 = 0;

    //Set 7-bit Slave Address (SADD[7:1])
    cr2 |= ((uint32_t)slave_addr << 1U) & 0xFEU;
    //Set Transfer Length (NBYTES[23:16])
    cr2 |= ((uint32_t)len << 16U);
    //Set Direction (RD_WRN bit 10: 0 = Write, 1 = Read)
    if (direction == I2C_READ)
        cr2 |= (1U << 10U);
    //Generate START Condition (START bit 13)
    cr2 |= (1U << 13U);

    // Apply configuration to hardware
    I2Cx->CR2 = cr2;
}
static inline void I2C_Write(I2C_TypeDef *I2Cx, uint8_t data) {
    // Wait for TXDR to be empty (TXIS == 0)
    while (!(I2Cx->ISR & (1U << 1U)));
    // Load byte into Transmit Data Register
    I2Cx->TXDR = data;
}

static inline uint8_t I2C_Read(I2C_TypeDef *I2Cx) {
    // Wait for RXNE (Receive Buffer Not Empty flag)
    while (!(I2Cx->ISR & (1U << 2U)));
    // Read byte from Receive Data Register
    return (uint8_t)(I2Cx->RXDR & 0xFFU);
}

static inline void I2C_Wait_TC(I2C_TypeDef *I2Cx) {
    // Wait for TC (Transfer Complete flag)
    while (!(I2Cx->ISR & (1U << 6U)));
}

static inline void I2C_Stop(I2C_TypeDef *I2Cx) {
    // Generate STOP condition (STOP bit 14 in CR2)
    I2Cx->CR2 |= (1U << 14U);
    // Wait for STOPF (Stop detection flag bit 5 in ISR)
    while (!(I2Cx->ISR & (1U << 5U)));
    // Clear STOPF flag by writing to ICR (STOPCF bit 5 in ICR)
    I2Cx->ICR |= (1U << 5U);
}

/* Writes 1 byte to a specific register inside the sensor */
void I2C_Reg_Write(I2C_TypeDef *I2Cx, uint8_t slave_addr, uint8_t reg, uint8_t val) {
    //Issue START + Address (Write Mode, expecting 2 bytes)
    I2C_Start(I2Cx, slave_addr, I2C_WRITE, 2);

    //Write Target Register Address
    I2C_Write(I2Cx, reg);

    //Write Value
    I2C_Write(I2Cx, val);

    //Wait for hardware to finish clocking out NBYTES (2 bytes)
	I2C_Wait_TC(I2Cx);

	//Manually issue STOP condition
	I2C_Stop(I2Cx);
}

/* Reads 'len' sequential bytes starting from 'reg' */
void I2C_Reg_Read_Seq(I2C_TypeDef *I2Cx, uint8_t slave_addr, uint8_t reg, uint8_t *dest, uint32_t len) {
    // ================= PHASE 1: WRITE REGISTER ADDRESS =================
    // Issue START + Slave Address (Write Mode, 1 Byte payload)
    I2C_Start(I2Cx, slave_addr, I2C_WRITE, 1);

    // Send the register address we want to read
    I2C_Write(I2Cx, reg);

    // Wait for write phase to complete before issuing Repeated START
    // for the READ operation
    I2C_Wait_TC(I2Cx);

    // ================= PHASE 2: READ DATA PAYLOAD =================
    // Issue REPEATED START + Slave Address (Read Mode, 'len' Bytes)
    I2C_Start(I2Cx, slave_addr, I2C_READ, len);

    // Read sequential bytes from the sensor
    for (uint32_t i = 0; i < len; i++)
        dest[i] = I2C_Read(I2Cx);

    // Wait for hardware to complete receiving all NBYTES
	I2C_Wait_TC(I2Cx);

	// Manually issue STOP condition
	I2C_Stop(I2Cx);
}






void delay(int loops) {
	for (int i = 0; i < loops; i++) {
		__asm("nop");
	}
}


#endif /* BSP_H_ */
