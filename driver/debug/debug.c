#include "debug.h"
#include "stm32f10x_usart.h"


#if  defined  (STM32F10X_HD)


/******************************************************************************
 * @brief      ���ڲ���������ʼ��һ��������Ϊprintf�Ļ���
 *
 * @param[in]  ��
 *
 * @return     ��
 *
 ******************************************************************************/
static void uart_init(uint32_t baud_rate)
{
    GPIO_InitTypeDef GPIO_InitStructure;                                                //����GPIO�ṹ��
    USART_InitTypeDef USART_InitStructure;                                              //���崮�ڽṹ��
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);       //ʹ��GPIOA��UART1��ʱ��

    GPIO_InitStructure.GPIO_Pin                     = GPIO_Pin_9 | GPIO_Pin_10;         //ʹ��PA9��PA10
    GPIO_InitStructure.GPIO_Mode                    = GPIO_Mode_AF_PP;                  //����GPIOΪ����ģʽ 
    GPIO_InitStructure.GPIO_Speed                   = GPIO_Speed_50MHz;                 //����Ϊ50Mhz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                                              //��ʼ��GPIO

    USART_InitStructure.USART_BaudRate              = baud_rate;                        //������
    USART_InitStructure.USART_WordLength            = USART_WordLength_8b;              //����λ8λ
    USART_InitStructure.USART_StopBits              = USART_StopBits_1;                 //ֹͣλ1λ
    USART_InitStructure.USART_Parity                = USART_Parity_No;                  //У��λ ��
    USART_InitStructure.USART_HardwareFlowControl   = USART_HardwareFlowControl_None;   //��������
    USART_InitStructure.USART_Mode                  = USART_Mode_Rx | USART_Mode_Tx;    //ʹ�ܽ��պͷ�������
    USART_Init(USART1, &USART_InitStructure);                                           //��ʼ��UART
    USART_ClearFlag(USART1, USART_FLAG_TC);                                             //�������λ
    USART_Cmd(USART1, ENABLE);                                                          //����USART
}




/******************************************************************************
 * @brief      ���ڲ�������ʹ�ô��ڷ���һ���ַ�
 *
 * @param[in]  ��
 *
 * @return     ��
 *
 ******************************************************************************/
static void uart_put_ch(uint8_t ch)
{
    USART_SendData(USART1, (unsigned char) ch);                     //����һ���ַ�
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);   //�ȴ�UART�������
}

#endif




/******************************************************************************
 * @brief      ��ʼ������
 *
 * @param[in]  baud_rate   :  ������
 *
 * @return     ��
 *
 ******************************************************************************/
int MH_DebugInit(uint32_t baud_rate)
{
    uart_init(baud_rate);
    return 0;
}




/* ��׼����Ҫ��֧�ֺ��� */
#pragma import(__use_no_semihosting)
FILE __stdout;

struct __FILE {
    int handle;
};

/* ����_sys_exit()�Ա���ʹ�ð�����ģʽ */
void _sys_exit(int x)
{
    x = x;
}


int fputc(int ch, FILE *f)
{
    uart_put_ch(ch);
    return (ch);
}


