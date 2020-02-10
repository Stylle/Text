#include "stm32f10x.h"
#include "delay.h"
#include "ULN2003.h"
#include "key.h"

u32 k = 2600;//转动速度

void ULN2003_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//GPIOB

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//设置输出模式这里“推挽输出”
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;  //设置指定IO口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //设置速率
	GPIO_Init(GPIOC,&GPIO_InitStructure);//端口选择
	GPIO_ResetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);//设置端口默认为高电平
}

void ULN2003_Left()
{
	IN1 = 1;
	delay_us(k);
	IN1 = 0;
	IN2 = 1;
	delay_us(k);
	IN2 = 0;
	IN3 = 1;
	delay_us(k);
	IN3 = 0;
	IN4 = 1;
	delay_us(k);
	IN4 = 0;	
}

void ULN2003_Right()
{
	IN4 = 1;
	delay_us(k);
	IN4 = 0;
	IN3 = 1;
	delay_us(k);
	IN3 = 0;
	IN2 = 1;
	delay_us(k);
	IN2 = 0;
	IN1 = 1;
	delay_us(k);
	IN1 = 0;
}
void ULN2003_Task()
{
	u8 flag = 0,key;
	ULN2003_Init();
	delay_init();
	KEY_Init();
	while(1)
	{
		key = KEY_Scan();
		switch(key)
		{
			case 0:flag = 1;break;
			case 1:flag = 2;break;
			case 2:flag = 3;break;
			case 3:flag = 0;break;
		}
		switch(flag)
		{
			case 0:break;
			case 1:ULN2003_Right();break;
			case 2:ULN2003_Left();break;
			case 3:ULN2003_Left();break;
		}
		
	}
}
