#ifndef __KEY4X4_H
#define __KEY4X4_H
#include "sys.h"
#include "delay.h"

/************************
	
	������̵Ķ����ʼ��
	
**************************/
//����
#define KEY4X4_H0	PCout(13) 
#define KEY4X4_H1	PCout(15)
#define KEY4X4_H2	PCout(1)     
#define KEY4X4_H3	PCout(3)     
//����
#define KEY4X4_L0	PAin(1)     
#define KEY4X4_L1	PAin(3)      
#define KEY4X4_L2	PAin(5)     
#define KEY4X4_L3	PAin(7)//���������ȡʱӦ��PXin��x��

#define KEY4X4_NOPRESS  0XFF//û�а������µ�ʱ�򷵻ص�ֵ

void KEY4X4_Init(void);//����������ʼ��
u8 KEY4X4_Scan(void);//������ȡ
//void KEY4X4_WaitUp(void);//��ⰴ������������
void KEY4x4_LEDControl(void);//��������led����

#endif

