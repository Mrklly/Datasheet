#include "stm8s.h"
#include "beep.h"

void Beep_Init(void)
{
  FLASH->DUKR = 0xAE;
  FLASH->DUKR = 0x56;//输入2个密钥解锁FLASH
  while(!(FLASH->IAPSR & 0x08));//等待解密成功
  FLASH->CR2 |= 0x80;//OPT=1，写操作使能
  FLASH->NCR2 &= 0x7f;//NOPT=0，对选项字节进行写操作被使能
  *((unsigned char *)0x4803) |= 0x80;//AFR7=1;
  *((unsigned char *)0x4804) &= 0x7f;//NAFR7=0;参考STM8S2XXX中文资料33页
}




