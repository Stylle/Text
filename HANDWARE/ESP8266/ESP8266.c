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
	//设置工作模式 1：station模式   2：AP模式  3：兼容 AP+station模式
	esp8266_send_cmd("AT+CWMODE=2","OK",50);
	//Wifi模块重启
	esp8266_send_cmd("AT+RST","OK",20);
	delay_ms(3000);         //延时3S等待重启成功
    //AP模式
	esp8266_send_cmd("AT+CWSAP=\"ESP8266\",\"87654321\",1,4","OK",200);//这里是wifi的配置
	esp8266_send_cmd("AT+CIPMUX=1","OK",20);
	esp8266_send_cmd("AT+CIPSERVER=1,8080","OK",200);
}
//向ESP8266发送命令
//cmd:发送的命令字符串;ack:期待的应答结果,如果为空,则表示不需要等待应答;waittime:等待时间(单位:10ms)
//返回值:0,发送成功(得到了期待的应答结果);1,发送失败
u8 esp8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0; 
	USART3_RX_STA=0;
	u3_printf("%s\r\n",cmd);	//发送命令
	if(ack&&waittime)		//需要等待应答
	{
		while(--waittime)	//等待倒计时
		{
			delay_ms(10);
			if(USART3_RX_STA&0X8000)//接收到期待的应答结果
			{
				if(esp8266_check_cmd(ack))
				{
					printf("ack:%s\r\n",(u8*)ack);
					break;//得到有效数据 
				}
					USART3_RX_STA=0;
			} 
		}
		if(waittime==0)res=1; 
	}
	return res;
} 
//ESP8266发送命令后,检测接收到的应答
//str:期待的应答结果
//返回值:0,没有得到期待的应答结果;其他,期待应答结果的位置(str的位置)
u8* esp8266_check_cmd(u8 *str)
{
	char *strx=0;
	if(USART3_RX_STA&0X8000)		//接收到一次数据了
	{ 
		USART3_RX_BUF[USART3_RX_STA&0X7FFF]=0;//添加结束符
		strx=strstr((const char*)USART3_RX_BUF,(const char*)str);
	} 
	return (u8*)strx;
}

/*
项目的主要内容：STM32配合ESP8266模块与服务器数据交互

ESP8266的连接：USART3（PB10、PB11）

如何判断数据接收完全？
1、出现了换行符；
2、如果超过10ms了都没有下一条数据（TIM7来进行10ms的定时）。
*/
void ESP_LED_Control()
{		
	char buf2[15];
	delay_init();	    	 			//延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 			//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	Uart_Init(115200);	 				//串口初始化为115200
	usart3_init(115200);	 				//串口初始化为115200
	LED_Init();
	 
	esp8266_start_trans();							//esp8266进行初始化 
	
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
	
