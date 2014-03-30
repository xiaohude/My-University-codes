#include "2440addr.h"
#include "2440lib.h"

void __irq timer0_isr(void);

//初始化函数
void timer0_init()
{
	//引脚功能初始化
	rGPBCON &= ~(3<<0);
	rGPBCON |= (2<<0);
	rGPGUP |= (1<<0);
	//清除中断相关寄存器
	rSRCPND |= (1<<10);
	rINTPND |= (1<<10);
	//选择中断屏蔽
	rINTMSK &= ~(1<<10);
	//安装中断处理函数
	pISR_TIMER0 = (unsigned int)timer0_isr;
	//设置分频参数
	rTCFG0 &= ~(255<<0);
	rTCFG0 |= (49<<0);
	rTCFG1 &= ~( (15<<20) | (15<<0) );
	rTCFG1 |= (1<<0);
	//设置计数初值
	rTCNTB0 = 25000;
	rTCMPB0 = 12500;
	//加载计数
	rTCON |= (1<<1);
	rTCON &= ~(1<<1);
	//开始定时器Timer0
	rTCON |= ( (1<<3) | (1<<2) | (1<<0) );
}

unsigned short highval = 12500;
//timer0中断
void __irq timer0_isr(void)
{
	rTCMPB0 = highval;
	rSRCPND |= (1<<10);
	rINTPND |= (1<<10);
}


void Main(void)
{	
	//初始化串口0以方便调试
	Uart0_Init_all();
	//调用初始化程序
	timer0_init();
	Uart_Printf("\n%s\n", "按下任意键，高电平占50/100");
	Uart_Getch();
	highval = 12500;
	Uart_Printf("\n%s\n", "按下任意键，高电平占90/100");
	Uart_Getch();
	highval = 22500;	
	Uart_Printf("\n%s\n", "按下任意键，高电平占20/100");
	Uart_Getch();
	highval = 5000;	
	while(1)
	{}
}