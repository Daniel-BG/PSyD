#include <ST7789h2.h>




void ST7789H2_WriteReg(uint8_t Command, uint8_t *Parameters, uint8_t NbParameters)
{
	uint8_t   i;

	/* Send command */
	FMC_BANK2_WriteReg(Command);

	/* Send command's parameters if any */
	for (i=0; i<NbParameters; i++)
	{
		FMC_BANK2_WriteData(Parameters[i]);
	}
}

/**
  * @brief  Set Cursor position.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @retval None
  */
void ST7789H2_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
	uint8_t   parameter[4];
	/* CASET: Column Address Set */
	parameter[0] = 0x00;
	parameter[1] = 0x00 + Xpos;
	parameter[2] = 0x00;
	parameter[3] = 0xEF + Xpos;
	ST7789H2_WriteReg(ST7789H2_CASET, parameter, 4);
	/* RASET: Row Address Set */
	parameter[0] = 0x00;
	parameter[1] = 0x00 + Ypos;
	parameter[2] = 0x00;
	parameter[3] = 0xEF + Ypos;
	ST7789H2_WriteReg(ST7789H2_RASET, parameter, 4);
}

/**
  * @brief  Enables the Display.
  * @param  None
  * @retval None
  */
void ST7789H2_DisplayOn(void)
{

	// ... completar enviar comando DISPLAY ON y luego SLEEP OUT

}

/**
  * @brief  Write pixel.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  RGBCode: the RGB pixel color in RGB565 format
  * @retval None
  */
void ST7789H2_WritePixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode)
{
  /* Set Cursor */
	ST7789H2_SetCursor(Xpos, Ypos);

  /* Prepare to write to LCD RAM */
	ST7789H2_WriteReg(ST7789H2_WRITE_RAM, (uint8_t*)NULL, 0);   /* RAM write data command */

  /* Write RAM data */
	FMC_BANK2_WriteData(RGBCode);
}

/*
 * Initialize the ST7789H2
 */
void ST7789H2_INIT() {
	uint8_t   parameter[14];
	/* Initialize st7789h2 low level bus layer ----------------------------------*/
	/* Sleep In Command */
	ST7789H2_WriteReg(ST7789H2_SLEEP_IN, (uint8_t*)NULL, 0);
	/* Wait for 10ms */
	Delay_ms(10);

	//... completar mandar comando de RESET y de SLEEP_OUT con sus correspondientes delays


	/* Normal display for Driver Down side */
	parameter[0] = 0x00;
	ST7789H2_WriteReg(ST7789H2_NORMAL_DISPLAY, parameter, 1);

	/* Color mode 16bits/pixel */
	parameter[0] = 0x05;
	ST7789H2_WriteReg(ST7789H2_COLOR_MODE, parameter, 1);

	/* Display inversion On */
	ST7789H2_WriteReg(ST7789H2_DISPLAY_INVERSION, (uint8_t*)NULL, 0);

	/* Set Column address CASET */
	parameter[0] = 0x00;
	parameter[1] = 0x00;
	parameter[2] = 0x00;
	parameter[3] = 0xEF;
	ST7789H2_WriteReg(ST7789H2_CASET, parameter, 4);
	/* Set Row address RASET */
	parameter[0] = 0x00;
	parameter[1] = 0x00;
	parameter[2] = 0x00;
	parameter[3] = 0xEF;
	ST7789H2_WriteReg(ST7789H2_RASET, parameter, 4);

	/*--------------- ST7789H2 Frame rate setting -------------------------------*/
	/* PORCH control setting */
	parameter[0] = 0x0C;
	parameter[1] = 0x0C;
	parameter[2] = 0x00;
	parameter[3] = 0x33;
	parameter[4] = 0x33;
	ST7789H2_WriteReg(ST7789H2_PORCH_CTRL, parameter, 5);

	/* GATE control setting */
	parameter[0] = 0x35;
	ST7789H2_WriteReg(ST7789H2_GATE_CTRL, parameter, 1);

	/*--------------- ST7789H2 Power setting ------------------------------------*/
	/* VCOM setting */
	parameter[0] = 0x1F;
	ST7789H2_WriteReg(ST7789H2_VCOM_SET, parameter, 1);

	/* LCM Control setting */
	parameter[0] = 0x2C;
	ST7789H2_WriteReg(ST7789H2_LCM_CTRL, parameter, 1);

	/* VDV and VRH Command Enable */
	parameter[0] = 0x01;
	parameter[1] = 0xC3;
	ST7789H2_WriteReg(ST7789H2_VDV_VRH_EN, parameter, 2);

	/* VDV Set */
	parameter[0] = 0x20;
	ST7789H2_WriteReg(ST7789H2_VDV_SET, parameter, 1);

	/* Frame Rate Control in normal mode */
	parameter[0] = 0x0F;
	ST7789H2_WriteReg(ST7789H2_FR_CTRL, parameter, 1);

	/* Power Control */
	parameter[0] = 0xA4;
	parameter[1] = 0xA1;
	ST7789H2_WriteReg(ST7789H2_POWER_CTRL, parameter, 1);

	/*--------------- ST7789H2 Gamma setting ------------------------------------*/
	/* Positive Voltage Gamma Control */
	parameter[0] = 0xD0;
	parameter[1] = 0x08;
	parameter[2] = 0x11;
	parameter[3] = 0x08;
	parameter[4] = 0x0C;
	parameter[5] = 0x15;
	parameter[6] = 0x39;
	parameter[7] = 0x33;
	parameter[8] = 0x50;
	parameter[9] = 0x36;
	parameter[10] = 0x13;
	parameter[11] = 0x14;
	parameter[12] = 0x29;
	parameter[13] = 0x2D;
	ST7789H2_WriteReg(ST7789H2_PV_GAMMA_CTRL, parameter, 14);

	/* Negative Voltage Gamma Control */
	parameter[0] = 0xD0;
	parameter[1] = 0x08;
	parameter[2] = 0x10;
	parameter[3] = 0x08;
	parameter[4] = 0x06;
	parameter[5] = 0x06;
	parameter[6] = 0x39;
	parameter[7] = 0x44;
	parameter[8] = 0x51;
	parameter[9] = 0x0B;
	parameter[10] = 0x16;
	parameter[11] = 0x14;
	parameter[12] = 0x2F;
	parameter[13] = 0x31;
	ST7789H2_WriteReg(ST7789H2_NV_GAMMA_CTRL, parameter, 14);

	/* Display ON command */
	ST7789H2_DisplayOn();

	/* Tearing Effect Line On: Option (00h:VSYNC Interface OFF, 01h:VSYNC Interface ON) */
	parameter[0] = 0x00;
	ST7789H2_WriteReg(ST7789H2_TEARING_EFFECT, parameter, 1);
}