#include "stm8s.h"
#include "SPI.h"
#include "delay.h"


void SPI_Init(void)
{
  SPI->CR1 = 0x00;//���ƼĴ���CR1������   
  SPI->CR1 |= 0x18;//����ͨ�Ų�����1Mbps(��ƵΪ16MHZ)16��Ƶ		
  //����ʱ�ӵ���λ�뼫��
  SPI->CR1 |= 0x00;//����״̬ʱ��SCK���ֵ͵�ƽ				    
  SPI->CR1 |= 0x00;//���ݲ����ӵ�һ��ʱ�ӱ��ؿ�ʼ
  //����֡��ʽ
  SPI->CR1 |= 0x00;//ͨ��ʱ��������λ����λ��ǰ����λ�ں� ��MSB��    
  SPI->CR2 |= BIT(1);//NSS����������� 
  SPI->CR2 |= BIT(0);//���豸ѡ��
  SPI->CR1 |= BIT(2);//���豸ѡ��
  SPI_IO_Init();
  SPI->CR1 |= BIT(6);//ʹ��ʱ��
}

void SPI_IO_Init(void)//PC5->SPI_SCK|||PC6->SPI_MOSI|||PC7->SPI_MISO
{
  GPIOC->DDR |= BIT(5);//PC5 ���ģʽ
  GPIOC->CR1 |= BIT(5);//PC5 �������
  GPIOC->CR2 |= BIT(5);//PC5�������10MHZ
  GPIOC->DDR |= BIT(6);//PC6 ���ģʽ
  GPIOC->CR1 |= BIT(6);//PC6 �������
  GPIOC->CR2 |= BIT(6);//PC6�������10MHZ
  GPIOC->CR1 |= BIT(7);
}

/***************************************************************************
*  Function: Driver_SPISend			  								                       
*  Object:  SPI��������													  					             
*  ���룺 &DataBuff �������ݻ����ͷָ�룻DataLen �������ݵĸ�����       
*  ����� ��				                                 			                 
*  ��ע�� ��ģʽ �������� Ӳ��SPI sck	mosi misi 							                      
***************************************************************************/
void SPISend(u8 *DataBuff,u16 DataLen)
{
  volatile u8 temp;//��ֹ���Ż�����������
  
  for(;DataLen>0;DataBuff++,DataLen--)
  {
    while(!(SPI->SR&BIT(1)));//�ȴ�����
    SPI->DR = *DataBuff;//��������
  }
  temp = SPI->DR;
  while(SPI->SR&BIT(7));//�ȴ����߿��� 
}

/***************************************************************************
*  Function: Driver_SPIReceive			  								                   
*  Object:  SPI��������													  					             
*  ���룺 &DataBuff �������ݻ����ͷָ�룻DataLen �������ݵĸ�����        
*  ����� ��				                                 			                 
*  ��ע�� ��ģʽ �������� Ӳ��SPI sck	mosi misi                     
***************************************************************************/
void SPIReceive(u8 *DataBuff,u16 DataLen)
{
  for(;DataLen>0;DataBuff++,DataLen--)
  {
    while(!(SPI->SR&BIT(0)));//�ȴ�����
    *DataBuff = SPI->DR;//��������
  }
  while(SPI->SR&BIT(7));//�ȴ����߿��� 
}
















