#ifndef __sys_config_H
#define __sys_config_H	
#include "stm8s.h"

#define open_HSE 1
#define close_HSE 0

#define HSI_16M  0X00
#define HSI_8M   0X01
#define HSI_4M   0X02
#define HSI_2M   0X03
#define HSI_1M   0X04
#define HSI_500K 0X05
#define HSI_250K 0X06
#define HSI_125K 0X07

void UseHSI_AUTO(void);
void UseHSI_HAND(void);


#endif
