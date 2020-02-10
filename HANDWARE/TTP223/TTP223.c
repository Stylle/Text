#include "TTP223.h"
#include "LED.h"
#include "delay.h"

void TTP223_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使能时钟GPIOA
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//设置输出模式这里“下拉输入”
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;  //设置指定IO口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //设置速率
	
	GPIO_Init(GPIOC,&GPIO_InitStructure);//端口选择
	GPIO_SetBits(GPIOC,GPIO_Pin_14);//设置端口PB7默认为高电平
	//GPIO_ResetBits(GPIOB,GPIO_Pin_7);//设置端口PB7默认为低电平
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
