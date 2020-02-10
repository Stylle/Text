#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

/************************
	
	独立按键的定义初始化
	
**************************/
#define KEY0 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)//读取按键状态
#define KEY1 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)
#define KEY2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)
#define KEY3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)

void KEY_Init(void);//独立按键初始化
u8 KEY_Scan(void);//按键读取
void KEY_TaskLed(void);//按键控制led灯

#endif
