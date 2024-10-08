#include "board.h"
#include "stm32f10x.h"

const led_desc_t led0 = 
{
    .clk_source = RCC_APB2Periph_GPIOA,
    .off_lvl = Bit_SET,
    .on_lvl = Bit_RESET,
    .pin = GPIO_Pin_5,
    .port = GPIOA,
};

void board_lowlevel_init(void)
{
    //NVIC_SetPriorityGrouping(NVIC_PriorityGroup_4);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}
