#include "stm8s.h"
#include "I2C.h"
#include "delay.h"


void I2C_Init(void)
{
  CLK->PCKENR1 |= 0X01;//��I2Cʱ��
  I2C->CCRH &= ~0X80;//I2Cģʽѡ�� ��׼ģʽ
  I2C->FREQR = 0x02;//��������ʱ��fck ��׼ģʽ>1M(����2M) 
  //���׼(fscΪͨ������):
  //tck=1/fck=0.5us
  //CCR=1/(2fsc*tck) = 1000000/2fsc*0.5 = 1000000/fsc
  //���������ú궨�� ����ͨ������ 10Kbps 
  I2C->CCRH = 0;
  I2C->CCRL = 100;
  I2C->TRISER = 3;//��������ʱ��Ĵ���
  I2C->CR1 |= 0X01;//����I2Cģ��
}


/********************************************************************************************************
*  Function: Driver_I2CSend						                                                           
*  Object: Ӳ��I2C����
*  ���룺 ���豸��ַ�� ���������ݵ�ͷָ�룻 �������ݵĳ��� 
*  ����� ��  	                                     
*  ��ע:  ͨ����������ֳ�ʱ���� ��ֱ�ӷ��� ���ⳤ�ȴ�
********************************************************************************************************/
void Driver_I2CSend(u8 Address,u8 *DataBuff,u16 DataLen)
{  	
  volatile u8 temp;//��ֹ���Ż�����������
  u16 time;
  
  time = 500;
  while(I2C->SR3&BIT(1))//�ȴ����߿���	
  if(!--time) 
  return;

  I2C->CR2 |= 0x01;//����ʼ����  
  time = 500;
  while((I2C->SR1&BIT(0))==0)//�ȴ��������
  if(!--time) return; 
  asm("nop");//������ʱ
  asm("nop");
  asm("nop");
  temp = I2C->SR1;

  I2C->DR = Address;//���͵�ַ
  time = 500;
  while((I2C->SR1&BIT(1))==0)//�ȴ�ACKӦ��
  if(!--time) return;
  asm("nop");//������ʱ
  asm("nop");
  asm("nop");
  temp = I2C->SR1;
  temp = I2C->SR3;//��ADDR��־

  //��������
  for(;DataLen>0;DataLen--,DataBuff++)
  {
    time = 500;
    while(!(I2C->SR1&BIT(7)))//�ȴ��Ĵ���Ϊ��
    if(!--time)return;
    I2C->DR = *DataBuff;
    time = 500;
    while(!(I2C->SR1&BIT(2)))//�ȴ��������
    if(!--time) return;
    asm("nop");
    asm("nop");
    asm("nop");
  }

  //��ֹͣ����,�ر�ͨ��
  //��BTFλ
  temp = I2C->SR1;
  temp = I2C->DR;
  I2C->CR2 |= BIT(1);//��ֹͣ 
}


/********************************************************************************************************
*  Function: Driver_I2CRecv						                                                           
*  Object: Ӳ��I2C���� 
*  ���룺 ���豸��ַ�����������ݵ�ͷָ�룻���������ݵĳ���
*  ����� �� 	                                     
*  ��ע:  ͨ����������ֳ�ʱ���� ��ֱ�ӷ��� ���ⳤ�ȴ�
********************************************************************************************************/
void Driver_I2CRecv(u8 Address,u8 *DataBuff,u16 DataLen)
{  	
  volatile u8 temp;//��ֹ���Ż�����������
  u16 time;
  
  time = 500;
  while(I2C->SR3&BIT(1))//�ȴ����߿���
  if(!--time)return;

  I2C->CR2 |= BIT(0);//����ʼ����
  time = 500;
  while(!(I2C->SR1&BIT(0)))//�ȴ��������
  if(!--time)return;
  asm("nop");
  asm("nop");
  asm("nop");
  temp = I2C->SR1;

  I2C->DR = Address;//���ӵ�ַ
  time = 500;
  while(!(I2C->SR1&BIT(1)))//�ȴ�ACKӦ��
  if(!--time)return;
  asm("nop");
  asm("nop");
  asm("nop");
  temp = I2C->SR1;
  temp = I2C->SR3;//��ADDR��־

  //��������,��DataLen-1����
  //ʹ��ACKӦ��
  I2C->CR2 |= BIT(2);
  for(;DataLen>1;DataLen--,DataBuff++)
  {
    time = 500;
    while(!(I2C->SR1&BIT(6)))//�ȴ��Ĵ���Ϊ��
    if(!--time)return;
    *DataBuff = I2C->DR;
  }
  I2C->CR2 &= ~BIT(2);//�ر�ACKӦ��
  //��ֹͣ����,�ر�ͨ��
  //��BTFλ
  temp = I2C->SR1;
  temp = I2C->DR;
  //��ֹͣ
  I2C->CR2 |= BIT(1);
  asm("nop");
  asm("nop");
  asm("nop");

  //�����һ����
  time = 500;
  while(!(I2C->SR1&BIT(6)))
  if(!--time)
  return;
  *DataBuff = I2C->DR;  		
}









