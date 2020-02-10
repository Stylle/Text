#include "stm32f10x.h"
#include "BEEP.h"
#include "delay.h"

void BEEP_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能时钟GPIOA
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//设置输出模式这里“推挽输出”
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  //设置指定IO口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //设置速率
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);//端口选择
	GPIO_SetBits(GPIOB,GPIO_Pin_7);//设置端口PB7默认为高电平
	//GPIO_ResetBits(GPIOB,GPIO_Pin_7);//设置端口PB7默认为低电平
}

void BEEP_Task(unsigned int nums)
{
	BEEP_Init();//初始化
	delay_init();
	while(1)
	{
		BEEP = 0;
		delay_ms(nums);
		BEEP = 1;
		delay_ms(nums);
	}
}
