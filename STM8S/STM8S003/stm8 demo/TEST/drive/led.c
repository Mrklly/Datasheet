#include "stm8s.h"
#include "led.h"


void LED_Init(void)
{
  GPIOI->DDR|=0x01;	//设置pi0为输出模式
  GPIOI->CR1|=0x01;	//设置pi0为推挽输出
  GPIOI->CR2|=0x01;	//设置pi0输出频率为20MHZ
  GPIOI->ODR|=0x01;	//初始化pi0为高电平
}


