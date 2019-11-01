#include "stm8s.h"
#include "PWM.h"


void TIM2PWM_Init(void)
{
  TIM2->CCMR2 |= 0x70;// OC2M：输出比较2模式,为PWM模式2，
                      // 向上计数时，若计数器小于比较值，为无效电平即当计数器在0到比较值时，输出为1，否则为0
  TIM2->CCER1 |= 0x10;// CC2E = 1，开启输出引脚  
  TIM2->CCER1 &= 0xDF;// CC2P = 0，高电平为有效电平;
  TIM2->ARRH = 0;
  TIM2->ARRL = 0xC8; //200,即pwm的分辨率为200；   初始化自动装载寄存器，决定PWM方波的频率，Fpwm=4000000/200=20KHZ                         
  TIM2->CCR2H = 0; //初始化比较寄存器，决定PWM方波的占空比
  TIM2->CCR2L = 0;                             
  TIM2->PSCR = 2; // 初始化时钟分频器为4，即计数器的时钟频率为Fmaster=16MHZ,CK_CNT = 4M,计数器的时钟频率fCK_CNT等于fCK_PSC/2^(PSC[3:0])
  TIM2->CR1 |= 0x01;// 启动计数
}
