#include "comm_can.h"

static bool s_can_online = false;

bool comm_can_init(void)
{
    s_can_online = true;
    return true;
}

bool comm_can_send_heartbeat(uint32_t uptime_ms, uint16_t state)
{
    (void)uptime_ms;
    (void)state;
    return s_can_online;
}

bool comm_can_process_rx(void)
{
    return s_can_online;
}

void comm_can_set_online(bool online)
{
    s_can_online = online;
}

bool comm_can_is_online(void)
{
    return s_can_online;
}
