#include "delay.h"
#include "stm32f10x.h"
#include "KEY.h"
#include "LED.h"
#include "usart.h"

void KEY_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure; 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PORTC,PORTBʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_6;//KEY0-KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC 8 6
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_14;//KEY2-KEY3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó�����������������ӵĸߵ�ƽ����Ҫ�������"GPIO_Mode_IPD"
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB 12 14
}

u8 KEY_Scan()
{
	u8 key;
	delay_init();
	if(KEY0 == 0)
	{
		delay_ms(20);//����
		if(KEY0 == 0)
		{
			while(!(KEY0 == 0));//��ⰴ���Ƿ���
			key = 0;
		}
	}
	else if(KEY1 == 0)
	{
		delay_ms(20);//����
		if(KEY1 == 0)
		{
			while(!(KEY1 == 0));//��ⰴ���Ƿ���
			key = 1;
		}
	}
	else if(KEY2 == 0)
	{
		delay_ms(20);//����
		if(KEY2 == 0)
		{
			while(!(KEY2 == 0));//��ⰴ���Ƿ���
			key = 2;
		}
	}
	else if(KEY3 == 0)
	{
		delay_ms(20);//����
		if(KEY3 == 0)
		{
			while(!(KEY3 == 0));//��ⰴ���Ƿ���
			key = 3;
		}
	}
	else key = 0XFF;
	return key;
}

void KEY_TaskLed(void)
{
	u8 key;
	LED_Init();
	KEY_Init();
	while(1)
	{
		key = KEY_Scan();
		switch(key)
		{
			case 0:LED1 = 1;break;
			case 1:LED1 = 0;break;
			case 2:LED2 = 1;break;
			case 3:LED2 = 0;break;
		//	defualt:break;
		}
	}
}

