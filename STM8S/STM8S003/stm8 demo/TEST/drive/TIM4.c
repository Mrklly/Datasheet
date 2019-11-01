#include "stm8s.h"
#include "TIM4.h"
#include "led.h"

void TIM4_Init(void)
{
  TIM4->PSCR = 0x07; // 2M的128分频
  TIM4->ARR = 0x64; // 6.4ms
  TIM4->IER |= 0x01; // 允许更新中断
  TIM4->CR1 |= 0x01; // 计数器使能，开始计数
}

#pragma vector=0x19     //23+2
__interrupt void TIM4_UPD_OVF_IRQHandler(void)//溢出中断，中文开发指南75页
{
  TIM4->SR1 = 0; //清除中断标记
}


