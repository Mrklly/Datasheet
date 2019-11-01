#include "stm8s.h"
#include "eeprom.h"
#include "delay.h"

void FlashUNLock(void)//FLASH解锁
{
  do
  {
    FLASH->DUKR = 0XAE;            // 写入第一个密钥
    FLASH->DUKR = 0X56;            // 写入第二个密钥
  }while((FLASH->IAPSR & 0x08)==0);//等待解密成功
  delay_ms(50);//没有加延时会导致前几个数据写入失败，一直不知道为什么
}

void FlashLock(void)//FLASH加锁
{
  FLASH->IAPSR &= 0XFD;//加锁
}

/********************************************************************************************************
*  Function: EEPWrite				                                                           
*  Object: 写EEPROM
*  输入： 头地址(0~1535)  数据指针  数据长
*  输出： 无 	                                     
*  备注: 1.5K EEPROM  不能超过
********************************************************************************************************/
void EEPWrite(u16 Adr, u8 *pData, u16 Len)
{
  u8 *p;
  p = (u8*)(0x4000 + Adr);   //p指针指向EEPROM 对应的单元
  for( ; Len > 0; Len--)//写数据
  {
    *p++ = *pData++;
    while(!(FLASH->IAPSR&0X04)); //等待写完成
  } 
}

/********************************************************************************************************
*  Function: EEPRead				                                                           
*  Object: 读EEPROM
*  输入： 头地址(0~1535) 数据存放指针 数据长
*  输出： 无 	                                     
*  备注: 1.5K EEPROM
********************************************************************************************************/
void EEPRead(u16 Adr, u8 *pData, u16 Len)
{
  u8 *p;
  
  p = (u8*)0x4000 + Adr; //p指针指向EEPROM 对应的单元
  for( ; Len > 0; Len--)//读数据
  *pData++ = *p++;
}


void EEPWriteBit(u16 Adr,u8 dat)//写入 一个字节
{
  u8 *p;
  p = (u8*)(0x4000 + Adr);   //p指针指向EEPROM 对应的单元
  *p++ = dat;
  while(!(FLASH->IAPSR&0X04)); //等待写完成
}

void EEPReadBit(u16 Adr, u8 *pData)//读一个字节
{
  u8 *p;
  
  p = (u8*)0x4000 + Adr; //p指针指向EEPROM 对应的单元
  *pData = *p;
}



