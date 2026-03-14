#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#define APP_CAN_HEARTBEAT_MS                (100U)
#define APP_RS485_POLL_MS                   (200U)
#define APP_AUTH_TIMEOUT_MS                 (30000U)
#define APP_PRECHARGE_TIMEOUT_MS            (8000U)
#define APP_CHARGE_MAX_TIMEOUT_MS           (8U * 60U * 60U * 1000U)

#define APP_TEMP_STOP_THRESHOLD_DEGC        (75)
#define APP_TEMP_RECOVER_THRESHOLD_DEGC     (65)

#define APP_OTA_SLOT_SIZE_BYTES             (512U * 1024U)
#define APP_OTA_HEADER_MAGIC                (0x43485247UL)

#endif
