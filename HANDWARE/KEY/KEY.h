#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

/************************
	
	���������Ķ����ʼ��
	
**************************/
#define KEY0 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)//��ȡ����״̬
#define KEY1 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)
#define KEY2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)
#define KEY3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)

void KEY_Init(void);//����������ʼ��
u8 KEY_Scan(void);//������ȡ
void KEY_TaskLed(void);//��������led��

#endif
