#include "2440addr.h"
#include "2440lib.h"

void __irq timer4_isr(void);

//LED灯相关引脚初始化
void led_init()
{
	rGPFCON &= ~( (3<<8)|(3<<10)|(3<<12)|(3<<14));
	rGPFCON |= ( (1<<8)|(1<<10)|(1<<12)|(1<<14));
	rGPFUP &= 0x0F;
	rGPFDAT |= 0xF0;
}
//定时器初始化函数
void timer4_init()
{
	//清除中断相关寄存器
	rSRCPND |= (1<<14);
	rINTPND |= (1<<14);
	//选择中断屏蔽
	rINTMSK &= ~(1<<14);
	//安装中断处理函数
	pISR_TIMER4 = (unsigned int)timer4_isr;
	//设置分频参数
	rTCFG0 &= ~(255<<8);
	rTCFG0 |= (249<<8); //设置预分频器参数为249
	rTCFG1 &= ~( (15<<20) | (15<<16) );
	rTCFG1 |= (1<<16);//设置二级分频为4，则计数频率为50000Hz
	//设置计数初值
	rTCNTB4 = 50000;
	//加载计数
	rTCON |= (1<<21);
	rTCON &= ~(1<<21);
	//开始定时器Timer4
	rTCON |= ( (1<<22) | (1<<20) );
}

unsigned char led_no = 0;
//timer4中断
void __irq timer4_isr(void)
{
	led_no += 1;
	if(led_no > 4)
	{
		led_no = 1;
	}
	rGPFDAT |= 0xF0;//全灭
	switch(led_no)
	{
		case 1:
		{
			rGPFDAT &= 0xEF;
		}
		break;
		case 2:
		{
			rGPFDAT &= 0xDF;
		}
		break;
		case 3:
		{
			rGPFDAT &= 0xBF;
		}
		break;
		case 4:
		{
			rGPFDAT &= 0x7F;
		}
		break;						
	}
	rSRCPND |= (1<<14);
	rINTPND |= (1<<14);
}

void Main(void)
{	
	//初始化串口0以方便调试
	Uart0_Init_all();
	//调用初始化程序
	led_init();
	timer4_init();
	Uart_Printf("\n%s\n", "开始定时器版的跑马灯，请大家仔细阅读程序~");
	while(1)
	{Uart_Getch();}
}