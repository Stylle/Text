#ifndef __ULN2003_H
#define __ULN2003_H

#include "sys.h"

/***************************************
	
	ULN2003驱动步进电机的定义初始化
	
****************************************/
#define IN1 PCout(0) 
#define IN2 PCout(1) 
#define IN3 PCout(2) 
#define IN4 PCout(3) 

void ULN2003_Init(void);//初始化
void ULN2003_Task(void);//按键控制正反转
void ULN2003_Left(void);
void ULN2003_Right(void);

#endif

