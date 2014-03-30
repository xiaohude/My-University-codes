#include "2440addr.h"
#include "2440lib.h"

void __irq tick_isr(void);

//初始化函数
void tick_init()
{
	//清除中断相关寄存器
	rSRCPND |= (1<<8);
	rINTPND |= (1<<8);
	//选择中断屏蔽
	rINTMSK &= ~(1<<8);
	//安装中断处理函数
	pISR_TICK = (unsigned int)tick_isr;
	//设置时间片计数器及中断使能
	rTICNT = 0x83;
}

unsigned int counter = 0;
//tick中断
void __irq tick_isr(void)
{
	counter += 1;
	if(96 == counter)
	{
		Uart_Printf("\n%s\n", "3秒钟时间到！");
		counter = 0;
	}
	rSRCPND |= (1<<8);
	rINTPND |= (1<<8);
}


void Main(void)
{	
	//初始化串口0以方便调试
	Uart0_Init_all();
	//调用初始化程序
	tick_init();
	while(1)
	{}
}