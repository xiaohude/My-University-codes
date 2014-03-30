#include "2440addr.h"
#include "2440lib.h"

void __irq wdt_ac97_isr(void);

//初始化函数
void wdt_init()
{
	//清除中断相关寄存器
	rSUBSRCPND |= (1<<13);	
	rSRCPND |= (1<<9);
	rINTPND |= (1<<9);
	//选择中断屏蔽
	rINTSUBMSK &=  ~(1<<13);
	rINTMSK &= ~(1<<9);
	//安装中断处理函数
	pISR_WDT_AC97 = (unsigned int)wdt_ac97_isr;
	//设置分频参数
	rWTCON &= ~(255<<8);
	rWTCON |= (249<<8);
	rWTCON &= ~(3<<3);
	//计时常数
	rWTDAT = 50000;
	rWTCNT = 50000;
	//开始
	rWTCON &= ~(1<<0);
	rWTCON |= (1<<2);
	rWTCON |= (1<<5);
}

//wdt_ac97中断
void __irq wdt_ac97_isr(void)
{
	if( 0 != (rSUBSRCPND & (1<<13)) )
	{
		Uart_Printf("\n%s\n", "看门狗4秒钟时间到！");	
		rSUBSRCPND |= (1<<13);	
	}
	rSRCPND |= (1<<9);
	rINTPND |= (1<<9);
}


void Main(void)
{	
	//初始化串口0以方便调试
	Uart0_Init_all();
	//调用初始化程序
	wdt_init();

	while(1)
	{}
}