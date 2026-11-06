#include <ota.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <bsp.h>
#include <MQTTPacket.h>

extern uint32_t _app_start; // Imported from active linker script

static OTA_Context_t ota_ctx = {0};

// Accessor functions
OTA_State_t OTA_getState() {
	return ota_ctx.state;
}

/*********************** TARGET ADDRESS RESOLVER *******************************/
uint32_t OTA_GetTargetAddress(void) {
    return ((uint32_t)&_app_start == FLASH_SLOT_A_ADDR) ? FLASH_SLOT_B_ADDR : FLASH_SLOT_A_ADDR;
}

/*********************** ERASE INACTIVE SLOT *******************************/
void OTA_EraseTargetSlot(void)
{
    uint32_t target_addr = OTA_GetTargetAddress();

    if (target_addr == FLASH_SLOT_B_ADDR) {
    	Debug_Printf("[OTA] Erasing Slot B (0x08040000)...\r\n");
    	Flash_EraseSector(6);
    	Flash_EraseSector(7);
    } else {
    	Debug_Printf("[OTA] Erasing Slot A (0x08000000)...\r\n");
    	Flash_EraseSector(0);
    	Flash_EraseSector(1);
    	Flash_EraseSector(2);
    	Flash_EraseSector(3);
    	Flash_EraseSector(4);
    	Flash_EraseSector(5);
    }

    Debug_Printf("[OTA] Target Slot Erased!\r\n");
}

/*********************** WRITE CHUNK AND PROCESS NEXT IF NEEDED ***********/

void OTA_WriteChunkAndProcess(uint8_t *data, uint16_t length) {
	OTA_WriteChunk(ota_ctx.bytes_downloaded, data, length);
	ota_ctx.bytes_downloaded += length;
	ota_ctx.current_chunk++;

	Debug_Printf("[OTA RX] Chunk %u (%d bytes) -> Total: %lu / %lu\r\n",
				 ota_ctx.current_chunk, length, ota_ctx.bytes_downloaded, ota_ctx.total_size);

	if (ota_ctx.bytes_downloaded < ota_ctx.total_size) {
		OTA_RequestNextChunk();
	} else {
		Debug_Printf("[OTA SUCCESS] Download Finished! Rebooting...\r\n");
		ota_ctx.state = OTA_STATE_COMPLETE;
		OTA_SwapBootSlotAndReset();
	}
}

/*********************** WRITE BINARY CHUNK *******************************/
void OTA_WriteChunk(uint32_t offset, uint8_t *data, uint16_t length)
{
    uint32_t write_addr = OTA_GetTargetAddress() + offset;

	Flash_Unlock();
	Flash_ClearErrors();
    for (uint16_t i = 0; i < length; i++) {
    	Flash_WriteByteRaw(write_addr + i, data[i]);
    }
    Flash_Lock();
}


/*********************** BOOT SWAP & SYSTEM RESET *******************************/
void OTA_SwapBootSlotAndReset(void)
{
    uint32_t target_addr = OTA_GetTargetAddress();
    // BOOT_ADD0 expects the flash address divided by 16KB (shifted right by 14 bits)
    uint16_t boot_val = (uint16_t)(target_addr >> 14);

    Debug_Printf("[OTA] Swapping BOOT_ADD0 to 0x%08X (val: 0x%04X) and resetting...\r\n",
                 target_addr, boot_val);
    Delay_ms(500);

    Flash_Unlock(); // Uses bsp.h helper
    Flash_Unlock_Opt();
    Flash_WaitNotBusy(); // Uses bsp.h helper

    //update target boot address
    Flash_Update_Opt(boot_val);

    Flash_WaitNotBusy();
    Flash_Lock_Opt();
    Flash_Lock(); // Uses bsp.h helper

    // Force system reset after Data Syncrhonization Barrier
    // (to flush pending mem stores)
    __DSB();
    SCB->AIRCR = (0x05FA0000U) | (1U << 2); // VECTKEY (0x05FA) + SYSRESETREQ (Bit 2)

    while (1); // Wait for hardware reset
}

/*********************** MQTT CHUNK REQUEST *******************************/
void OTA_RequestNextChunk(void)
{
    uint8_t buf[128];
    char topic[64];
    char payload[16];

    snprintf(topic, sizeof(topic), "v2/fw/request/1/chunk/%u", ota_ctx.current_chunk);
    snprintf(payload, sizeof(payload), "%d", OTA_CHUNK_SIZE);

    MQTTString topicString = MQTTString_initializer;
    topicString.cstring = topic;

    int len = MQTTSerialize_publish(buf, sizeof(buf), 0, 0, 0, 0,
                                    topicString, (unsigned char *)payload, strlen(payload));
    UART_WriteBytes(UART5, buf, len);
}

/*********************** ATTRIBUTE / OTA PARSER *******************************/
void OTA_ProcessJSON(const char *json) {
    char *ver_ptr = strstr(json, "\"fw_version\":");
    char *size_ptr = strstr(json, "\"fw_size\":");

    if (ver_ptr && size_ptr && ota_ctx.state == OTA_STATE_IDLE) {
        char new_version[32] = {0};
        sscanf(ver_ptr, "\"fw_version\":\"%31[^\"]\"", new_version);
        uint32_t new_size = (uint32_t)atoi(size_ptr + 10);

    	// Determine what binary suffix this device requires
    	const char *required_suffix = ((uint32_t)&_app_start == FLASH_SLOT_A_ADDR) ? "B" : "A";

    	// Reject the update if the incoming version tag doesn't match the inactive slot
    	if (strstr(new_version, required_suffix) == NULL) {
    	    Debug_Printf("[OTA] Rejected update %s! Device is running in Slot %c and requires %s binary.\r\n",
    	                 new_version,
    	                 ((uint32_t)&_app_start == FLASH_SLOT_A_ADDR) ? 'A' : 'B',
    	                 required_suffix);
    	    return;
    	}

        // Verify if version differs from running app
        if (strcmp(new_version, CURRENT_FW_VERSION) != 0 && new_size > 0) {
            Debug_Printf("[OTA] New Version Found: %s (Size: %lu bytes)\r\n", new_version, new_size);

            ota_ctx.state = OTA_STATE_DOWNLOADING;
            ota_ctx.total_size = new_size;
            ota_ctx.bytes_downloaded = 0;
            ota_ctx.current_chunk = 0;
            strncpy(ota_ctx.target_version, new_version, sizeof(ota_ctx.target_version));

            OTA_EraseTargetSlot();
            OTA_RequestNextChunk();
        }
    }
}

