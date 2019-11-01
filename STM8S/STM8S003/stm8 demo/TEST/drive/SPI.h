#ifndef __SPI_H
#define __SPI_H
#include "stm8s.h"

void SPI_Init(void);
void SPI_IO_Init(void);
void SPISend(u8 *DataBuff,u16 DataLen);
void SPIReceive(u8 *DataBuff,u16 DataLen);

#endif

