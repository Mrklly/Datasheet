#ifndef __I2C_H
#define __I2C_H
#include "stm8s.h"

void I2C_Init(void);
void Driver_I2CSend(u8 Address,u8 *DataBuff,u16 DataLen);
void Driver_I2CRecv(u8 Address,u8 *DataBuff,u16 DataLen);

#endif

