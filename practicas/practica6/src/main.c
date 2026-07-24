
/* Includes ------------------------------------------------------------------*/
#include <bsp.h>
#include <ST7789h2.h>

void LCD_Pins_Init() {
	/* Initialize LCD special pins GPIOs */
	/* LCD_RESET GPIO configuration */
	RCC_AHB1ENR->bits.GPIOHEN = 1;
	GPIO_CONFIG(GPIOH, 7, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PUPD_NONE, 0);
	/* LCD_TE GPIO configuration */
	RCC_AHB1ENR->bits.GPIOCEN = 1;
	GPIO_CONFIG(GPIOC, 8, GPIO_MODE_INPUT, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO_PUPD_NONE, 0);
	/* LCD_BL_CTRL GPIO configuration */
	RCC_AHB1ENR->bits.GPIOHEN = 1;
	GPIO_CONFIG(GPIOH, 11, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_OSPEED_LOW, GPIO_PUPD_NONE, 0);
}

void LCD_Startup_Seq() {
	/* Backlight control signal assertion */
	GPIO_PIN_WRITE(GPIOH, 11, GPIO_STATE_ONE);

	/* Apply hardware reset according to procedure indicated in FRD154BP2901 documentation */
	GPIO_PIN_WRITE(GPIOH, 7, GPIO_STATE_ZERO);
	DELAY(5);   /* Reset signal asserted during 5ms  */
	GPIO_PIN_WRITE(GPIOH, 7, GPIO_STATE_ONE);
	DELAY(10);  /* Reset signal released during 10ms */
	GPIO_PIN_WRITE(GPIOH, 7, GPIO_STATE_ZERO);
	DELAY(20);  /* Reset signal asserted during 20ms */
	GPIO_PIN_WRITE(GPIOH, 7, GPIO_STATE_ONE);
	DELAY(10);  /* Reset signal released during 10ms */
}

void LCD_Init() {
	LCD_Pins_Init();
	LCD_Startup_Seq();
}


void FSMC_Pins_Init() {
	/* Initialize the SRAM controller */
	/* Enable FMC clock */
	RCC_AHB3ENR->bits.FMCEN = 1;
	/* Enable FSMC clock */
	RCC_AHB3ENR->bits.FMCEN = 1;
	RCC_AHB3RSTR->bits.FMCEN = 1;
	RCC_AHB3RSTR->bits.FMCEN = 0;

	/* Enable GPIOS for FSM */
	/*
	 	FMC pins -> PD10, PD9, PD8, PE15, PE14, PE13, PE12, PE11, PE10, PE9, PE8, PE7, PD1, PD0, PD15, PD14
		FMC NOE, NWE - > PD4, PD5
		FMC RS -> PF0
		FMC NCS -> PG9
	 */
	RCC_AHB1ENR->bits.GPIODEN = 1;
	uint8_t pins_d [9] = {0, 1, 4, 5, 8, 9, 10, 14, 15};
	for (int i = 0; i < 9; i++)
		GPIO_CONFIG(GPIOD, pins_d[i], GPIO_MODE_ALT, GPIO_OTYPE_PP, GPIO_OSPEED_VHIGH, GPIO_PUPD_PU, GPIO_AF12_FSMC);
	RCC_AHB1ENR->bits.GPIOEEN = 1;
	uint8_t pins_e [9] = {7, 8, 9, 10, 11, 12, 13, 14, 15};
	for (int i = 0; i < 9; i++)
		GPIO_CONFIG(GPIOE, pins_e[i], GPIO_MODE_ALT, GPIO_OTYPE_PP, GPIO_OSPEED_VHIGH, GPIO_PUPD_PU, GPIO_AF12_FSMC);
	RCC_AHB1ENR->bits.GPIOFEN = 1;
	GPIO_CONFIG(GPIOF, 0, GPIO_MODE_ALT, GPIO_OTYPE_PP, GPIO_OSPEED_VHIGH, GPIO_PUPD_PU, GPIO_AF12_FSMC);
	RCC_AHB1ENR->bits.GPIOGEN = 1;
	GPIO_CONFIG(GPIOG, 9, GPIO_MODE_ALT, GPIO_OTYPE_PP, GPIO_OSPEED_VHIGH, GPIO_PUPD_PU, GPIO_AF12_FSMC);
}

void FSMC_Reg_Config() {
	/* Initialize SRAM control Interface */
	/* Disable NORSRAM Device */
	FSMC_NORSRAM_DISABLE(FMC, 2);

	/* Set NORSRAM device control parameters */
	_REGISTER_SET(&(FMC->BCR2),
		FSMC_BCR1_MBKEN                | FSMC_BCR1_MUXEN                | FSMC_BCR1_MTYP                 | FSMC_BCR1_MWID                 |
		FSMC_BCR1_FACCEN               | FSMC_BCR1_BURSTEN              | FSMC_BCR1_WAITPOL              | FSMC_BCR1_WAITCFG              |
		FSMC_BCR1_WREN                 | FSMC_BCR1_WAITEN               | FSMC_BCR1_EXTMOD               | FSMC_BCR1_ASYNCWAIT            |
		FSMC_BCR1_CCLKEN			   | FSMC_BCR1_WFDIS				| FSMC_BCR1_CPSIZE				 | FSMC_BCR1_CBURSTRW
		,
										 FSMC_DATA_ADDRESS_MUX_DISABLE  | FSMC_MEMORY_TYPE_SRAM          | FSMC_NORSRAM_MEM_BUS_WIDTH_16  |
		FSMC_NORSRAM_FLASH_ACCESS_DIS  | FSMC_BURST_ACCESS_MODE_DISABLE | FSMC_WAIT_SIGNAL_POLARITY_LOW  | FSMC_WAIT_TIMING_BEFORE_WS     |
		FSMC_WRITE_OPERATION_ENABLE    | FSMC_WAIT_SIGNAL_DISABLE       | FSMC_EXTENDED_MODE_DISABLE      | FSMC_ASYNCHRONOUS_WAIT_DISABLE |
		FSMC_CONTINUOUS_CLOCK_SYNC_ONLY| FSMC_WRITE_FIFO_DISABLE		| FSMC_PAGE_SIZE_NONE 			 | FSMC_WRITE_BURST_DISABLE
	, 0);

	_REGISTER_SET(&(FMC->BCR1), FSMC_BCR1_WFDIS, FSMC_WRITE_FIFO_DISABLE, 0);

	/* Initialize SRAM timing Interface */
	/* Set FSMC_NORSRAM device timing parameters */
	_REGISTER_SET(&(FMC->BTR2),
			FSMC_BTR1_ADDSET | FSMC_BTR1_ADDHLD  | FSMC_BTR1_DATAST | FSMC_BTR1_BUSTURN |
			FSMC_BTR1_CLKDIV | FSMC_BTR1_DATLAT  | FSMC_BTR1_ACCMOD
			,
			(9										| //AddressSetupTime
			((2)       	<< FSMC_BTR1_ADDHLD_Pos)  	| //AddressHoldTime
			((6)        << FSMC_BTR1_DATAST_Pos)  	| //DataSetupTime
			((1)  		<< FSMC_BTR1_BUSTURN_Pos) 	| //BusTurnAroundDuration
			(((2) - 1U) << FSMC_BTR1_CLKDIV_Pos)  	| //CLKDivision
			(((2) - 2U) << FSMC_BTR1_DATLAT_Pos)  	| //DataLatency
			(FSMC_ACCESS_MODE_A))					  //AccessMode
	, 0);

	/* Enable the NORSRAM device */
	FSMC_NORSRAM_ENABLE(FMC, 2);
}


void FSMC_Init() {
	FSMC_Pins_Init();
	FSMC_Reg_Config();
}

/* Private function prototypes -----------------------------------------------*/

// Definimos una variable global para la semilla (debe ser distinta de 0)
static uint32_t estado_rng = 123456789;

// Genera un entero sin signo de 32 bits (0 a 4,294,967,295)
uint32_t rand32(void) {
    uint32_t x = estado_rng;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return estado_rng = x;
}

int main(void)
{
	LCD_Init();
	FSMC_Init();
	ST7789H2_INIT();

	/* Clear the LCD */
	for (int i = 0; i < 240; i++)
		for (int j = 0; j < 240; j++)
			ST7789H2_WritePixel(i, j, LCD_COLOR_WHITE);


	for (int i = 50; i < 60; i++)
		for (int j = 50; j < 60; j++)
			ST7789H2_WritePixel(i, j, LCD_COLOR_RED);


	while(1)
	{
		uint32_t rnd = rand32();
		ST7789H2_WritePixel((rnd >> 24) & 0xff, (rnd >> 16) & 0xff, rnd & 0xffff);
	}
}
