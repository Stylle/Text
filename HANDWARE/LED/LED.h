#ifndef __LED_H
#define __LED_H

#include "sys.h"

/************************
	
	LED�ƵĶ����ʼ��
	
**************************/
#define LED1 PBout(5) //�����Ϳ���ֱ�Ӳ���led1
#define LED2 PBout(7) //�����Ϳ���ֱ�Ӳ���led1

void LED_Init(void);//LED��ʼ��
void LED_Task(void);//����Ƴ���
void Uart_LED_Task(void);//����LED
void LED_ON(u16 ch);
void LED_OFF(u16 ch);
void LEDBreathing_Lamp(void);//������

#endif

