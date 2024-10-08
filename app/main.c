#include "main.h"


int main(void)
{
    borad_lowlevel_init();
    uart_init();
    OLED_Init();
    led_init(&led0);


    while(1)
    {
        led_on(&led0);
        OLED_ShowChar(1, 1, 'a');
    }
}
 