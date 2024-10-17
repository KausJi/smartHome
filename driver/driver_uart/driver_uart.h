#ifndef __DRIVER_UART_H
#define __DRIVER_UART_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <ringbuffer8.h>

#if defined (STM32F10X_HD)
    #include "stm32f10x.h"
#else
    #error drv_timer.h: No processor defined!
#endif

void driver_uart3_init(void);
void uart3_senddata(char *data, char length);
void uart3_lock_init(void);

#endif /* __DRIVER_UART_H */
