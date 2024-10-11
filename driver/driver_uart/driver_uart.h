#ifndef __DRIVER_UART_H
#define __DRIVER_UART_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#if defined (STM32F10X_HD)
    #include "stm32f10x.h"
#else
    #error drv_timer.h: No processor defined!
#endif

void driver_uart(void);
void uart3_senddata(char *data, char length);


#endif /* __DRIVER_UART_H */
