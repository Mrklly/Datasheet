/*******************************************************************************
оƬ�ͺţ�STM32S207R8T6
���ߣ����ĺ�
��ϵ��ʽ��QQ��982166720
����˵�������������Ѿ������Գɹ���I2C,SPIδ���ԣ�
*******************************************************************************/
#include "stm8s.h"
#include "delay.h"
#include "led.h"
#include "exit.h"
#include "uart.h"
#include "uart3.h"

int main(void)
{ 
  CLK->CKDIVR = 0x00;//ʹ���ڲ�ʱ�ӣ�16MHZ
  delay_init(16);
  UART1_INIT();
  UART3_INIT();
  LED_Init();
  INTEN; //��ȫ���ж�
  
  
  while(1)
  {
    led_not;
    delay_ms(500);
  }
}

