#include "LED.h"
#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"

void LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//GPIOB
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��ʱ��GPIOA
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������ģʽ������������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;  //����ָ��IO��
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //��������
	GPIO_Init(GPIOB,&GPIO_InitStructure);//�˿�ѡ��
	GPIO_SetBits(GPIOB,GPIO_Pin_5);//���ö˿�PB5Ĭ��Ϊ�ߵ�ƽ
	//GPIO_ResetBits(GPIOB,GPIO_Pin_5);//���ö˿�PB5Ĭ��Ϊ�͵�ƽ
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������ģʽ������������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  //����ָ��IO��
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //��������
	GPIO_Init(GPIOB,&GPIO_InitStructure);//�˿�ѡ��
	GPIO_SetBits(GPIOB,GPIO_Pin_7);//���ö˿�PA5Ĭ��Ϊ�ߵ�ƽ
}
void LED_Task(void)
{
	LED_Init();
	delay_init();
	while(1)
	{
//		GPIO_SetBits(GPIOB,GPIO_Pin_5);
//		GPIO_SetBits(GPIOA,GPIO_Pin_5);//Ϩ������led��
//		
		//λ��������ʼ����������
//   	PBout(5) = 1;
		PBout(7) = 1;
		LED1 = 1;//��ͷ�ļ��궨��PBout��5��ΪLED1 
		
		delay_ms(100);
//		
//		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_5);//����led��
		
		//λ����
		PBout(5) = 0;
		PBout(7) = 0;
		
		delay_ms(100);
	}
}
void Uart_LED_Task(void)
{
	u16 t,buf[200];
	int ch;
	u16 len;	
	u16 times=0;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	Uart_Init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
 	while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				buf[t] = USART_RX_BUF[t];
				USART_SendData(USART1, USART_RX_BUF[t]);//�򴮿�1��������
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			}
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;				
			if(buf[0] =='L'&& buf[1]=='E'&&buf[2]=='D')
			{
				ch = buf[3] - 0X30; //��ȡͨ����
         		if(ch >= 0 && ch <= 7) //�ж�ͨ�����Ƿ�Ϊ0-7
				{
					if (buf[4] == 'O' && buf[5] == 'N')
					{
						LED_ON(ch);
					}
					else if(buf[4] =='O'&& buf[5] == 'F' && buf[6] == 'F')
					{
						LED_OFF(ch);
					 }
				}
			}	

		}
		else
		{
			times++;
			//if(times%2000==0)printf("����������,�Իس�������\n");  
			//if(times%30==0)LED1=!LED1;//��˸LED,��ʾϵͳ��������.
			delay_ms(10);   
		}
	}	 

}
void LED_ON(u16 ch)
{
  switch(ch)
  {
    case 1:LED1 = 0;printf("����LED1\r\n\r\n");break;
    case 2:LED2 = 0;printf("����LED2\r\n\r\n");break;
  default:break;
  }
}

void LED_OFF(u16 ch)
{
  switch(ch)
  {
    case 1:LED1 = 1;printf("�ر�LED2\r\n\r\n");break;
    case 2:LED2 = 1;printf("�ر�LED2\r\n\r\n");break;
  default:break;
  }
}
void LEDBreathing_Lamp(void)
{
	u16 PWM_Low = 0,CYCLE = 1100;
	LED_Init();
	delay_init();
	while(1)
	{
		LED1 = 0;
		for(PWM_Low = 1;PWM_Low < CYCLE;PWM_Low++)
		{ 
		//PWM_LOW��ʾ��
	 	//��ƽʱ�䣬���ѭ���е͵�ƽʱ����1�ۼӵ�CYCLE�����ڣ���ֵ����500��
	   		LED1 = 0;        //����LED  
	   		delay_us(PWM_Low);//��ʱ���ȣ�500��ѭ���д�1����599
	   		LED1 = 1;        //Ϩ��LED
	  	    delay_us(CYCLE-PWM_Low);//��ʱ���ȣ�500��ѭ���д�499����1    
	   }
	   LED1 = 1;
	   for(PWM_Low = CYCLE - 1;PWM_Low > 0;PWM_Low--)
	   { 
	   		LED1 = 0;      
	   		delay_us(PWM_Low);
	   		LED1 = 1;       
	  	    delay_us(CYCLE-PWM_Low);   
	   }
   }
}

