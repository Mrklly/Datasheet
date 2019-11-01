#ifndef __UART3_H
#define __UART3_H
#include "stm8s.h"
#include "stdio.h"

void UART3_INIT(void);
void UART3_SendData(u8 ch);
void UART3_SendDatas(u8 ch);
void UART3_SendString(u8 *str);

#endif

