#include "exit.h"
#include "stm8s.h"
#include "led.h"


void EXIT_Init(void)
{
  GPIOB->DDR&=0XFE;//����PB0Ϊ����ģʽ
  GPIOB->CR1|=0X01;//����PB0Ϊ��������ģʽ	
  EXTI->CR1|=0X02;
  EXTI->CR1&=0XFB;//�����ش���
  GPIOB->CR2|=0X01;//����PB0�ж�
}

#pragma vector=6
__interrupt void EXTI_PORTB_IRQHandler(void)
{
  GPIOI->ODR^=(1<<0);
}


