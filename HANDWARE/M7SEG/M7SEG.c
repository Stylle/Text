#include "delay.h"
#include "stm32f10x.h"
#include "KEY4x4.h"
#include "m7seg.h"
#include "timer.h"
#include "KEY.h"
#include "LED.h"
//˵����λѡ�˿�ΪPB0��1��10��11
//��led�˿�Ϊ��PA0 - - PA7
u16 hour = 22, min = 23,num = 0 ;

unsigned int TAB_CA[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,
                        0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,0xFF};//����
void M7SEG_Port_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������ģʽ������������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;  //����ָ��IO��
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //��������
	GPIO_Init(GPIOA,&GPIO_InitStructure);//�˿�ѡ��
	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);//���ö˿�PB5Ĭ��Ϊ�ߵ�ƽ
}
void M7SEG_Bit_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//GPIOB
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������ģʽ������������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_10|GPIO_Pin_11;  //����ָ��IO��
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //��������
	GPIO_Init(GPIOB,&GPIO_InitStructure);//�˿�ѡ��
	GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_10|GPIO_Pin_11);//���ö˿�PB5Ĭ��Ϊ�ߵ�ƽ
}

void M7SEG_Init()
{
	M7SEG_Port_Init();
	M7SEG_Bit_Init();
}

void M7SEG_Display()
{
  u16 temp[4],k; //���Ҫ��ʾ����ֵ��ˢ������

  M7SEG_Init();// ��ʼ����ѡ��λѡ�˿�
  delay_init();
  k=2;

  temp[3] = 1;//ǧλ
  temp[2] = 2;//��λ
  temp[1] = 3;//ʮλ
  temp[0] = 4;//��λ
  
 while(1)
{
  //ǧλ
  M7SEG_PORT = TAB_CA[temp[3]]; //�Ͷ���
  M7SEG_BIT1 = 0; //��λѡ����ʼ��ʾ��λ����
  delay_ms(k);//��ʱ��������ʾʱ���ˢ��ʱ��
  M7SEG_BIT1 = 1; //�ر�λѡ��������ʾ��λ����
  //��λ
  M7SEG_PORT = TAB_CA[temp[2]];
  M7SEG_BIT2 = 0;
  delay_ms(k);
  M7SEG_BIT2 = 1;
  //ʮλ
  M7SEG_PORT = TAB_CA[temp[1]];
  M7SEG_BIT3 = 0;
  delay_ms(k);
  M7SEG_BIT3 = 1;
  //��λ
  M7SEG_PORT = TAB_CA[temp[0]];
  M7SEG_BIT4 = 0;
  delay_ms(k) ;
  M7SEG_BIT4 = 1;    
  }
}

void IRQ_M7SEG_Clock(void)
{
	u16 temp[4],k,delay_s; //���Ҫ��ʾ����ֵ��ˢ������
	TIM7_Int_Init(9999,7199);
	M7SEG_Init();// ��ʼ����ѡ��λѡ�˿�
	delay_init();
	k=2;
	while(1)
	{
		delay_s++;
		
		temp[0] = min%10;//ǧλ
		temp[1] = min/10;//��λ
		temp[2] = hour%10;//ʮλ
		temp[3] = hour/10;//��λ
			
		//ǧλ
		M7SEG_PORT = TAB_CA[temp[3]]; //�Ͷ���
		M7SEG_BIT1 = 0; //��λѡ����ʼ��ʾ��λ����
		delay_ms(k);//��ʱ��������ʾʱ���ˢ��ʱ��
		M7SEG_BIT1 = 1; //�ر�λѡ��������ʾ��λ����
		if(delay_s >= 80)
		{
			//��λ
			M7SEG_PORT = TAB_CA[temp[2]] + 0x80;
			M7SEG_BIT2 = 0;
			delay_ms(k);
			M7SEG_BIT2 = 1;
			if(delay_s == 150)  delay_s = 0;
		}
		else
		{
			//��λ
			M7SEG_PORT = TAB_CA[temp[2]];
			M7SEG_BIT2 = 0;
			delay_ms(k);
			M7SEG_BIT2 = 1;
		}
		//ʮλ
		M7SEG_PORT = TAB_CA[temp[1]];
		M7SEG_BIT3 = 0;
		delay_ms(k);
		M7SEG_BIT3 = 1;
		//��λ
		M7SEG_PORT = TAB_CA[temp[0]];
		M7SEG_BIT4 = 0;
		delay_ms(k) ;
		M7SEG_BIT4 = 1; 
	}  
}
