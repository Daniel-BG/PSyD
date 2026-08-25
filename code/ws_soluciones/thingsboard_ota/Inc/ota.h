#ifndef OTA_H_
#define OTA_H_

#include <stdint.h>

#define CURRENT_FW_VERSION "1.0.0"
#define FLASH_SLOT_A_ADDR   0x08000000U
#define FLASH_SLOT_B_ADDR   0x08040000U
#define OTA_CHUNK_SIZE      512 // 512B chunk size to avoid UART buffer overflows

typedef enum {
    OTA_STATE_IDLE,
    OTA_STATE_DOWNLOADING,
    OTA_STATE_COMPLETE
} OTA_State_t;

typedef struct {
    OTA_State_t state;
    char target_version[32];
    uint32_t total_size;
    uint32_t bytes_downloaded;
    uint16_t current_chunk;
} OTA_Context_t;

OTA_State_t OTA_getState();

uint32_t OTA_GetTargetAddress(void);
void OTA_EraseTargetSlot(void);
void OTA_WriteChunkAndProcess(uint8_t *data, uint16_t length);
void OTA_WriteChunk(uint32_t offset, uint8_t *data, uint16_t length);
void OTA_SwapBootSlotAndReset(void);
void OTA_RequestNextChunk(void);
void OTA_ProcessJSON(const char *json);


#endif /* OTA_H_ */
