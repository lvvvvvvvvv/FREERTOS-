#ifndef FAULT_MANAGER_H
#define FAULT_MANAGER_H

#include <stdbool.h>
#include "charger_types.h"

void fault_manager_init(void);
void fault_manager_raise(FaultCode code, bool latch);
void fault_manager_clear(FaultCode code);
bool fault_manager_has_active_fault(void);
FaultCode fault_manager_get_highest_priority(void);

#endif
