#include "KEY4X4.h"
#include "LED.h"
#include "stm32f10x.h"
#include "usart.h"
#include "stdio.h"

void KEY4X4_Init(void)
{
	GPIO_InitTypeDef GPIO_Initture;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能时钟GPIOA
	
	//初始化行“推完输出”
	GPIO_Initture.GPIO_Mode = GPIO_Mode_Out_PP;//设置输出模式这里“推挽输出”
	GPIO_Initture.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_13 | GPIO_Pin_15;  //设置指定IO口
	GPIO_Initture.GPIO_Speed = GPIO_Speed_50MHz;  //设置速率
	GPIO_Init(GPIOC,&GPIO_Initture);//端口选择
	//GPIO_ResetBits(GPIOC,GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_13 | GPIO_Pin_15);//设置端口默认为低电平
	//初始化列“上拉输入”
	GPIO_Initture.GPIO_Mode = GPIO_Mode_IPU;//设置输出模式这里“上拉输入”
	GPIO_Initture.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7;  //设置指定IO口
	GPIO_Initture.GPIO_Speed = GPIO_Speed_50MHz;  //设置速率
	GPIO_Init(GPIOA,&GPIO_Initture);//端口选择
	//GPIO_ResetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7);//设置端口默认为低电平
}
u8 KEY4X4_Scan(void)
{
	u8 i, key;
	key = KEY4X4_NOPRESS;
	for(i=0;i<4;i++)
	{
    //行线输出低电平
		KEY4X4_H0 = 1;
		KEY4X4_H1 = 1;
		KEY4X4_H2 = 1; 
		KEY4X4_H3 = 1;
	switch(i)
	{
		case 0: KEY4X4_H0 = 0; break; //第0行输出低电平
		case 1: KEY4X4_H1 = 0; break; //第1行输出低电平
		case 2: KEY4X4_H2 = 0; break; //第2行输出低电平
		case 3: KEY4X4_H3 = 0; break; //第3行输出低电平
		default: break;
	}
  //读取列线状态
	 if(KEY4X4_L0 == 0)            //第0列按下，读回低电平
		key = (i<<2) + 0;
	 else if (KEY4X4_L1 == 0)      //第1列按下，读回低电平
		key = (i<<2) + 1;
	 else if (KEY4X4_L2 == 0)      //第2列按下，读回低电平
		key = (i<<2) + 2;
	 else if (KEY4X4_L3 == 0)      //第3列按下，读回低电平
		key = (i<<2) + 3;
	 }
	return key; //返回键值
}

void KEY4x4_LEDControl(void)
{
	u8 key;
	KEY4X4_Init();//矩阵键盘初始化
	LED_Init();
	Uart_Init(115200);//串口初始化
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	delay_init();
	while(1)
	{
		key = KEY4X4_Scan();
		delay_ms(10);//延时消抖
		//printf("按键 %d 按下\r\n",key);
		if(key==0XFF) 	LED1 = 0;
		else 			LED1 = 1;
	}
}

