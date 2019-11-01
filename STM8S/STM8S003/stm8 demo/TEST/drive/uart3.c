#include "stm8s.h"
#include "uart3.h"
#include "stdio.h"

/**************************

UART3_RX->PD6;;;UART3_TX->PD5

***************************/

void UART3_INIT(void)
{
  UART3->CR2=0X00;//使能UART3
  UART3->CR1=0x00; //关闭UART3，设置数据位8位，禁止奇偶效验，禁止中断
  UART3->CR3=0x00; //一位停止位，默认值
  UART3->BRR2=0x0b; //设置波特率为115200,16MHZ,要先写BRR2。
  UART3->BRR1=0x08;
  UART3->CR2|=0X2C;//使能串口接收发送
}


void UART3_SendData(u8 ch)
{
  while((UART3->SR & 0x80)==0x00);
  UART3->DR=ch;
} 

void Uart3SendDatas(u8 *Dat,u8 Len)
{
   while(Len--)
  {
     UART3_SendData(*Dat++);
   }
}

void UART3_SendString(u8 *str)
{ 
  while(*str!= '\0')//判断字符串是否发送完毕
  {
    UART3_SendData(*str);//发送单个字符
    str++;//字符地址加1，指向先下一符
  }
}


#pragma vector=0x17
__interrupt void UART3_RX_IRQHandler(void)
{ 
  volatile u8 USART3_RX_BUF; 
  while (!(UART3->SR & 0x20));
  USART3_RX_BUF=(u8)UART3->DR;
  
  UART3_SendData(USART3_RX_BUF);
}


