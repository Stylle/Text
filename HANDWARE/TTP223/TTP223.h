#ifndef __TTP223_H
#define __TTP223_H

#include "stm32f10x.h"
#include "sys.h"
/************************
	
	���������Ķ����ʼ��
	
**************************/

#define IC_EKY PCin(14) 

void TTP223_Init(void);
u8 	 TTP223_Scan(void);//������������ֵ
void IC_KEY_LED(void);

#endif
