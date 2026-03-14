#ifndef RFID_PAYMENT_H
#define RFID_PAYMENT_H

#include <stdbool.h>
#include <stdint.h>
#include "charger_types.h"

bool rfid_payment_init(void);
bool rfid_payment_authorize(uint32_t card_uid);
bool rfid_payment_settle(BillingRecord *record);

#endif
