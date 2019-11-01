#include "stm8s.h"
#include "I2C.h"
#include "delay.h"


void I2C_Init(void)
{
  CLK->PCKENR1 |= 0X01;//开I2C时钟
  I2C->CCRH &= ~0X80;//I2C模式选择 标准模式
  I2C->FREQR = 0x02;//设置输入时钟fck 标准模式>1M(配置2M) 
  //则标准(fsc为通信速率):
  //tck=1/fck=0.5us
  //CCR=1/(2fsc*tck) = 1000000/2fsc*0.5 = 1000000/fsc
  //按速率设置宏定义 配置通信速率 10Kbps 
  I2C->CCRH = 0;
  I2C->CCRL = 100;
  I2C->TRISER = 3;//配置上升时间寄存器
  I2C->CR1 |= 0X01;//开启I2C模块
}


/********************************************************************************************************
*  Function: Driver_I2CSend						                                                           
*  Object: 硬件I2C发送
*  输入： 从设备地址； 待发送数据的头指针； 待发数据的长； 
*  输出： 无  	                                     
*  备注:  通信中如果出现超时故障 则直接返回 避免长等待
********************************************************************************************************/
void Driver_I2CSend(u8 Address,u8 *DataBuff,u16 DataLen)
{  	
  volatile u8 temp;//防止被优化而产生警告
  u16 time;
  
  time = 500;
  while(I2C->SR3&BIT(1))//等待总线空闲	
  if(!--time) 
  return;

  I2C->CR2 |= 0x01;//发起始条件  
  time = 500;
  while((I2C->SR1&BIT(0))==0)//等待发送完毕
  if(!--time) return; 
  asm("nop");//短暂延时
  asm("nop");
  asm("nop");
  temp = I2C->SR1;

  I2C->DR = Address;//发送地址
  time = 500;
  while((I2C->SR1&BIT(1))==0)//等待ACK应答
  if(!--time) return;
  asm("nop");//短暂延时
  asm("nop");
  asm("nop");
  temp = I2C->SR1;
  temp = I2C->SR3;//清ADDR标志

  //发送数据
  for(;DataLen>0;DataLen--,DataBuff++)
  {
    time = 500;
    while(!(I2C->SR1&BIT(7)))//等待寄存器为空
    if(!--time)return;
    I2C->DR = *DataBuff;
    time = 500;
    while(!(I2C->SR1&BIT(2)))//等待发送完毕
    if(!--time) return;
    asm("nop");
    asm("nop");
    asm("nop");
  }

  //发停止条件,关闭通信
  //清BTF位
  temp = I2C->SR1;
  temp = I2C->DR;
  I2C->CR2 |= BIT(1);//发停止 
}


/********************************************************************************************************
*  Function: Driver_I2CRecv						                                                           
*  Object: 硬件I2C接收 
*  输入： 从设备地址；待接收数据的头指针；待接收数据的长；
*  输出： 无 	                                     
*  备注:  通信中如果出现超时故障 则直接返回 避免长等待
********************************************************************************************************/
void Driver_I2CRecv(u8 Address,u8 *DataBuff,u16 DataLen)
{  	
  volatile u8 temp;//防止被优化而产生警告
  u16 time;
  
  time = 500;
  while(I2C->SR3&BIT(1))//等待总线空闲
  if(!--time)return;

  I2C->CR2 |= BIT(0);//发起始条件
  time = 500;
  while(!(I2C->SR1&BIT(0)))//等待发送完毕
  if(!--time)return;
  asm("nop");
  asm("nop");
  asm("nop");
  temp = I2C->SR1;

  I2C->DR = Address;//发从地址
  time = 500;
  while(!(I2C->SR1&BIT(1)))//等待ACK应答
  if(!--time)return;
  asm("nop");
  asm("nop");
  asm("nop");
  temp = I2C->SR1;
  temp = I2C->SR3;//清ADDR标志

  //接收数据,读DataLen-1个数
  //使能ACK应答
  I2C->CR2 |= BIT(2);
  for(;DataLen>1;DataLen--,DataBuff++)
  {
    time = 500;
    while(!(I2C->SR1&BIT(6)))//等待寄存器为满
    if(!--time)return;
    *DataBuff = I2C->DR;
  }
  I2C->CR2 &= ~BIT(2);//关闭ACK应答
  //发停止条件,关闭通信
  //清BTF位
  temp = I2C->SR1;
  temp = I2C->DR;
  //发停止
  I2C->CR2 |= BIT(1);
  asm("nop");
  asm("nop");
  asm("nop");

  //读最后一个数
  time = 500;
  while(!(I2C->SR1&BIT(6)))
  if(!--time)
  return;
  *DataBuff = I2C->DR;  		
}









