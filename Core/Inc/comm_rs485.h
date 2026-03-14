#ifndef COMM_RS485_H
#define COMM_RS485_H

#include <stdbool.h>
#include <stdint.h>

bool comm_rs485_init(void);
bool comm_rs485_poll_meter(void);
bool comm_rs485_send_frame(const uint8_t *data, uint16_t len);
bool comm_rs485_is_online(void);

#endif
