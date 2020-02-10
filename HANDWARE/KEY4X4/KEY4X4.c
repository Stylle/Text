#include "KEY4X4.h"
#include "LED.h"
#include "stm32f10x.h"
#include "usart.h"
#include "stdio.h"

void KEY4X4_Init(void)
{
	GPIO_InitTypeDef GPIO_Initture;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��ʱ��GPIOA
	
	//��ʼ���С����������
	GPIO_Initture.GPIO_Mode = GPIO_Mode_Out_PP;//�������ģʽ������������
	GPIO_Initture.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_13 | GPIO_Pin_15;  //����ָ��IO��
	GPIO_Initture.GPIO_Speed = GPIO_Speed_50MHz;  //��������
	GPIO_Init(GPIOC,&GPIO_Initture);//�˿�ѡ��
	//GPIO_ResetBits(GPIOC,GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_13 | GPIO_Pin_15);//���ö˿�Ĭ��Ϊ�͵�ƽ
	//��ʼ���С��������롱
	GPIO_Initture.GPIO_Mode = GPIO_Mode_IPU;//�������ģʽ����������롱
	GPIO_Initture.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7;  //����ָ��IO��
	GPIO_Initture.GPIO_Speed = GPIO_Speed_50MHz;  //��������
	GPIO_Init(GPIOA,&GPIO_Initture);//�˿�ѡ��
	//GPIO_ResetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7);//���ö˿�Ĭ��Ϊ�͵�ƽ
}
u8 KEY4X4_Scan(void)
{
	u8 i, key;
	key = KEY4X4_NOPRESS;
	for(i=0;i<4;i++)
	{
    //��������͵�ƽ
		KEY4X4_H0 = 1;
		KEY4X4_H1 = 1;
		KEY4X4_H2 = 1; 
		KEY4X4_H3 = 1;
	switch(i)
	{
		case 0: KEY4X4_H0 = 0; break; //��0������͵�ƽ
		case 1: KEY4X4_H1 = 0; break; //��1������͵�ƽ
		case 2: KEY4X4_H2 = 0; break; //��2������͵�ƽ
		case 3: KEY4X4_H3 = 0; break; //��3������͵�ƽ
		default: break;
	}
  //��ȡ����״̬
	 if(KEY4X4_L0 == 0)            //��0�а��£����ص͵�ƽ
		key = (i<<2) + 0;
	 else if (KEY4X4_L1 == 0)      //��1�а��£����ص͵�ƽ
		key = (i<<2) + 1;
	 else if (KEY4X4_L2 == 0)      //��2�а��£����ص͵�ƽ
		key = (i<<2) + 2;
	 else if (KEY4X4_L3 == 0)      //��3�а��£����ص͵�ƽ
		key = (i<<2) + 3;
	 }
	return key; //���ؼ�ֵ
}

void KEY4x4_LEDControl(void)
{
	u8 key;
	KEY4X4_Init();//������̳�ʼ��
	LED_Init();
	Uart_Init(115200);//���ڳ�ʼ��
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();
	while(1)
	{
		key = KEY4X4_Scan();
		delay_ms(10);//��ʱ����
		//printf("���� %d ����\r\n",key);
		if(key==0XFF) 	LED1 = 0;
		else 			LED1 = 1;
	}
}

