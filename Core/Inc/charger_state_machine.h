#ifndef CHARGER_STATE_MACHINE_H
#define CHARGER_STATE_MACHINE_H

#include "charger_types.h"

typedef struct {
    ChargerState state;
    FaultCode active_fault;
    bool plug_locked;
    bool output_enabled;
} ChargerContext;

void charger_sm_init(ChargerContext *ctx);
ChargerState charger_sm_handle_event(ChargerContext *ctx, ChargerEvent event);
const char *charger_sm_state_str(ChargerState state);

#endif
