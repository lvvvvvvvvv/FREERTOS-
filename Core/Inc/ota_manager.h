#ifndef OTA_MANAGER_H
#define OTA_MANAGER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint32_t version;
    uint32_t image_size;
    uint32_t crc32;
    uint8_t signature[64];
} OtaImageHeader;

bool ota_manager_init(void);
bool ota_manager_start(const OtaImageHeader *header);
bool ota_manager_write_chunk(uint32_t offset, const uint8_t *data, uint16_t len);
bool ota_manager_finalize(void);
bool ota_manager_mark_boot_success(void);

#endif
