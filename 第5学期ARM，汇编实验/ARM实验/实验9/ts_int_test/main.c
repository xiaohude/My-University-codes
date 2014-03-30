#include "2440addr.h"
#include "2440lib.h"

void __irq adc_isr(void);

//触摸屏初始化函数
void ts_init()
{	
	//安装中断处理函数
	pISR_ADC = (unsigned int)adc_isr;
	//清除中断相关寄存器
	rSUBSRCPND |= ((1<<10) | (1<<9));
	rSRCPND |= (1<<31);
	rINTPND |= (1<<31);
	//选择中断屏蔽
	rINTSUBMSK &= ~((1<<10) | (1<<9));
	rINTMSK &= ~(1<<31);
	
	rADCCON &= ~((1<<14) | (0xff<<6) | (7<<3) | (1<<2) | (1<<1) | (1<<0) );
	rADCCON |= ((1<<14) | (9<<6));
	rADCDLY=40000;
	
	rADCUPDN = 0;
	rADCTSC = 0xd3;			
}

volatile unsigned short x_pos = 0;
volatile unsigned short y_pos = 0;

void __irq adc_isr(void)
{	
	if( 0 != (rSUBSRCPND & (1<<9)) ) //INT_TC
	{
		if( 0 != (rADCUPDN & (1<<0)) ) //按下
		{
			rADCTSC = 0x5c;//模式变为Auto X/Y
			rADCCON |= (1<<0);//开始AD转换
			while(rADCCON & (1<<0));//等待转换开始		
		}
		else if( 0 != (rADCUPDN & (1<<1)) ) //抬起
		{
			rADCTSC = 0xd3;//模式变为等待按下中断模式
		}	
		rSUBSRCPND |= (1<<9);//清除子中断
		rADCUPDN = 0;//清除按下标志
	}
	else if( 0 != (rSUBSRCPND & (1<<10)) ) //INT_ADC_S
	{
		//读取X/Y位置
		x_pos = (unsigned short)(rADCDAT0 & 0x3ff);
		y_pos = (unsigned short)(rADCDAT1 & 0x3ff);
		Uart_Printf("\n%s%u, %u\n", "坐标为：", x_pos, y_pos);
		rADCTSC = 0x1d3;//模式变为等待抬起中断模式
		rSUBSRCPND |= (1<<10);
	}
	
	rSRCPND |= (1<<31);
	rINTPND |= (1<<31);	
}

void Main(void)
{	
	//初始化串口0以方便调试
	Uart0_Init_all();
	//调用初始化程序
	ts_init();
	Uart_Printf("\n%s\n", "开始触摸屏程序，请大家仔细阅读程序~");
	while(1)
	{Uart_Getch();}
}