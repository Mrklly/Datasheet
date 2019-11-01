#include "stm8s.h"
#include "chipID.h"

u8 ChipID[12];

void GetID(void)
{
  ChipID[0] = *(volatile u8 *)(0X48CD); 
  ChipID[1] = *(volatile u8 *)(0X48CE); 
  ChipID[2] = *(volatile u8 *)(0X48CF);
  ChipID[3] = *(volatile u8 *)(0X48D0); 
  ChipID[4] = *(volatile u8 *)(0X48D1); 
  ChipID[5] = *(volatile u8 *)(0X48D2);
  ChipID[6] = *(volatile u8 *)(0X48D3); 
  ChipID[7] = *(volatile u8 *)(0X48D4); 
  ChipID[8] = *(volatile u8 *)(0X48D5);
  ChipID[9] = *(volatile u8 *)(0X48D6); 
  ChipID[10] = *(volatile u8 *)(0X48D7); 
  ChipID[11] = *(volatile u8 *)(0X48D8);
}


