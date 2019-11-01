#ifndef __UART_H
#define __UART_H
#include "stm8s.h"
#include "stdio.h"

void UART1_INIT(void);
void UART1_SendData(u8 ch);
void UART1_SendDatas(u8 ch);
void UART1_SendString(u8 *str);
int fputc(int ch, FILE *f);

#endif

