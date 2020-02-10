#include "stm32f10x.h"
#include "delay.h"
#include "LED.h"
#include "BEEP.h"
#include "KEY.h"
#include "ESP8266.h"
#include "KEY4X4.h"
#include "TTP223.h"
#include "SG90.h"
#include "ULN2003.h"
#include "m7seg.h"

/**********************************

	      主程序的调用

**********************************/

int main(void)
{	
	//BEEP_Task(10);蜂鸣器的测试程序
	//LED_Task();//LED的测试程序
	//KEY_Ta skLed();//按键控制LED灯
	//Uart_LED_Task();//串口与led
	//ESP_LED_Control();//ESP8266控制led
	//KEY4x4_LEDControl();//偶数按键开灯
	//IC_KEY_LED();//触摸开关开灯实验
	//LEDBreathing_Lamp();//呼吸灯实验
	//SG90_KEYControl();
	//ULN2003_Task();//按键控制步进电机
	IRQ_M7SEG_Clock();//时钟
}
