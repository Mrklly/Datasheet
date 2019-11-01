#include "stm8s.h"
#include "uart.h"
#include "stdio.h"

/**************************

UART1_RX->PA4;;;UART1_TX->PA5

***************************/

void UART1_INIT(void)
{
  UART1->CR2=0X00;//使能UART1
  UART1->CR1=0x00; //关闭UART，设置数据位8位，禁止奇偶效验，禁止中断
  UART1->CR3=0x00; //一位停止位，默认值
  UART1->BRR2=0x0b; //设置波特率为115200,16MHZ,要先写BRR2。
  UART1->BRR1=0x08;
  UART1->CR2|=0X2C;//使能串口接收发送
}

void UART1_SendData(u8 ch)
{
  while((UART1->SR & 0x80)==0x00);
  UART1->DR=ch;
} 

void Uart1SendDatas(u8 *Dat,u8 Len)
{
   while(Len--)
  {
     UART1_SendData(*Dat++);
   }
}

void UART1_SendString(u8 *str)
{ 
  while(*str!= '\0')//判断字符串是否发送完毕
  {
    UART1_SendData(*str);//发送单个字符
    str++;//字符地址加1，指向先下一符
  }
}

/***********************************************
 * 函数名：fputc
 * 描述  ：重定向c库函数printf到USART1
 * 输入  ：无
 * 输出  ：无
 * 调用  ：由printf调用
 ***********************************************/
int fputc(int ch, FILE *f)
{  
 /*将Printf内容发往串口*/ 
  UART1->DR=(unsigned char)ch;
  while (!(UART1->SR & 0x80));
  return (ch);
}

#pragma vector=0x14
__interrupt void UART1_RX_IRQHandler(void)
{ 
  u8 USART1_RX_BUF; 
  while (!(UART1->SR & 0x20));
  USART1_RX_BUF=(u8)UART1->DR;
  
  printf("data=%d\r\n",USART1_RX_BUF);
}


