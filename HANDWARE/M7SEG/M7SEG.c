#include "delay.h"
#include "stm32f10x.h"
#include "KEY4x4.h"
#include "m7seg.h"
#include "timer.h"
#include "KEY.h"
#include "LED.h"
//说明：位选端口为PB0、1、10、11
//段led端口为：PA0 - - PA7
u16 hour = 22, min = 23,num = 0 ;

unsigned int TAB_CA[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,
                        0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,0xFF};//段码
void M7SEG_Port_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//设置输出模式这里“推挽输出”
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;  //设置指定IO口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //设置速率
	GPIO_Init(GPIOA,&GPIO_InitStructure);//端口选择
	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);//设置端口PB5默认为高电平
}
void M7SEG_Bit_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//GPIOB
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//设置输出模式这里“推挽输出”
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_10|GPIO_Pin_11;  //设置指定IO口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //设置速率
	GPIO_Init(GPIOB,&GPIO_InitStructure);//端口选择
	GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_10|GPIO_Pin_11);//设置端口PB5默认为高电平
}

void M7SEG_Init()
{
	M7SEG_Port_Init();
	M7SEG_Bit_Init();
}

void M7SEG_Display()
{
  u16 temp[4],k; //存放要显示的数值和刷新速率

  M7SEG_Init();// 初始化段选和位选端口
  delay_init();
  k=2;

  temp[3] = 1;//千位
  temp[2] = 2;//百位
  temp[1] = 3;//十位
  temp[0] = 4;//个位
  
 while(1)
{
  //千位
  M7SEG_PORT = TAB_CA[temp[3]]; //送段码
  M7SEG_BIT1 = 0; //打开位选，开始显示该位数据
  delay_ms(k);//延时，控制显示时间和刷新时间
  M7SEG_BIT1 = 1; //关闭位选，结束显示该位数据
  //百位
  M7SEG_PORT = TAB_CA[temp[2]];
  M7SEG_BIT2 = 0;
  delay_ms(k);
  M7SEG_BIT2 = 1;
  //十位
  M7SEG_PORT = TAB_CA[temp[1]];
  M7SEG_BIT3 = 0;
  delay_ms(k);
  M7SEG_BIT3 = 1;
  //个位
  M7SEG_PORT = TAB_CA[temp[0]];
  M7SEG_BIT4 = 0;
  delay_ms(k) ;
  M7SEG_BIT4 = 1;    
  }
}

void IRQ_M7SEG_Clock(void)
{
	u16 temp[4],k,delay_s; //存放要显示的数值和刷新速率
	TIM7_Int_Init(9999,7199);
	M7SEG_Init();// 初始化段选和位选端口
	delay_init();
	k=2;
	while(1)
	{
		delay_s++;
		
		temp[0] = min%10;//千位
		temp[1] = min/10;//百位
		temp[2] = hour%10;//十位
		temp[3] = hour/10;//个位
			
		//千位
		M7SEG_PORT = TAB_CA[temp[3]]; //送段码
		M7SEG_BIT1 = 0; //打开位选，开始显示该位数据
		delay_ms(k);//延时，控制显示时间和刷新时间
		M7SEG_BIT1 = 1; //关闭位选，结束显示该位数据
		if(delay_s >= 80)
		{
			//百位
			M7SEG_PORT = TAB_CA[temp[2]] + 0x80;
			M7SEG_BIT2 = 0;
			delay_ms(k);
			M7SEG_BIT2 = 1;
			if(delay_s == 150)  delay_s = 0;
		}
		else
		{
			//百位
			M7SEG_PORT = TAB_CA[temp[2]];
			M7SEG_BIT2 = 0;
			delay_ms(k);
			M7SEG_BIT2 = 1;
		}
		//十位
		M7SEG_PORT = TAB_CA[temp[1]];
		M7SEG_BIT3 = 0;
		delay_ms(k);
		M7SEG_BIT3 = 1;
		//个位
		M7SEG_PORT = TAB_CA[temp[0]];
		M7SEG_BIT4 = 0;
		delay_ms(k) ;
		M7SEG_BIT4 = 1; 
	}  
}
