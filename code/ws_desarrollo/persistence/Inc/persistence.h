/*
 * persistence.h
 *
 *  Created on: Aug 27, 2026
 *      Author: dani
 */

#ifndef PERSISTENCE_H_
#define PERSISTENCE_H_

#define FLASH_SECTOR_NUM    7U                  // Sector 7 (safe upper Flash sector)
#define FLASH_STORAGE_ADDR  0x08060000U         // Base address of Sector 7
#define FLASH_MAGIC_KEY     0xCAFEBABEU         // Marker to verify stored data validity

typedef struct {
    uint32_t magic;
    uint16_t x;
    uint16_t y;
} FlashTouchData;

/* Erases Sector 7 and writes the magic key + touch coordinates */
void Flash_SaveTouch(uint16_t x, uint16_t y) {
    FlashTouchData data = {
        .magic = FLASH_MAGIC_KEY,
        .x = x,
        .y = y
    };

    Flash_EraseSector(FLASH_SECTOR_NUM);

    uint8_t *pData = (uint8_t *)&data;
    for (uint32_t i = 0; i < sizeof(FlashTouchData); i++) {
        Flash_WriteByte(FLASH_STORAGE_ADDR + i, pData[i]);
    }

}

/* Reads coordinates from Flash if a valid magic key is present */
uint8_t Flash_ReadTouch(uint16_t *x, uint16_t *y) {
    // ... completar conseguir un puntero de tipo FlashTouchData
    // ... a la dirección base para poder leerla

    // ... si encontramos la MAGIC KEY, devolver 1
    // ... además de rellenar los valores x, y
    // ... de lo contrario, devolver 0 (Flash vacía)
}

#endif /* PERSISTENCE_H_ */
