#include "sys_config.h"
#include "stm8s.h"

void UseHSI_AUTO(void)
{
  CLK->SWCR&=0XFB;//SWIEN=0,��ֹʱ���л��ж�
  CLK->SWCR|=0X02;//SWEN=1��ʹ���л�����
  CLK->SWCR=0XB4;//0XE1:HSIΪ��ʱ�ӣ�0XD2:LSIΪ��ʱ��(��LSI_EN=1ʱ)��0XB4��HSEΪ��ʱ�ӣ�
  CLK->CKDIVR=0X00;//��Ƶϵ��
}

void UseHSI_HAND(void)//��ʱ����ʧ��
{
  CLK->SWCR&=0XFB;//SWIEN=0,��ֹʱ���л��ж�
  CLK->CKDIVR=0;//��Ƶϵ��
  CLK->SWCR=0XB4;//0XE1:HSIΪ��ʱ�ӣ�0XD2:LSIΪ��ʱ��(��LSI_EN=1ʱ)��0XB4��HSEΪ��ʱ�ӣ�
  while(!(CLK->SWCR&0X07));
  CLK->SWCR|=0X02;//SWEN=1��ʹ���л�����
}


