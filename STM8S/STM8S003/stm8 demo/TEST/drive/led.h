#ifndef __LED_H
#define __LED_H
#include "stm8s.h"

#define led_off  GPIOI->ODR|=(1<<0);  //�ر�LED
#define led_on   GPIOI->ODR&=0xfe;    //��LED
#define led_not  GPIOI->ODR^=(1<<0);  //LED״̬ȡ��


void LED_Init(void);


#endif

