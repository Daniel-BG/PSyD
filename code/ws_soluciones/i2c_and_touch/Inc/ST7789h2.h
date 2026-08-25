/*
 * ST7789h2.h
 *
 *  Created on: Jul 14, 2026
 *      Author: dani
 */

#include <bsp.h>
#include <stddef.h>

#ifndef ST7789H2_H_
#define ST7789H2_H_



/**
  * @brief  ST7789H2 Registers
  */
#define ST7789H2_RESET				0x01
#define ST7789H2_LCD_ID             0x04
#define ST7789H2_SLEEP_IN           0x10
#define ST7789H2_SLEEP_OUT          0x11
#define ST7789H2_PARTIAL_DISPLAY    0x12
#define ST7789H2_DISPLAY_INVERSION  0x21
#define ST7789H2_DISPLAY_ON         0x29
#define ST7789H2_WRITE_RAM          0x2C
#define ST7789H2_READ_RAM           0x2E
#define ST7789H2_CASET              0x2A
#define ST7789H2_RASET              0x2B
#define ST7789H2_VSCRDEF            0x33 /* Vertical Scroll Definition */
#define ST7789H2_VSCSAD             0x37 /* Vertical Scroll Start Address of RAM */
#define ST7789H2_TEARING_EFFECT     0x35
#define ST7789H2_NORMAL_DISPLAY     0x36
#define ST7789H2_IDLE_MODE_OFF      0x38
#define ST7789H2_IDLE_MODE_ON       0x39
#define ST7789H2_COLOR_MODE         0x3A
#define ST7789H2_WRCABCMB           0x5E /* Write Content Adaptive Brightness Control */
#define ST7789H2_RDCABCMB           0x5F /* Read Content Adaptive Brightness Control */
#define ST7789H2_PORCH_CTRL         0xB2
#define ST7789H2_GATE_CTRL          0xB7
#define ST7789H2_VCOM_SET           0xBB
#define ST7789H2_DISPLAY_OFF        0xBD
#define ST7789H2_LCM_CTRL           0xC0
#define ST7789H2_VDV_VRH_EN         0xC2
#define ST7789H2_VDV_SET            0xC4
#define ST7789H2_VCOMH_OFFSET_SET   0xC5
#define ST7789H2_FR_CTRL            0xC6
#define ST7789H2_POWER_CTRL         0xD0
#define ST7789H2_PV_GAMMA_CTRL      0xE0
#define ST7789H2_NV_GAMMA_CTRL      0xE1


#define LCD_COLOR_BLUE          ((uint16_t)0x001F)
#define LCD_COLOR_GREEN         ((uint16_t)0x07E0)
#define LCD_COLOR_RED           ((uint16_t)0xF800)
#define LCD_COLOR_CYAN          ((uint16_t)0x07FF)
#define LCD_COLOR_MAGENTA       ((uint16_t)0xF81F)
#define LCD_COLOR_YELLOW        ((uint16_t)0xFFE0)
#define LCD_COLOR_LIGHTBLUE     ((uint16_t)0x841F)
#define LCD_COLOR_LIGHTGREEN    ((uint16_t)0x87F0)
#define LCD_COLOR_LIGHTRED      ((uint16_t)0xFC10)
#define LCD_COLOR_LIGHTMAGENTA  ((uint16_t)0xFC1F)
#define LCD_COLOR_LIGHTYELLOW   ((uint16_t)0xFFF0)
#define LCD_COLOR_DARKBLUE      ((uint16_t)0x0010)
#define LCD_COLOR_DARKGREEN     ((uint16_t)0x0400)
#define LCD_COLOR_DARKRED       ((uint16_t)0x8000)
#define LCD_COLOR_DARKCYAN      ((uint16_t)0x0410)
#define LCD_COLOR_DARKMAGENTA   ((uint16_t)0x8010)
#define LCD_COLOR_DARKYELLOW    ((uint16_t)0x8400)
#define LCD_COLOR_WHITE         ((uint16_t)0xFFFF)
#define LCD_COLOR_LIGHTGRAY     ((uint16_t)0xD69A)
#define LCD_COLOR_GRAY          ((uint16_t)0x8410)
#define LCD_COLOR_DARKGRAY      ((uint16_t)0x4208)
#define LCD_COLOR_BLACK         ((uint16_t)0x0000)
#define LCD_COLOR_BROWN         ((uint16_t)0xA145)
#define LCD_COLOR_ORANGE        ((uint16_t)0xFD20)


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
	/* CASET: Comumn Addrses Set */
	parameter[0] = 0x00;
	parameter[1] = 0x00 + Xpos;
	parameter[2] = 0x00;
	parameter[3] = 0xEF + Xpos;
	ST7789H2_WriteReg(ST7789H2_CASET, parameter, 4);
	/* RASET: Row Addrses Set */
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
	/* Display ON command */
	ST7789H2_WriteReg(ST7789H2_DISPLAY_ON, (uint8_t*)NULL, 0);

	/* Sleep Out command */
	ST7789H2_WriteReg(ST7789H2_SLEEP_OUT, (uint8_t*)NULL, 0);
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
	DELAY(10);

	/* SW Reset Command */
	ST7789H2_WriteReg(ST7789H2_RESET, (uint8_t*)NULL, 0);
	/* Wait for 200ms */
	DELAY(200);

	/* Sleep Out Command */
	ST7789H2_WriteReg(ST7789H2_SLEEP_OUT, (uint8_t*)NULL, 0);
	/* Wait for 120ms */
	DELAY(120);

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

#endif /* ST7789H2_H_ */
