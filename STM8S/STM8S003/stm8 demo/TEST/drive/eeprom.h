#ifndef __EEPROM_H
#define __EEPROM_H
#include "stm8s.h"

void FlashUNLock(void);
void FlashLock(void);
void EEPWrite(u16 Adr, u8 *pData, u16 Len);
void EEPRead(u16 Adr, u8 *pData, u16 Len);
void EEPWriteBit(u16 Adr,u8 dat);

#endif

