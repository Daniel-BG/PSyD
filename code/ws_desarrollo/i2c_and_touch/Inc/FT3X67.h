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
    // ... completar leer utilizando I2C_Reg_Read_Seq 5 bytes

    uint8_t num_touches = buffer[0] & 0x0F;

    if (num_touches > 0 && num_touches <= 2) {
        // ... completar parsear coordenadas en ts->x y ts->y

        ts->touch_detected = 1;
        return 1;
    }

    ts->touch_detected = 0;
    return 0;
}

#endif /* FT3X67_H_ */
