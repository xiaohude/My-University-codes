#include "2440addr.h"
#include "2440lib.h"



//adc初始化函数
void adc_init()
{
	rADCCON &= ~((1<<14) | (0xff<<6) | (7<<3) | (1<<2) | (1<<1) | (1<<0) );
	rADCCON |= ((1<<14) | (49<<6));
	rADCTSC |= ~(1<<2);
}


void Main(void)
{	
	unsigned short ad_value = 0;
	//初始化串口0以方便调试
	Uart0_Init_all();
	//调用初始化程序
	adc_init();
	Uart_Printf("\n%s\n", "开始adc程序，请大家仔细阅读程序~");
	while(1)
	{
		Uart_Printf("\n%s\n", "按下任意键，读取AIN1~");
		Uart_Getch();
		//选择adc通道为AIN1并启动
		rADCCON &= ~(7<<3);
		rADCCON |= ((1<<3) | (1<<1));
		ad_value = (unsigned short)(rADCDAT0 & 0x3ff);
		//等待ADC完成
		while(!(rADCCON & (1<<15)));
		//读取AD转换结果
		ad_value = (unsigned short)(rADCDAT0 & 0x3ff);
		Uart_Printf("\n%s%u\n", "AIN1值为：", ad_value);
	}
}