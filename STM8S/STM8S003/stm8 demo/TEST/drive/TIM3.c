#include "stm8s.h"
#include "TIM3.h"
#include "led.h"

void TIM3_Init(void)
{
  TIM3->PSCR = 0x0A; //ϵͳʱ�Ӿ�Ԥ��Ƶf=16M/1024=15.625k,0A=10,2^10=1024;
  TIM3->ARRH = 0x3D; // 1/15.625k * 15626 = 1s
  TIM3->ARRL = 0x0A; //3D0A=15626
  TIM3->IER |= 0x01; //��������ж�
  TIM3->CR1 |= 0x01; //ʹ�ܼ�����
}

#pragma vector=0x11     //15+2
__interrupt void TIM3_UPD_OVF_BRK_IRQHandler(void)//����жϣ����Ŀ���ָ��75ҳ
{
  TIM3->SR1 = 0; //����жϱ��
  led_not;
}

