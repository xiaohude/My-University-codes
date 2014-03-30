#include "2440addr.h"
#include "2440lib.h"

void __irq eint0_isr(void);
void __irq eint2_isr(void);
void __irq eint8_23_isr(void);


void isr_init()
{
	//引脚功能初始化
	rGPFCON &= ~((3<<4) | (3<<0));
	rGPFCON |= ((2<<4) | (2<<0));
	rGPFUP |= ((1<<2) | (1<<0));
	rGPGCON &= ~((3<<22) | (3<<6));
	rGPGCON |= ((2<<22) | (2<<6));
	rGPGUP |= ((1<<11) | (1<<3));
	//选择触发信号电平（低电平触发中断）
	rEXTINT0 &= ~((7<<8) | (7<<0));
	rEXTINT1 &= ~(7<<12);
	rEXTINT2 &= ~(7<<12);
	//选择信号滤波
	rEXTINT1 |= (1<<15);
	rEXTINT2 |= (1<<15);
	rEINTFLT2 &= ~((1<<31) | (0x7f<<24));
	rEINTFLT2 |= ((0<<31) | (0x4<<24));
	//清除中断相关寄存器
	rEINTPEND |= ((1<<19) | (1<<11));
	rSRCPND |= ((1<<5) | (1<<2) | (1<<0));
	rINTPND |= ((1<<5) | (1<<2) | (1<<0));
	//选择中断屏蔽
	rEINTMASK &= ~((1<<19) | (1<<11));
	rINTMSK &= ~((1<<5) | (1<<2) | (1<<0));
	//安装中断处理函数
	pISR_EINT0 = (unsigned int)eint0_isr;
	pISR_EINT2 = (unsigned int)eint2_isr;
	pISR_EINT8_23 = (unsigned int)eint8_23_isr;
}
//eint0
void __irq eint0_isr(void)
{
	Uart_Printf("\n%s\n", "SW1按下");
	rSRCPND |= (1<<0);
	rINTPND |= (1<<0);
}
//eint2
void __irq eint2_isr(void)
{
	Uart_Printf("\n%s\n", "SW2按下");
	rSRCPND |= (1<<2);
	rINTPND |= (1<<2);	
}
//eint8_23
void __irq eint8_23_isr(void)
{
	if( 0 != (rEINTPEND & (1<<19)) )
	{
		Uart_Printf("\n%s\n", "SW4按下");
		rEINTPEND |= (1<<19);
	}
	else if( 0 != (rEINTPEND & (1<<11)) )
	{
		Uart_Printf("\n%s\n", "SW3按下");
		rEINTPEND |= (1<<11);		
	}
	rSRCPND |= (1<<5);
	rINTPND |= (1<<5);
}

void Main(void)
{	
	//初始化串口0以方便调试
	Uart0_Init_all();
	//调用中断初始化程序
	isr_init();
	
	while(1)
	{
		Uart_Getch();
	}
}