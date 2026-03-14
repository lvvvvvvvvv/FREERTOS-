#include "fault_manager.h"

static FaultCode s_active_fault = FAULT_NONE;

void fault_manager_init(void)
{
    s_active_fault = FAULT_NONE;
}

void fault_manager_raise(FaultCode code, bool latch)
{
    (void)latch;
    if (s_active_fault == FAULT_NONE) {
        s_active_fault = code;
    }
}

void fault_manager_clear(FaultCode code)
{
    if (s_active_fault == code) {
        s_active_fault = FAULT_NONE;
    }
}

bool fault_manager_has_active_fault(void)
{
    return s_active_fault != FAULT_NONE;
}

FaultCode fault_manager_get_highest_priority(void)
{
    return s_active_fault;
}
