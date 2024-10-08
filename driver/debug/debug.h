#ifndef  __DEBUG_H
#define  __DEBUG_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>


#if defined (STM32F10X_HD)
    #include "stm32f10x.h"
#else
    #error drv_timer.h: No processor defined!
#endif


/* �û�API */
int MH_DebugInit(uint32_t baud_rate);


#endif /* __DEBUG_H */
