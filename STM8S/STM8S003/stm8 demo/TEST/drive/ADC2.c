#include "stm8s.h"
#include "delay.h"
#include "ADC2.h"


void ADC2_Init(void)
{
  ADC2->CR1 |= 0x01;//从睡眠模式唤醒
  ADC2->CR2 &= 0xF7; // A/D结果数据左对齐
  ADC2->CR1 = 0x60; // ADC时钟=主时钟/12=1.333MHZ;ADC转换模式=单次;禁止ADC转换
  ADC2->TDRH = 0XFF;//禁止施密特触发器
  ADC2->TDRL = 0XFF;
}

float ADC2_ReadOnce(u8 chx)
{
  u8 val_h=0,val_l=0,i=0;
  u16 val=0;
  float volate=0;
  
  ADC2->CSR = chx;//选择通道
  ADC2->CR1 |= 0x01; // CR1寄存器的最低位置1，使能ADC转换
  for(i=0;i<100;i++);// 延时一段时间，保证ADC模块的上电完成
  ADC2->CR1 |= 0x01; // 将CR1寄存器的最低位置1
  while(!(ADC2->CSR & 0x80)); // 等待ADC结束
  val_h =(u8)ADC2->DRH; // 读出ADC结果的高8位
  val_l =(u8)ADC2->DRL; // 读出ADC结果的低8位
  val=(val_h<<2)+val_l;//合并值
  volate=3.3f*val/1024;//计算出电压值
  return volate;
}


