#include "ESP8266.h"
#include "string.h"
#include "usart.h"
#include "usart3.h"
#include "stm32f10x.h"
#include "sys.h" 
#include "delay.h"
#include "LED.h"
#include "timer.h"

void esp8266_start_trans(void)
{
	//���ù���ģʽ 1��stationģʽ   2��APģʽ  3������ AP+stationģʽ
	esp8266_send_cmd("AT+CWMODE=2","OK",50);
	//Wifiģ������
	esp8266_send_cmd("AT+RST","OK",20);
	delay_ms(3000);         //��ʱ3S�ȴ������ɹ�
    //APģʽ
	esp8266_send_cmd("AT+CWSAP=\"ESP8266\",\"87654321\",1,4","OK",200);//������wifi������
	esp8266_send_cmd("AT+CIPMUX=1","OK",20);
	esp8266_send_cmd("AT+CIPSERVER=1,8080","OK",200);
}
//��ESP8266��������
//cmd:���͵������ַ���;ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��;waittime:�ȴ�ʱ��(��λ:10ms)
//����ֵ:0,���ͳɹ�(�õ����ڴ���Ӧ����);1,����ʧ��
u8 esp8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0; 
	USART3_RX_STA=0;
	u3_printf("%s\r\n",cmd);	//��������
	if(ack&&waittime)		//��Ҫ�ȴ�Ӧ��
	{
		while(--waittime)	//�ȴ�����ʱ
		{
			delay_ms(10);
			if(USART3_RX_STA&0X8000)//���յ��ڴ���Ӧ����
			{
				if(esp8266_check_cmd(ack))
				{
					printf("ack:%s\r\n",(u8*)ack);
					break;//�õ���Ч���� 
				}
					USART3_RX_STA=0;
			} 
		}
		if(waittime==0)res=1; 
	}
	return res;
} 
//ESP8266���������,�����յ���Ӧ��
//str:�ڴ���Ӧ����
//����ֵ:0,û�еõ��ڴ���Ӧ����;����,�ڴ�Ӧ������λ��(str��λ��)
u8* esp8266_check_cmd(u8 *str)
{
	char *strx=0;
	if(USART3_RX_STA&0X8000)		//���յ�һ��������
	{ 
		USART3_RX_BUF[USART3_RX_STA&0X7FFF]=0;//��ӽ�����
		strx=strstr((const char*)USART3_RX_BUF,(const char*)str);
	} 
	return (u8*)strx;
}

/*
��Ŀ����Ҫ���ݣ�STM32���ESP8266ģ������������ݽ���

ESP8266�����ӣ�USART3��PB10��PB11��

����ж����ݽ�����ȫ��
1�������˻��з���
2���������10ms�˶�û����һ�����ݣ�TIM7������10ms�Ķ�ʱ����
*/
void ESP_LED_Control()
{		
	char buf2[15];
	delay_init();	    	 			//��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 			//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	Uart_Init(115200);	 				//���ڳ�ʼ��Ϊ115200
	usart3_init(115200);	 				//���ڳ�ʼ��Ϊ115200
	LED_Init();
	 
	esp8266_start_trans();							//esp8266���г�ʼ�� 
	
	while(1)
	{
		if(USART3_RX_STA&0x8000)
		{
			printf("USART3_RX_BUF=%s\r\n",USART3_RX_BUF);
			sprintf(buf2,"%s",USART3_RX_BUF);
			printf("buf2=%s",buf2);
			if(strstr((const char*)buf2,"LED1ON"))  LED1 = 0;
				
			if(strstr((const char*)buf2,"LED1OFF")) LED1 = 1;
				
			USART3_RX_STA=0;
		}
	}
}
	
