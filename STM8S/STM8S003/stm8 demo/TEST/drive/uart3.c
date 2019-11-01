#include "stm8s.h"
#include "uart3.h"
#include "stdio.h"

/**************************

UART3_RX->PD6;;;UART3_TX->PD5

***************************/

void UART3_INIT(void)
{
  UART3->CR2=0X00;//ʹ��UART3
  UART3->CR1=0x00; //�ر�UART3����������λ8λ����ֹ��żЧ�飬��ֹ�ж�
  UART3->CR3=0x00; //һλֹͣλ��Ĭ��ֵ
  UART3->BRR2=0x0b; //���ò�����Ϊ115200,16MHZ,Ҫ��дBRR2��
  UART3->BRR1=0x08;
  UART3->CR2|=0X2C;//ʹ�ܴ��ڽ��շ���
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
  while(*str!= '\0')//�ж��ַ����Ƿ������
  {
    UART3_SendData(*str);//���͵����ַ�
    str++;//�ַ���ַ��1��ָ������һ��
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


