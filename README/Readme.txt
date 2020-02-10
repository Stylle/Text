/*************************************************

在这个文件中存储我在学习过程中遇到的一些问题

core目录：启动文件目录核心目录
User：主程序的调用目录
Lib：库文件的存储目录
System：正点原子的通用库函数
HANDWARE：个人程序存储目录
README:问题收集目录


软件使用：创建完工程文件过后设置烧录器
debug选项中sw下载模式10m左右，flash选项中选择reset and run
output里面三个选项全部打勾生成hex文件方便使用ch340烧录器下载
包含创建的新目录在c/c++下面的include path下面包含目录

STM32的I0口相比51而言要复杂得多，所以使用起来也困难很多。
首先STM32的I0口可以由软件配置成如下8种模式: 
输入模式
    -输入浮空（GPIO_Mode_IN_FLOATING）
    -输入上拉(GPIO_Mode_IPU)
    -输入下拉(GPIO_Mode_IPD)
    -模拟输入(GPIO_Mode_AIN)

输出模式
    -开漏输出(GPIO_Mode_Out_OD)
    -开漏复用功能(GPIO_Mode_AF_OD)
    -推挽式输出(GPIO_Mode_Out_PP)
    -推挽式复用功能(GPIO_Mode_AF_PP)

Keil窗口布局打乱了点击Window->Reset View to Defaults即可恢复默认窗口布局

”..\OBJ\Temp.axf: Error: L6218E: Undefined symbol KEY_TaskLed (referred from main.o).
Not enough information to list image symbols.“
报这个错误表示工程目录中没有添加这个文件也就是在软件中添加

..\HANDWARE\KEY\KEY.c(68): error:  #268: declaration may not appear after executable statement in block
定义变量不可以在可执行程序过后

..\HANDWARE\KEY\KEY.c(81): warning:  #1-D: last line of file ends without a newline
提示程序最后一行没有回车这是keil5的bug

extern 表示申明函数不是定义函数，表示在其他模块里面寻找这个变量

typedef 定义可以多重定义define和这个有点像但是typedef是专门定义类型的

触摸按键ttp223默认输出低电平触摸输出高电平

stm32有8个16位定时器分成3个组；

基本定时器（TIM6，TIM7）的主要功能：

只有最基本的定时功能，。基本定时器TIM6和TIM7各包含一个16位自动装载计数器，由各自的可编程预分频器驱动

通用定时器（TIM2~TIM5）的主要功能：

除了基本的定时器的功能外，还具有测量输入信号的脉冲长度（ 输入捕获） 或者产生输出波形（ 输出比较和PWM）

高级定时器（TIM1，TIM8）的主要功能：

高级定时器不但具有基本，通用定时器的所有的功能，还具有控制交直流电动机所有的功能，你比如它可以输出6路互补带死区的信号，刹车功能等等

点击下载程序的时候如果没有插入下载器软件就会停止工作

**************************************************/