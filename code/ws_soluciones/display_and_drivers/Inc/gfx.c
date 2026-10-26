#include "gfx.h"

/* Safe pixel draw with boundary checking */
void GFX_DrawPixel(int16_t x, int16_t y, uint16_t color) {
    if (x < 0 || x >= GFX_WIDTH || y < 0 || y >= GFX_HEIGHT) {
        return;
    }
    ST7789H2_WritePixel((uint16_t)x, (uint16_t)y, color);
}

/* Fast Horizontal Line */
void GFX_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    if (y < 0 || y >= GFX_HEIGHT || w <= 0) return;
    
    int16_t x2 = x + w - 1;
    if (x >= GFX_WIDTH || x2 < 0) return;
    
    if (x < 0) x = 0;
    if (x2 >= GFX_WIDTH) x2 = GFX_WIDTH - 1;

    for (int16_t i = x; i <= x2; i++) {
        ST7789H2_WritePixel((uint16_t)i, (uint16_t)y, color);
    }
}

/* Fast Vertical Line */
void GFX_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    if (x < 0 || x >= GFX_WIDTH || h <= 0) return;
    
    int16_t y2 = y + h - 1;
    if (y >= GFX_HEIGHT || y2 < 0) return;

    if (y < 0) y = 0;
    if (y2 >= GFX_HEIGHT) y2 = GFX_HEIGHT - 1;

    for (int16_t i = y; i <= y2; i++) {
        ST7789H2_WritePixel((uint16_t)x, (uint16_t)i, color);
    }
}

/* General Line Drawing using Bresenham's Line Algorithm */
void GFX_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    if (x0 == x1) {
        if (y0 > y1) { int16_t t = y0; y0 = y1; y1 = t; }
        GFX_DrawFastVLine(x0, y0, y1 - y0 + 1, color);
        return;
    }
    if (y0 == y1) {
        if (x0 > x1) { int16_t t = x0; x0 = x1; x1 = t; }
        GFX_DrawFastHLine(x0, y0, x1 - x0 + 1, color);
        return;
    }

    int16_t dx = abs(x1 - x0);
    int16_t dy = abs(y1 - y0);
    int16_t sx = (x0 < x1) ? 1 : -1;
    int16_t sy = (y0 < y1) ? 1 : -1;
    int16_t err = dx - dy;

    while (1) {
        GFX_DrawPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        
        int16_t e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

/* Outline Rectangle */
void GFX_DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    GFX_DrawFastHLine(x, y, w, color);
    GFX_DrawFastHLine(x, y + h - 1, w, color);
    GFX_DrawFastVLine(x, y, h, color);
    GFX_DrawFastVLine(x + w - 1, y, h, color);
}

/* Filled Rectangle */
void GFX_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    for (int16_t i = y; i < y + h; i++) {
        GFX_DrawFastHLine(x, i, w, color);
    }
}

/* Outline Square */
void GFX_DrawSquare(int16_t x, int16_t y, int16_t size, uint16_t color) {
    GFX_DrawRect(x, y, size, size, color);
}

/* Filled Square */
void GFX_FillSquare(int16_t x, int16_t y, int16_t size, uint16_t color) {
    GFX_FillRect(x, y, size, size, color);
}

/* Circle Outline using Midpoint Circle Algorithm */
void GFX_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    GFX_DrawPixel(x0, y0 + r, color);
    GFX_DrawPixel(x0, y0 - r, color);
    GFX_DrawPixel(x0 + r, y0, color);
    GFX_DrawPixel(x0 - r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        GFX_DrawPixel(x0 + x, y0 + y, color);
        GFX_DrawPixel(x0 - x, y0 + y, color);
        GFX_DrawPixel(x0 + x, y0 - y, color);
        GFX_DrawPixel(x0 - x, y0 - y, color);
        GFX_DrawPixel(x0 + y, y0 + x, color);
        GFX_DrawPixel(x0 - y, y0 + x, color);
        GFX_DrawPixel(x0 + y, y0 - x, color);
        GFX_DrawPixel(x0 - y, y0 - x, color);
    }
}

/* Filled Circle */
void GFX_FillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    GFX_DrawFastVLine(x0, y0 - r, 2 * r + 1, color);

    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        GFX_DrawFastVLine(x0 + x, y0 - y, 2 * y + 1, color);
        GFX_DrawFastVLine(x0 - x, y0 - y, 2 * y + 1, color);
        GFX_DrawFastVLine(x0 + y, y0 - x, 2 * x + 1, color);
        GFX_DrawFastVLine(x0 - y, y0 - x, 2 * x + 1, color);
    }
}

/* Fill Entire Screen */
void GFX_FillScreen(uint16_t color) {
    GFX_FillRect(0, 0, GFX_WIDTH, GFX_HEIGHT, color);
}