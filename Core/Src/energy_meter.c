#include "energy_meter.h"

bool energy_meter_init(void)
{
    return true;
}

bool energy_meter_update(MeterSnapshot *snapshot)
{
    if (snapshot == 0) {
        return false;
    }

    snapshot->voltage_mv = 220000;
    snapshot->current_ma = 10000;
    snapshot->power_mw = 2200000;
    snapshot->energy_wh += 10;
    return true;
}
