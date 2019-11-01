#include "stm8s.h"
#include "TIM1.h"
#include "led.h"

void TIM1_Init(void)
{
  TIM1->PSCRH = 0x3E; // 系统时钟经预分频f=fck/(PSCR+1)
  TIM1->PSCRL = 0x7F; // PSCR=0x3E7F， f=16M/(0x3E7F+1)=1000Hz,每个计数周期1ms
  TIM1->ARRH = 0x01; // 自动重载寄存器ARR=0x01F4=500
  TIM1->ARRL = 0xF4; // 每记数500次产生一次中断，即500ms
  TIM1->IER |= 0x01; // 允许更新中断
  TIM1->CR1 |= 0x01; // 计数器使能，开始计数
}

#pragma vector=0xD     //11+2
__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void)//溢出中断，中文开发指南75页
{
  TIM1->SR1 = 0; //清除中断标记
  led_not;
}
