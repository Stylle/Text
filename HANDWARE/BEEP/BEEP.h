#ifndef __BEEP_H
#define __BEEP_H


/************************
	
	�������Ķ����ʼ��
	
**************************/
#define BEEP PBout(7) //�����Ϳ���ֱ�Ӳ���led1

void BEEP_Init(void);//��������ʼ��
void BEEP_Task(unsigned int nums);//���������Գ���

#endif
