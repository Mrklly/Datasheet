#include "stm8s.h"
#include "PWM.h"


void TIM2PWM_Init(void)
{
  TIM2->CCMR2 |= 0x70;// OC2M������Ƚ�2ģʽ,ΪPWMģʽ2��
                      // ���ϼ���ʱ����������С�ڱȽ�ֵ��Ϊ��Ч��ƽ������������0���Ƚ�ֵʱ�����Ϊ1������Ϊ0
  TIM2->CCER1 |= 0x10;// CC2E = 1�������������  
  TIM2->CCER1 &= 0xDF;// CC2P = 0���ߵ�ƽΪ��Ч��ƽ;
  TIM2->ARRH = 0;
  TIM2->ARRL = 0xC8; //200,��pwm�ķֱ���Ϊ200��   ��ʼ���Զ�װ�ؼĴ���������PWM������Ƶ�ʣ�Fpwm=4000000/200=20KHZ                         
  TIM2->CCR2H = 0; //��ʼ���ȽϼĴ���������PWM������ռ�ձ�
  TIM2->CCR2L = 0;                             
  TIM2->PSCR = 2; // ��ʼ��ʱ�ӷ�Ƶ��Ϊ4������������ʱ��Ƶ��ΪFmaster=16MHZ,CK_CNT = 4M,��������ʱ��Ƶ��fCK_CNT����fCK_PSC/2^(PSC[3:0])
  TIM2->CR1 |= 0x01;// ��������
}
