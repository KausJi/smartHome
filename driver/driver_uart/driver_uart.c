#include "driver_uart.h"
#include "stm32f10x_usart.h"

static ringbuffer8_t rxrb;
static uint8_t rx_buff[128];

void driver_uart3_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    //USART3_TX PB10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //USART3_RX PB11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    NVIC_InitTypeDef NVIC_InitStructure;
    memset(&NVIC_InitStructure, 0, sizeof(NVIC_InitTypeDef));
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART3, &USART_InitStructure);
    USART_Cmd(USART3, ENABLE);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
}

//发送一个字节
static void uart3_sendbyte(char data)
{
    while((USART3->SR & USART_SR_TXE) == 0); //等待发送完
    USART3->DR = (uint8_t)data;
}

//发送指定长度字节的数据
void uart3_senddata(char *data, char length)
{
    for(uint8_t i = 0; i < length; i++)
    {
        uart3_sendbyte(data[i]);
    }
}

//串口中断
void USART3_IRQHandler(void)
{
    /* 如果发生的是RX中断，把数据读出来，存入ringbuffer*/
    char c;

    /* UART in mode Receiver */
    if (((USART3->SR & USART_SR_RXNE) != RESET) && ((USART3->CR1 & USART_CR1_RXNEIE) != RESET))
    {
        c = USART3->DR;
        rb8_put(rxrb, c);
        return;
    } 
}

void uart3_lock_init(void)
{
    rxrb = rb8_new(rx_buff, sizeof(rx_buff));
}
