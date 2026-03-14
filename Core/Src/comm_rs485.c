#include "comm_rs485.h"

static bool s_rs485_online = false;

bool comm_rs485_init(void)
{
    s_rs485_online = true;
    return true;
}

bool comm_rs485_poll_meter(void)
{
    return s_rs485_online;
}

bool comm_rs485_send_frame(const uint8_t *data, uint16_t len)
{
    (void)data;
    (void)len;
    return s_rs485_online;
}

bool comm_rs485_is_online(void)
{
    return s_rs485_online;
}
