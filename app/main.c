#include "main.h"


int main(void)
{
    board_lowlevel_init();
    DebugInit(115200);
    printf("start\r\n");


    OLED_Init();
    led_init(&led0);

    driver_uart3_init();
    uart3_lock_init();
    uart3_senddata("AT\r\n", 4);
    
    
    while(1)
    {
        led_on(&led0);
        OLED_ShowChar(1, 1, 'a');
        
        
    }
}
 