#include "stm8s.h"
#include "led.h"


void LED_Init(void)
{
  GPIOI->DDR|=0x01;	//����pi0Ϊ���ģʽ
  GPIOI->CR1|=0x01;	//����pi0Ϊ�������
  GPIOI->CR2|=0x01;	//����pi0���Ƶ��Ϊ20MHZ
  GPIOI->ODR|=0x01;	//��ʼ��pi0Ϊ�ߵ�ƽ
}


