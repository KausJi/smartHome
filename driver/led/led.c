#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "stm32f10x.h"
#include "led.h"


void led_init(const led_desc_t *desc)
{
    RCC_APB2PeriphClockCmd(desc->clk_source, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    memset(&GPIO_InitStructure, 0, sizeof(GPIO_InitTypeDef));
    GPIO_InitStructure.GPIO_Pin = desc->pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(desc->port, &GPIO_InitStructure);

    GPIO_WriteBit(desc->port, desc->pin, desc->off_lvl);
}

void led_deinit(const led_desc_t *desc)
{
    GPIO_WriteBit(desc->port, desc->pin, desc->off_lvl);
}

void led_on(const led_desc_t *desc)
{
    GPIO_WriteBit(desc->port, desc->pin, desc->on_lvl);
}

void led_off(const led_desc_t *desc)
{
    GPIO_WriteBit(desc->port, desc->pin, desc->off_lvl);
}
