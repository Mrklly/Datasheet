#ifndef __BEEP_H
#define __BEEP_H
#include "stm8s.h"

#define beep_on BEEP->CSR |= (1<<5);//BEEPEN=1��ʹ�ܷ�����
#define beep_off BEEP->CSR &= (0<<5);//BEEPEN=0��ʧ�ܷ�����

void Beep_Init(void);

#endif

