#include "TTP223.h"
#include "LED.h"
#include "delay.h"

void TTP223_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ʹ��ʱ��GPIOA
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//�������ģʽ����������롱
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;  //����ָ��IO��
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //��������
	
	GPIO_Init(GPIOC,&GPIO_InitStructure);//�˿�ѡ��
	GPIO_SetBits(GPIOC,GPIO_Pin_14);//���ö˿�PB7Ĭ��Ϊ�ߵ�ƽ
	//GPIO_ResetBits(GPIOB,GPIO_Pin_7);//���ö˿�PB7Ĭ��Ϊ�͵�ƽ
}
u8 TTP223_Scan(void)
{
	u8 key;
	if(IC_EKY == 1) key  = 1;
	else 			key  = 0;
	return key;
}

void IC_KEY_LED(void)
{
	u8 key;
	delay_init();
	LED_Init();
	TTP223_Init();
	while(1)
	{
		key = TTP223_Scan();
		if(key == 1)
		{
			delay_ms(1000);
			if(key == 1)	LED1 = ~LED1;
		}
	}
}
