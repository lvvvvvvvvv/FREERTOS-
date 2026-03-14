#include "charger_state_machine.h"

static bool is_fault_event(ChargerEvent event)
{
    return (event == CHG_EVENT_FAULT_RAISED);
}

void charger_sm_init(ChargerContext *ctx)
{
    if (ctx == 0) {
        return;
    }

    ctx->state = CHG_STATE_IDLE;
    ctx->active_fault = FAULT_NONE;
    ctx->plug_locked = false;
    ctx->output_enabled = false;
}

ChargerState charger_sm_handle_event(ChargerContext *ctx, ChargerEvent event)
{
    if (ctx == 0) {
        return CHG_STATE_FAULT;
    }

    if (is_fault_event(event)) {
        ctx->state = CHG_STATE_FAULT;
        ctx->output_enabled = false;
        return ctx->state;
    }

    switch (ctx->state) {
    case CHG_STATE_IDLE:
        if (event == CHG_EVENT_PLUG_IN) {
            ctx->state = CHG_STATE_PLUG_DETECTED;
        }
        break;

    case CHG_STATE_PLUG_DETECTED:
        if (event == CHG_EVENT_PLUG_OUT) {
            ctx->state = CHG_STATE_IDLE;
        } else if (event == CHG_EVENT_START_CMD) {
            ctx->state = CHG_STATE_AUTH_PENDING;
        }
        break;

    case CHG_STATE_AUTH_PENDING:
        if (event == CHG_EVENT_AUTH_OK) {
            ctx->state = CHG_STATE_PRECHARGE;
            ctx->plug_locked = true;
        } else if (event == CHG_EVENT_AUTH_FAIL || event == CHG_EVENT_TIMEOUT || event == CHG_EVENT_PLUG_OUT) {
            ctx->state = CHG_STATE_IDLE;
            ctx->plug_locked = false;
        }
        break;

    case CHG_STATE_PRECHARGE:
        if (event == CHG_EVENT_PRECHARGE_DONE) {
            ctx->state = CHG_STATE_CHARGING;
            ctx->output_enabled = true;
        } else if (event == CHG_EVENT_STOP_CMD || event == CHG_EVENT_TIMEOUT) {
            ctx->state = CHG_STATE_STOPPING;
        }
        break;

    case CHG_STATE_CHARGING:
        if (event == CHG_EVENT_STOP_CMD || event == CHG_EVENT_CHARGE_DONE || event == CHG_EVENT_TIMEOUT) {
            ctx->state = CHG_STATE_STOPPING;
            ctx->output_enabled = false;
        }
        break;

    case CHG_STATE_STOPPING:
        if (event == CHG_EVENT_BILLING_DONE) {
            ctx->state = CHG_STATE_IDLE;
            ctx->plug_locked = false;
            ctx->output_enabled = false;
        }
        break;

    case CHG_STATE_BILLING:
        if (event == CHG_EVENT_BILLING_DONE) {
            ctx->state = CHG_STATE_IDLE;
        }
        break;

    case CHG_STATE_FAULT:
        if (event == CHG_EVENT_FAULT_CLEARED) {
            ctx->state = CHG_STATE_IDLE;
            ctx->plug_locked = false;
            ctx->output_enabled = false;
            ctx->active_fault = FAULT_NONE;
        }
        break;

    default:
        ctx->state = CHG_STATE_FAULT;
        break;
    }

    return ctx->state;
}

const char *charger_sm_state_str(ChargerState state)
{
    switch (state) {
    case CHG_STATE_IDLE: return "IDLE";
    case CHG_STATE_PLUG_DETECTED: return "PLUG_DETECTED";
    case CHG_STATE_AUTH_PENDING: return "AUTH_PENDING";
    case CHG_STATE_PRECHARGE: return "PRECHARGE";
    case CHG_STATE_CHARGING: return "CHARGING";
    case CHG_STATE_STOPPING: return "STOPPING";
    case CHG_STATE_BILLING: return "BILLING";
    case CHG_STATE_FAULT: return "FAULT";
    default: return "UNKNOWN";
    }
}
