#include "2440addr.h"
#include "2440lib.h"

void delay(void)
{
	int i;
	for(i=0; i<10000000; i++);
}

void Led_Init(void)
{
	rGPFCON &= ~( (3<<8)|(3<<10)|(3<<12)|(3<<14));
	rGPFCON |= ( (1<<8)|(1<<10)|(1<<12)|(1<<14));
	rGPFUP &= 0x0F;
	rGPFDAT |= 0xFF;
}

void Main(void)
{	
	Uart0_Init_all();
	Led_Init() ;
	Uart_Printf("\n%s\n", "Led相关引脚已经初始化完毕！请按任意键开始闪烁");
	Uart_Getch();
	while(1)
	{	
		rGPFDAT &= 0x0F;
		Uart_Printf("\n%s\n", "Led亮");
		delay();
		rGPFDAT |= 0xFF;
		Uart_Printf("\n%s\n", "Led灭");
		delay();
	}
}