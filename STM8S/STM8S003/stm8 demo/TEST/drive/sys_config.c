#include "sys_config.h"
#include "stm8s.h"

void UseHSI_AUTO(void)
{
  CLK->SWCR&=0XFB;//SWIEN=0,禁止时钟切换中断
  CLK->SWCR|=0X02;//SWEN=1，使能切换机制
  CLK->SWCR=0XB4;//0XE1:HSI为主时钟；0XD2:LSI为主时钟(仅LSI_EN=1时)；0XB4：HSE为主时钟；
  CLK->CKDIVR=0X00;//分频系数
}

void UseHSI_HAND(void)//暂时测试失败
{
  CLK->SWCR&=0XFB;//SWIEN=0,禁止时钟切换中断
  CLK->CKDIVR=0;//分频系数
  CLK->SWCR=0XB4;//0XE1:HSI为主时钟；0XD2:LSI为主时钟(仅LSI_EN=1时)；0XB4：HSE为主时钟；
  while(!(CLK->SWCR&0X07));
  CLK->SWCR|=0X02;//SWEN=1，使能切换机制
}


