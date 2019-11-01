#include "stm8s.h"
#include "TIM4.h"
#include "led.h"

void TIM4_Init(void)
{
  TIM4->PSCR = 0x07; // 2M��128��Ƶ
  TIM4->ARR = 0x64; // 6.4ms
  TIM4->IER |= 0x01; // ��������ж�
  TIM4->CR1 |= 0x01; // ������ʹ�ܣ���ʼ����
}

#pragma vector=0x19     //23+2
__interrupt void TIM4_UPD_OVF_IRQHandler(void)//����жϣ����Ŀ���ָ��75ҳ
{
  TIM4->SR1 = 0; //����жϱ��
}


