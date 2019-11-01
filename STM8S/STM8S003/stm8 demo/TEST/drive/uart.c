#include "stm8s.h"
#include "uart.h"
#include "stdio.h"

/**************************

UART1_RX->PA4;;;UART1_TX->PA5

***************************/

void UART1_INIT(void)
{
  UART1->CR2=0X00;//ʹ��UART1
  UART1->CR1=0x00; //�ر�UART����������λ8λ����ֹ��żЧ�飬��ֹ�ж�
  UART1->CR3=0x00; //һλֹͣλ��Ĭ��ֵ
  UART1->BRR2=0x0b; //���ò�����Ϊ115200,16MHZ,Ҫ��дBRR2��
  UART1->BRR1=0x08;
  UART1->CR2|=0X2C;//ʹ�ܴ��ڽ��շ���
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
  while(*str!= '\0')//�ж��ַ����Ƿ������
  {
    UART1_SendData(*str);//���͵����ַ�
    str++;//�ַ���ַ��1��ָ������һ��
  }
}

/***********************************************
 * ��������fputc
 * ����  ���ض���c�⺯��printf��USART1
 * ����  ����
 * ���  ����
 * ����  ����printf����
 ***********************************************/
int fputc(int ch, FILE *f)
{  
 /*��Printf���ݷ�������*/ 
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


