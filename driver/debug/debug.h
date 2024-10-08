#ifndef __DEBUG_H
#define __DEBUG_H


#include <stdint.h>


typedef void (*uart_rx_callback_t)(uint8_t data);


void uart_init(void);
void uart_send(uint8_t data);
void uart_recv_callback_register(uart_rx_callback_t cb);


#endif /* __DEBUG_H */
