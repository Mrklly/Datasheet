#ifndef __ADC2_H
#define __ADC2_H
#include "stm8s.h"

void ADC2_Init(void);
float ADC2_ReadOnce(u8 chx);

#endif

