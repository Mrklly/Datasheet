/*******************************************************************************
芯片型号：STM32S207R8T6
作者：孤心寒
联系方式：QQ：982166720
测试说明：所有外设已经都测试成功（I2C,SPI未测试）
*******************************************************************************/
#include "stm8s.h"
#include "delay.h"
#include "led.h"
#include "exit.h"
#include "uart.h"
#include "uart3.h"

int main(void)
{ 
  CLK->CKDIVR = 0x00;//使用内部时钟，16MHZ
  delay_init(16);
  UART1_INIT();
  UART3_INIT();
  LED_Init();
  INTEN; //打开全局中断
  
  
  while(1)
  {
    led_not;
    delay_ms(500);
  }
}

