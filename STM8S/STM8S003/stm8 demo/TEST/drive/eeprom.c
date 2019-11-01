#include "stm8s.h"
#include "eeprom.h"
#include "delay.h"

void FlashUNLock(void)//FLASH����
{
  do
  {
    FLASH->DUKR = 0XAE;            // д���һ����Կ
    FLASH->DUKR = 0X56;            // д��ڶ�����Կ
  }while((FLASH->IAPSR & 0x08)==0);//�ȴ����ܳɹ�
  delay_ms(50);//û�м���ʱ�ᵼ��ǰ��������д��ʧ�ܣ�һֱ��֪��Ϊʲô
}

void FlashLock(void)//FLASH����
{
  FLASH->IAPSR &= 0XFD;//����
}

/********************************************************************************************************
*  Function: EEPWrite				                                                           
*  Object: дEEPROM
*  ���룺 ͷ��ַ(0~1535)  ����ָ��  ���ݳ�
*  ����� �� 	                                     
*  ��ע: 1.5K EEPROM  ���ܳ���
********************************************************************************************************/
void EEPWrite(u16 Adr, u8 *pData, u16 Len)
{
  u8 *p;
  p = (u8*)(0x4000 + Adr);   //pָ��ָ��EEPROM ��Ӧ�ĵ�Ԫ
  for( ; Len > 0; Len--)//д����
  {
    *p++ = *pData++;
    while(!(FLASH->IAPSR&0X04)); //�ȴ�д���
  } 
}

/********************************************************************************************************
*  Function: EEPRead				                                                           
*  Object: ��EEPROM
*  ���룺 ͷ��ַ(0~1535) ���ݴ��ָ�� ���ݳ�
*  ����� �� 	                                     
*  ��ע: 1.5K EEPROM
********************************************************************************************************/
void EEPRead(u16 Adr, u8 *pData, u16 Len)
{
  u8 *p;
  
  p = (u8*)0x4000 + Adr; //pָ��ָ��EEPROM ��Ӧ�ĵ�Ԫ
  for( ; Len > 0; Len--)//������
  *pData++ = *p++;
}


void EEPWriteBit(u16 Adr,u8 dat)//д�� һ���ֽ�
{
  u8 *p;
  p = (u8*)(0x4000 + Adr);   //pָ��ָ��EEPROM ��Ӧ�ĵ�Ԫ
  *p++ = dat;
  while(!(FLASH->IAPSR&0X04)); //�ȴ�д���
}

void EEPReadBit(u16 Adr, u8 *pData)//��һ���ֽ�
{
  u8 *p;
  
  p = (u8*)0x4000 + Adr; //pָ��ָ��EEPROM ��Ӧ�ĵ�Ԫ
  *pData = *p;
}



