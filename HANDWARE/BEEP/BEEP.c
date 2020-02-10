#include "stm32f10x.h"
#include "BEEP.h"
#include "delay.h"

void BEEP_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��ʱ��GPIOA
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������ģʽ������������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  //����ָ��IO��
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //��������
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);//�˿�ѡ��
	GPIO_SetBits(GPIOB,GPIO_Pin_7);//���ö˿�PB7Ĭ��Ϊ�ߵ�ƽ
	//GPIO_ResetBits(GPIOB,GPIO_Pin_7);//���ö˿�PB7Ĭ��Ϊ�͵�ƽ
}

void BEEP_Task(unsigned int nums)
{
	BEEP_Init();//��ʼ��
	delay_init();
	while(1)
	{
		BEEP = 0;
		delay_ms(nums);
		BEEP = 1;
		delay_ms(nums);
	}
}
