#ifndef GFX_H_
#define GFX_H_

#include <stdint.h>
#include <stdlib.h>
#include "ST7789h2.h"

/* Display dimensions */
#define GFX_WIDTH   240
#define GFX_HEIGHT  240

/* Basic Primitive Prototypes */
void GFX_DrawPixel(int16_t x, int16_t y, uint16_t color);
void GFX_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
void GFX_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);

/* Line Functions */
void GFX_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

/* Rectangle & Square Functions */
void GFX_DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void GFX_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void GFX_DrawSquare(int16_t x, int16_t y, int16_t size, uint16_t color);
void GFX_FillSquare(int16_t x, int16_t y, int16_t size, uint16_t color);

/* Circle Functions */
void GFX_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void GFX_FillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

/* Screen Fill */
void GFX_FillScreen(uint16_t color);

#endif /* GFX_H_ */