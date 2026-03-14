#include "ota_manager.h"
#include "app_config.h"

static OtaImageHeader s_pending_header;
static bool s_has_pending_image = false;

bool ota_manager_init(void)
{
    s_has_pending_image = false;
    return true;
}

bool ota_manager_start(const OtaImageHeader *header)
{
    if (header == 0 || header->image_size > APP_OTA_SLOT_SIZE_BYTES) {
        return false;
    }

    s_pending_header = *header;
    s_has_pending_image = true;
    return true;
}

bool ota_manager_write_chunk(uint32_t offset, const uint8_t *data, uint16_t len)
{
    (void)data;

    if (!s_has_pending_image) {
        return false;
    }

    return (offset + len) <= s_pending_header.image_size;
}

bool ota_manager_finalize(void)
{
    return s_has_pending_image;
}

bool ota_manager_mark_boot_success(void)
{
    s_has_pending_image = false;
    return true;
}
