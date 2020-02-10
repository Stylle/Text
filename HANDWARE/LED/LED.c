#include "LED.h"
#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"

void LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//GPIOB
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能时钟GPIOA
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//设置输出模式这里“推挽输出”
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;  //设置指定IO口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //设置速率
	GPIO_Init(GPIOB,&GPIO_InitStructure);//端口选择
	GPIO_SetBits(GPIOB,GPIO_Pin_5);//设置端口PB5默认为高电平
	//GPIO_ResetBits(GPIOB,GPIO_Pin_5);//设置端口PB5默认为低电平
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//设置输出模式这里“推挽输出”
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  //设置指定IO口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //设置速率
	GPIO_Init(GPIOB,&GPIO_InitStructure);//端口选择
	GPIO_SetBits(GPIOB,GPIO_Pin_7);//设置端口PA5默认为高电平
}
void LED_Task(void)
{
	LED_Init();
	delay_init();
	while(1)
	{
//		GPIO_SetBits(GPIOB,GPIO_Pin_5);
//		GPIO_SetBits(GPIOA,GPIO_Pin_5);//熄灭两个led灯
//		
		//位操作，初始化不可以少
//   	PBout(5) = 1;
		PBout(7) = 1;
		LED1 = 1;//在头文件宏定义PBout（5）为LED1 
		
		delay_ms(100);
//		
//		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_5);//点亮led灯
		
		//位操作
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
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	Uart_Init(115200);	 //串口初始化为115200
 	LED_Init();			     //LED端口初始化
 	while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				buf[t] = USART_RX_BUF[t];
				USART_SendData(USART1, USART_RX_BUF[t]);//向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			}
			printf("\r\n\r\n");//插入换行
			USART_RX_STA=0;				
			if(buf[0] =='L'&& buf[1]=='E'&&buf[2]=='D')
			{
				ch = buf[3] - 0X30; //读取通道号
         		if(ch >= 0 && ch <= 7) //判断通道号是否为0-7
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
			//if(times%2000==0)printf("请输入数据,以回车键结束\n");  
			//if(times%30==0)LED1=!LED1;//闪烁LED,提示系统正在运行.
			delay_ms(10);   
		}
	}	 

}
void LED_ON(u16 ch)
{
  switch(ch)
  {
    case 1:LED1 = 0;printf("点亮LED1\r\n\r\n");break;
    case 2:LED2 = 0;printf("点亮LED2\r\n\r\n");break;
  default:break;
  }
}

void LED_OFF(u16 ch)
{
  switch(ch)
  {
    case 1:LED1 = 1;printf("关闭LED2\r\n\r\n");break;
    case 2:LED2 = 1;printf("关闭LED2\r\n\r\n");break;
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
		//PWM_LOW表示低
	 	//电平时间，这个循环中低电平时长从1累加到CYCLE（周期）的值，即500次
	   		LED1 = 0;        //点亮LED  
	   		delay_us(PWM_Low);//延时长度，500次循环中从1加至599
	   		LED1 = 1;        //熄灭LED
	  	    delay_us(CYCLE-PWM_Low);//延时长度，500次循环中从499减至1    
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

