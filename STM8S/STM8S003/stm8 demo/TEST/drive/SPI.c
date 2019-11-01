#include "stm8s.h"
#include "SPI.h"
#include "delay.h"


void SPI_Init(void)
{
  SPI->CR1 = 0x00;//控制寄存器CR1先清零   
  SPI->CR1 |= 0x18;//配置通信波特率1Mbps(主频为16MHZ)16分频		
  //配置时钟的相位与极性
  SPI->CR1 |= 0x00;//空闲状态时，SCK保持低电平				    
  SPI->CR1 |= 0x00;//数据采样从第一个时钟边沿开始
  //定义帧格式
  SPI->CR1 |= 0x00;//通信时，串行移位，高位在前，低位在后 （MSB）    
  SPI->CR2 |= BIT(1);//NSS引脚软件管理 
  SPI->CR2 |= BIT(0);//主设备选择
  SPI->CR1 |= BIT(2);//主设备选择
  SPI_IO_Init();
  SPI->CR1 |= BIT(6);//使能时钟
}

void SPI_IO_Init(void)//PC5->SPI_SCK|||PC6->SPI_MOSI|||PC7->SPI_MISO
{
  GPIOC->DDR |= BIT(5);//PC5 输出模式
  GPIOC->CR1 |= BIT(5);//PC5 推挽输出
  GPIOC->CR2 |= BIT(5);//PC5输出速率10MHZ
  GPIOC->DDR |= BIT(6);//PC6 输出模式
  GPIOC->CR1 |= BIT(6);//PC6 推挽输出
  GPIOC->CR2 |= BIT(6);//PC6输出速率10MHZ
  GPIOC->CR1 |= BIT(7);
}

/***************************************************************************
*  Function: Driver_SPISend			  								                       
*  Object:  SPI发送数据													  					             
*  输入： &DataBuff 发送数据缓存的头指针；DataLen 发送数据的个数；       
*  输出： 无				                                 			                 
*  备注： 主模式 四线连接 硬件SPI sck	mosi misi 							                      
***************************************************************************/
void SPISend(u8 *DataBuff,u16 DataLen)
{
  volatile u8 temp;//防止被优化而产生警告
  
  for(;DataLen>0;DataBuff++,DataLen--)
  {
    while(!(SPI->SR&BIT(1)));//等待发送
    SPI->DR = *DataBuff;//发送数据
  }
  temp = SPI->DR;
  while(SPI->SR&BIT(7));//等待总线空闲 
}

/***************************************************************************
*  Function: Driver_SPIReceive			  								                   
*  Object:  SPI接收数据													  					             
*  输入： &DataBuff 接收数据缓存的头指针；DataLen 接收数据的个数；        
*  输出： 无				                                 			                 
*  备注： 主模式 四线连接 硬件SPI sck	mosi misi                     
***************************************************************************/
void SPIReceive(u8 *DataBuff,u16 DataLen)
{
  for(;DataLen>0;DataBuff++,DataLen--)
  {
    while(!(SPI->SR&BIT(0)));//等待接收
    *DataBuff = SPI->DR;//接收数据
  }
  while(SPI->SR&BIT(7));//等待总线空闲 
}
















