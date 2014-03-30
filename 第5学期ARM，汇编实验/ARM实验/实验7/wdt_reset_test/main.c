#include "2440addr.h"
#include "2440lib.h"


//初始化函数
void wdt_init()
{
	//设置分频参数
	rWTCON &= ~(255<<8);
	rWTCON |= (249<<8);
	rWTCON &= ~(3<<3);
	//计时常数
	rWTCNT = 50000;
	//开始
	rWTCON |= (1<<0);
	rWTCON |= (0<<2);
	rWTCON |= (1<<5);
}

void Main(void)
{	
	//初始化串口0以方便调试
	Uart0_Init_all();
	//调用初始化程序
	wdt_init();
	while(1)
	{
		Uart_Printf("\n%s\n", "4秒钟内按下任意键，否则系统重启！");
		Uart_Getch();
		rWTCNT = 50000;
	}
}