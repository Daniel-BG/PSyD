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

//RCC (Reset and clock control)
#define RCC_AHB1EN_BASE_ADDR 0x40023830




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

//Structure for Reset and Clock Control peripheral clock register 1
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
} RCC_AHB_ENR_TypeDef;




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

#define RCC_AHB1ENR 		((RCC_AHB_ENR_TypeDef *) RCC_AHB1EN_BASE_ADDR)



/*************************************************************
 * MACROS
 ************************************************************/

static inline void _GPIO_REG_SET(volatile uint32_t *reg_ptr, uint32_t pin, uint32_t mask, uint32_t value, uint32_t shift_mult) {
    uint32_t temp = *reg_ptr;
    temp &= ~(mask << (pin * shift_mult));
    temp |= (value << (pin * shift_mult));
    *reg_ptr = temp;
}


/*************************************************************
 * API FUNCTIONS
 ************************************************************/

//GPIO MODE SET
typedef enum {
    GPIO_MODE_INPUT  = 0x00,
    GPIO_MODE_OUTPUT = 0x01,
    GPIO_MODE_ALT    = 0x02,
    GPIO_MODE_ANALOG = 0x03
} GPIO_Mode_t;

static inline void GPIO_MODE_SET(volatile GPIO_TypeDef *GPIOx, uint32_t pin, GPIO_Mode_t mode) {
    _GPIO_REG_SET(&(GPIOx)->MODER, pin, 0x03, (uint32_t)mode, 2);
}

//GPIO OUTPUT TYPE SET
typedef enum {
    GPIO_OTYPE_PP = 0x00,
    GPIO_OTYPE_OD = 0x01
} GPIO_OType_t;

static inline void GPIO_OTYPE_SET(volatile GPIO_TypeDef *GPIOx, uint32_t pin, GPIO_OType_t otype) {
    _GPIO_REG_SET(&(GPIOx)->OTYPER, pin, 0x01, (uint32_t)otype, 1);
}

//GPIO OUTPUT SPEED SET
typedef enum {
    GPIO_OSPEED_LOW    = 0x00,
    GPIO_OSPEED_MEDIUM = 0x01,
    GPIO_OSPEED_HIGH   = 0x02,
    GPIO_OSPEED_VHIGH  = 0x03
} GPIO_OSpeed_t;

static inline void GPIO_OSPEED_SET(volatile GPIO_TypeDef *GPIOx, uint32_t pin, GPIO_OSpeed_t ospeed) {
    _GPIO_REG_SET(&(GPIOx)->OSPEEDR, pin, 0x03, (uint32_t)ospeed, 2);
}

//GPIO PULLUP/DOWN SET
typedef enum {
    GPIO_PUPD_NONE = 0x00,
    GPIO_PUPD_PU   = 0x01,
    GPIO_PUPD_PD   = 0x02
} GPIO_PuPd_t;

static inline void GPIO_PUPD_SET(volatile GPIO_TypeDef *GPIOx, uint32_t pin, GPIO_PuPd_t pupd) {
    _GPIO_REG_SET(&(GPIOx)->PUPDR, pin, 0x03, (uint32_t)pupd, 2);
}

//ATOMIC GPIO WRITE VIA BSRR
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

//GPIO READ
static inline uint32_t GPIO_PIN_READ(volatile GPIO_TypeDef *GPIOx, uint32_t pin) {
    return (GPIOx->IDR >> pin) & 0x01;
}





void delay(int loops) {
	for (int i = 0; i < loops; i++) {
		__asm("nop");
	}
}


#endif /* BSP_H_ */
