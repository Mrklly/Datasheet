#include "stm8s.h"
#include "TIM1.h"
#include "led.h"

void TIM1_Init(void)
{
  TIM1->PSCRH = 0x3E; // ϵͳʱ�Ӿ�Ԥ��Ƶf=fck/(PSCR+1)
  TIM1->PSCRL = 0x7F; // PSCR=0x3E7F�� f=16M/(0x3E7F+1)=1000Hz,ÿ����������1ms
  TIM1->ARRH = 0x01; // �Զ����ؼĴ���ARR=0x01F4=500
  TIM1->ARRL = 0xF4; // ÿ����500�β���һ���жϣ���500ms
  TIM1->IER |= 0x01; // ��������ж�
  TIM1->CR1 |= 0x01; // ������ʹ�ܣ���ʼ����
}

#pragma vector=0xD     //11+2
__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void)//����жϣ����Ŀ���ָ��75ҳ
{
  TIM1->SR1 = 0; //����жϱ��
  led_not;
}
