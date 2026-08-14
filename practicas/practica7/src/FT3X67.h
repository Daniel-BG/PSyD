/*
 * FT3X67.h
 *
 *  Created on: Aug 11, 2026
 *      Author: dani
 */

#ifndef FT3X67_H_
#define FT3X67_H_

#define TS_I2C_7BIT_ADDR 0x38
#define FT_REG_TD_STATUS 0x02

typedef struct {
    uint16_t x;
    uint16_t y;
    uint8_t  touch_detected;
} TS_State_t;

/**
  * @brief  Reads the current touch coordinates from the FT3X67.
  * @param  ts: Pointer to TS_State_t structure to store parsed coordinates
  * @return 1 if touch is valid, 0 otherwise
  */
uint8_t FT3X67_GetTouchCoordinates(TS_State_t *ts) {
    uint8_t buffer[5];

    /* Read 5 consecutive registers starting at TD_STATUS (0x02 to 0x06) */
    I2C_Reg_Read_Seq(I2C3, TS_I2C_7BIT_ADDR, FT_REG_TD_STATUS, buffer, 5);

    uint8_t num_touches = buffer[0] & 0x0F;

    if (num_touches > 0 && num_touches <= 5) {
        /* Parse 12-bit X coordinate from registers 0x03 and 0x04 */
        ts->x = ((uint16_t)(buffer[1] & 0x0F) << 8) | buffer[2];

        /* Parse 12-bit Y coordinate from registers 0x05 and 0x06 */
        ts->y = ((uint16_t)(buffer[3] & 0x0F) << 8) | buffer[4];

        ts->touch_detected = 1;
        return 1;
    }

    ts->touch_detected = 0;
    return 0;
}

#endif /* FT3X67_H_ */
