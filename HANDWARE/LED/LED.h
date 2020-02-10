#ifndef __LED_H
#define __LED_H

#include "sys.h"

/************************
	
	LED灯的定义初始化
	
**************************/
#define LED1 PBout(5) //这样就可以直接操作led1
#define LED2 PBout(7) //这样就可以直接操作led1

void LED_Init(void);//LED初始化
void LED_Task(void);//跑马灯程序
void Uart_LED_Task(void);//串口LED
void LED_ON(u16 ch);
void LED_OFF(u16 ch);
void LEDBreathing_Lamp(void);//呼吸灯

#endif

