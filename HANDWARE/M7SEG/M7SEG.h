#ifndef _M7SEG_H
#define _M7SEG_H
#include "sys.h"

#define M7SEG_PORT GPIOA->ODR

#define M7SEG_BIT1 PBout(0)
#define M7SEG_BIT2 PBout(1)
#define M7SEG_BIT3 PBout(10)
#define M7SEG_BIT4 PBout(11)

void M7SEG_Port_Init(void);//段led初始化
void M7SEG_Bit_Init(void);//位选初始化
void M7SEG_Init(void);//数码管初始化
void M7SEG_Display(void);//数码管显示
void IRQ_M7SEG_Clock(void);//时钟

#endif

