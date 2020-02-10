#ifndef _M7SEG_H
#define _M7SEG_H
#include "sys.h"

#define M7SEG_PORT GPIOA->ODR

#define M7SEG_BIT1 PBout(0)
#define M7SEG_BIT2 PBout(1)
#define M7SEG_BIT3 PBout(10)
#define M7SEG_BIT4 PBout(11)

void M7SEG_Port_Init(void);//��led��ʼ��
void M7SEG_Bit_Init(void);//λѡ��ʼ��
void M7SEG_Init(void);//����ܳ�ʼ��
void M7SEG_Display(void);//�������ʾ
void IRQ_M7SEG_Clock(void);//ʱ��

#endif

