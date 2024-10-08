#include "debug.h"
#include "stm32f10x_usart.h"


#if  defined  (STM32F10X_HD)


/******************************************************************************
 * @brief      �1�7�1�7�1�7�1�8�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�0�3�1�7�1�7�0�5�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�0�2printf�1�7�0�3�1�7�1�7�1�7
 *
 * @param[in]  �1�7�1�7
 *
 * @return     �1�7�1�7
 *
 ******************************************************************************/
static void uart_init(uint32_t baud_rate)
{
    GPIO_InitTypeDef GPIO_InitStructure;                                                //�1�7�1�7�1�7�1�7GPIO�1�7�5�5�1�7�1�7
    USART_InitTypeDef USART_InitStructure;                                              //�1�7�1�7�1�7�Ą1�7�1�9�5�5�1�7�1�7
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);       //�0�0�1�7�1�7GPIOA�1�7�1�7UART1�1�7�1�7�0�2�1�7�1�7

    GPIO_InitStructure.GPIO_Pin                     = GPIO_Pin_9 | GPIO_Pin_10;         //�0�0�1�7�1�7PA9�1�7�1�7PA10
    GPIO_InitStructure.GPIO_Mode                    = GPIO_Mode_AF_PP;                  //�1�7�1�7�1�7�1�7GPIO�0�2�1�7�1�7�1�7�1�7�0�0�0�4 
    GPIO_InitStructure.GPIO_Speed                   = GPIO_Speed_50MHz;                 //�1�7�1�7�1�7�1�7�0�250Mhz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                                              //�1�7�1�7�0�3�1�7�1�7GPIO

    USART_InitStructure.USART_BaudRate              = baud_rate;                        //�1�7�1�7�1�7�1�7�1�7�1�7
    USART_InitStructure.USART_WordLength            = USART_WordLength_8b;              //�1�7�1�7�1�7�1�7��8��
    USART_InitStructure.USART_StopBits              = USART_StopBits_1;                 //�0�5�0�9��1��
    USART_InitStructure.USART_Parity                = USART_Parity_No;                  //���1�7�1�7�� �1�7�1�7
    USART_InitStructure.USART_HardwareFlowControl   = USART_HardwareFlowControl_None;   //�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7
    USART_InitStructure.USART_Mode                  = USART_Mode_Rx | USART_Mode_Tx;    //�0�0�1�7�1�7�1�7�1�7�0�6�0�5�1�7�1�7�1�7�1�7�1�7�1�7�1�7
    USART_Init(USART1, &USART_InitStructure);                                           //�1�7�1�7�0�3�1�7�1�7UART
    USART_ClearFlag(USART1, USART_FLAG_TC);                                             //�1�7�1�7�1�7�1�7�1�7�1�7�1�7��
    USART_Cmd(USART1, ENABLE);                                                          //�1�7�1�7�1�7�1�7USART
}




/******************************************************************************
 * @brief      �1�7�1�7�1�7�1�8�1�7�1�7�1�7�1�7�1�7�1�7�1�7�0�0�1�7�0�0�1�7�1�7�1�3�1�7�1�7�1�7�0�5�1�7�1�7�1�7�0�7�1�7
 *
 * @param[in]  �1�7�1�7
 *
 * @return     �1�7�1�7
 *
 ******************************************************************************/
static void uart_put_ch(uint8_t ch)
{
    USART_SendData(USART1, (unsigned char) ch);                     //�1�7�1�7�1�7�1�7�0�5�1�7�1�7�1�7�0�7�1�7
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);   //�1�7�0�9�1�7UART�1�7�1�7�1�7�1�7�1�7�1�7�1�7
}

#endif




/******************************************************************************
 * @brief      �1�7�1�7�0�3�1�7�1�7�1�7�1�7�1�7�1�7
 *
 * @param[in]  baud_rate   :  �1�7�1�7�1�7�1�7�1�7�1�7
 *
 * @return     �1�7�1�7
 *
 ******************************************************************************/
int MH_DebugInit(uint32_t baud_rate)
{
    uart_init(baud_rate);
    return 0;
}




/* �1�7�1�7�0�6�1�7�1�7�1�7�1�7�0�8�1�7�1�7�0�1�1�7�0�0�1�7�1�7�1�7 */
#pragma import(__use_no_semihosting)
FILE __stdout;

struct __FILE {
    int handle;
};

/* �1�7�1�7�1�7�1�7_sys_exit()�1�7�0�3�1�7�1�7�1�7�0�0�1�7�0�8�1�7�1�7�1�7�1�7�1�7�0�0�0�4 */
void _sys_exit(int x)
{
    x = x;
}


int fputc(int ch, FILE *f)
{
    uart_put_ch(ch);
    return (ch);
}


