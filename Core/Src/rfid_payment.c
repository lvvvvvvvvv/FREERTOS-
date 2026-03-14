#include "rfid_payment.h"

bool rfid_payment_init(void)
{
    return true;
}

bool rfid_payment_authorize(uint32_t card_uid)
{
    /* Demo: even UID passes, odd UID fails */
    return ((card_uid & 0x1U) == 0U);
}

bool rfid_payment_settle(BillingRecord *record)
{
    if (record == 0) {
        return false;
    }

    record->paid = true;
    return true;
}
