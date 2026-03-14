#include <assert.h>
#include <stdio.h>

#include "charger_state_machine.h"

static void test_normal_flow(void)
{
    ChargerContext ctx;
    charger_sm_init(&ctx);

    assert(charger_sm_handle_event(&ctx, CHG_EVENT_PLUG_IN) == CHG_STATE_PLUG_DETECTED);
    assert(charger_sm_handle_event(&ctx, CHG_EVENT_START_CMD) == CHG_STATE_AUTH_PENDING);
    assert(charger_sm_handle_event(&ctx, CHG_EVENT_AUTH_OK) == CHG_STATE_PRECHARGE);
    assert(charger_sm_handle_event(&ctx, CHG_EVENT_PRECHARGE_DONE) == CHG_STATE_CHARGING);
    assert(charger_sm_handle_event(&ctx, CHG_EVENT_CHARGE_DONE) == CHG_STATE_STOPPING);
    assert(charger_sm_handle_event(&ctx, CHG_EVENT_BILLING_DONE) == CHG_STATE_IDLE);
}

static void test_fault_flow(void)
{
    ChargerContext ctx;
    charger_sm_init(&ctx);

    (void)charger_sm_handle_event(&ctx, CHG_EVENT_PLUG_IN);
    (void)charger_sm_handle_event(&ctx, CHG_EVENT_START_CMD);
    assert(charger_sm_handle_event(&ctx, CHG_EVENT_FAULT_RAISED) == CHG_STATE_FAULT);
    assert(charger_sm_handle_event(&ctx, CHG_EVENT_FAULT_CLEARED) == CHG_STATE_IDLE);
}

int main(void)
{
    test_normal_flow();
    test_fault_flow();
    puts("state machine tests passed");
    return 0;
}
