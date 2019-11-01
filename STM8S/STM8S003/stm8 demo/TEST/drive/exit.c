#include "exit.h"
#include "stm8s.h"
#include "led.h"


void EXIT_Init(void)
{
  GPIOB->DDR&=0XFE;//设置PB0为输入模式
  GPIOB->CR1|=0X01;//设置PB0为浮空输入模式	
  EXTI->CR1|=0X02;
  EXTI->CR1&=0XFB;//上升沿触发
  GPIOB->CR2|=0X01;//开启PB0中断
}

#pragma vector=6
__interrupt void EXTI_PORTB_IRQHandler(void)
{
  GPIOI->ODR^=(1<<0);
}


