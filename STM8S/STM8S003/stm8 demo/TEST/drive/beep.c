#include "stm8s.h"
#include "beep.h"

void Beep_Init(void)
{
  FLASH->DUKR = 0xAE;
  FLASH->DUKR = 0x56;//����2����Կ����FLASH
  while(!(FLASH->IAPSR & 0x08));//�ȴ����ܳɹ�
  FLASH->CR2 |= 0x80;//OPT=1��д����ʹ��
  FLASH->NCR2 &= 0x7f;//NOPT=0����ѡ���ֽڽ���д������ʹ��
  *((unsigned char *)0x4803) |= 0x80;//AFR7=1;
  *((unsigned char *)0x4804) &= 0x7f;//NAFR7=0;�ο�STM8S2XXX��������33ҳ
}




