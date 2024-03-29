#include "2440addr.h"
#include "2440lib.h"

extern void handle_swi(void);

extern void swi97_int(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3);

__swi(98) void swi98_int(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3);
__swi(99) unsigned int swi99_int(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3);

void swi97_func(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3)
{
	Uart_Printf("\nswi97 4个参数的软中断，参数：%u %u %u %u\n", p0, p1, p2, p3);
}

void swi98_func(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3)
{
	Uart_Printf("\nswi98 4个参数的软中断，参数：%u %u %u %u\n", p0, p1, p2, p3);
}

unsigned int swi99_func(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3)
{
	Uart_Printf("\nswi99 4个参数的软中断，参数：%u %u %u %u\n", p0, p1, p2, p3);
	return p0 + p1 + p2 + p3;
}

//软中断初始化函数
void swi_init()
{
	pISR_SWI = (unsigned int)handle_swi;
}

void Main(void)
{	
	unsigned int ret;
	//初始化串口0以方便调试
	Uart0_Init_all();
	//初始化软中断
	swi_init();
    //测试软中断
	Uart_Printf("\n%s\n", "按下任意键，开始swi97 4个参数的软中断");
	Uart_Getch();
	swi97_int(11, 22, 33, 44);    
	Uart_Printf("\n%s\n", "按下任意键，开始swi98 4个参数的软中断");
	Uart_Getch();
	swi98_int(55, 66, 77, 88);
	Uart_Printf("\n%s\n", "按下任意键，开始swi99 4个参数的软中断");
	Uart_Getch();
	ret = swi99_int(91, 81, 71, 61);	
	Uart_Printf("\nswi99返回值为%u\n", ret);
	while(1)
	{
		Uart_Getch();
	}
}