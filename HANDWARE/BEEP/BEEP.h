#ifndef __BEEP_H
#define __BEEP_H


/************************
	
	蜂鸣器的定义初始化
	
**************************/
#define BEEP PBout(7) //这样就可以直接操作led1

void BEEP_Init(void);//蜂鸣器初始化
void BEEP_Task(unsigned int nums);//蜂鸣器测试程序

#endif
