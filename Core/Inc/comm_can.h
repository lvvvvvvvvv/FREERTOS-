#ifndef COMM_CAN_H
#define COMM_CAN_H

#include <stdbool.h>
#include <stdint.h>

bool comm_can_init(void);
bool comm_can_send_heartbeat(uint32_t uptime_ms, uint16_t state);
bool comm_can_process_rx(void);
void comm_can_set_online(bool online);
bool comm_can_is_online(void);

#endif
