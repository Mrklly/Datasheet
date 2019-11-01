#ifndef __LED_H
#define __LED_H
#include "stm8s.h"

#define led_off  GPIOI->ODR|=(1<<0);  //关闭LED
#define led_on   GPIOI->ODR&=0xfe;    //打开LED
#define led_not  GPIOI->ODR^=(1<<0);  //LED状态取反


void LED_Init(void);


#endif

