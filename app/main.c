#include "main.h"


int main(void)
{
    board_lowlevel_init();
    DebugInit(115200);
    OLED_Init();
    led_init(&led0);
    uart3_lock_init();
    
    printf("start\r\n");

    while(1)
    {
        led_on(&led0);
        OLED_ShowChar(1, 1, 'a');
        
        
    }
}
 