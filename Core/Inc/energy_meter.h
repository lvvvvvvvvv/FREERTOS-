#ifndef ENERGY_METER_H
#define ENERGY_METER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint32_t voltage_mv;
    uint32_t current_ma;
    uint32_t power_mw;
    uint32_t energy_wh;
} MeterSnapshot;

bool energy_meter_init(void);
bool energy_meter_update(MeterSnapshot *snapshot);

#endif
