#ifndef CHARGER_TYPES_H
#define CHARGER_TYPES_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    CHG_STATE_IDLE = 0,
    CHG_STATE_PLUG_DETECTED,
    CHG_STATE_AUTH_PENDING,
    CHG_STATE_PRECHARGE,
    CHG_STATE_CHARGING,
    CHG_STATE_STOPPING,
    CHG_STATE_BILLING,
    CHG_STATE_FAULT
} ChargerState;

typedef enum {
    CHG_EVENT_NONE = 0,
    CHG_EVENT_PLUG_IN,
    CHG_EVENT_PLUG_OUT,
    CHG_EVENT_AUTH_OK,
    CHG_EVENT_AUTH_FAIL,
    CHG_EVENT_PRECHARGE_DONE,
    CHG_EVENT_START_CMD,
    CHG_EVENT_STOP_CMD,
    CHG_EVENT_CHARGE_DONE,
    CHG_EVENT_FAULT_RAISED,
    CHG_EVENT_FAULT_CLEARED,
    CHG_EVENT_BILLING_DONE,
    CHG_EVENT_TIMEOUT
} ChargerEvent;

typedef enum {
    FAULT_NONE = 0,
    FAULT_OVERVOLTAGE,
    FAULT_UNDERVOLTAGE,
    FAULT_OVERCURRENT,
    FAULT_OVERTEMPERATURE,
    FAULT_ISOLATION,
    FAULT_EMERGENCY_STOP,
    FAULT_COMM_CAN_LOST,
    FAULT_COMM_485_LOST,
    FAULT_METER_INVALID
} FaultCode;

typedef struct {
    uint32_t session_id;
    uint32_t card_uid;
    uint32_t start_timestamp;
    uint32_t stop_timestamp;
    uint32_t energy_wh;
    uint32_t amount_cent;
    bool paid;
} BillingRecord;

typedef struct {
    FaultCode code;
    bool latch;
    uint32_t timestamp;
} FaultEvent;

#endif
