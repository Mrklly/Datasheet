#include "stm8s.h"
#include "delay.h"
#include "ADC2.h"


void ADC2_Init(void)
{
  ADC2->CR1 |= 0x01;//��˯��ģʽ����
  ADC2->CR2 &= 0xF7; // A/D������������
  ADC2->CR1 = 0x60; // ADCʱ��=��ʱ��/12=1.333MHZ;ADCת��ģʽ=����;��ֹADCת��
  ADC2->TDRH = 0XFF;//��ֹʩ���ش�����
  ADC2->TDRL = 0XFF;
}

float ADC2_ReadOnce(u8 chx)
{
  u8 val_h=0,val_l=0,i=0;
  u16 val=0;
  float volate=0;
  
  ADC2->CSR = chx;//ѡ��ͨ��
  ADC2->CR1 |= 0x01; // CR1�Ĵ��������λ��1��ʹ��ADCת��
  for(i=0;i<100;i++);// ��ʱһ��ʱ�䣬��֤ADCģ����ϵ����
  ADC2->CR1 |= 0x01; // ��CR1�Ĵ��������λ��1
  while(!(ADC2->CSR & 0x80)); // �ȴ�ADC����
  val_h =(u8)ADC2->DRH; // ����ADC����ĸ�8λ
  val_l =(u8)ADC2->DRL; // ����ADC����ĵ�8λ
  val=(val_h<<2)+val_l;//�ϲ�ֵ
  volate=3.3f*val/1024;//�������ѹֵ
  return volate;
}


