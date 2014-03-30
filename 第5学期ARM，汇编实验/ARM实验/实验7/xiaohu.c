#include "2440addr.h"
#include "2440lib.h"

void __irq rtc_isr(void);
///////////定义变量的时候只能在代码最前面定义变量。可以定义到函数外面
	unsigned char year, month, day, date, hour, min, sec;
	unsigned char year_bcd, month_bcd, day_bcd, date_bcd, hour_bcd, min_bcd, sec_bcd;
	unsigned char alm_year, alm_month, alm_date, alm_hour, alm_min, alm_sec;
	unsigned char alm_year_bcd, alm_month_bcd, alm_date_bcd, alm_hour_bcd, alm_min_bcd, alm_sec_bcd;	
	int i=0;//用来分辨是设置时钟时间还是设置报警时间，还是读取当前时间。

//Led 连接用到的引脚初始化 
void Led_Init(void) 
{ 
  rGPFCON &= ~( (3<<8)|(3<<10)|(3<<12)|(3<<14)); 
  rGPFCON |= ( (1<<8)|(1<<10)|(1<<12)|(1<<14)); 
  rGPFUP &= 0x0F; 
  rGPFDAT |= 0xFF; // 初始灯全灭 
}

//初始化函数
void rtc_init()
{
	Led_Init();
	//引脚功能初始化
	rGPBCON &= ~(3<<0);/////这三个语句是用来控制蜂鸣器初始化。
	rGPBCON |= (1<<0);
	rGPBUP |= (1<<0);
	//清除中断相关寄存器
	rSRCPND |= (1<<30);
	rINTPND |= (1<<30);
	//选择中断屏蔽
	rINTMSK &= ~(1<<30);
	//安装中断处理函数
	pISR_RTC = (unsigned int)rtc_isr;
	//报警不使能
	rRTCALM = 0x00;
}


//rtc中断
void __irq rtc_isr(void)
{
	Uart_Printf("\n%s\n", "报警时间到！");
	rGPBDAT |=1;///蜂鸣器响
	rGPFDAT |= 0xFF;
	rGPFDAT &=~(15<<4);//灯全亮~~~
	rSRCPND |= (1<<30);
	rINTPND |= (1<<30);
}


void readtime()
{
		rRTCCON |= 0x1;
		year_bcd = rBCDYEAR; month_bcd = rBCDMON; day_bcd = rBCDDAY; date_bcd = rBCDDATE;
		hour_bcd = rBCDHOUR; min_bcd = rBCDMIN; sec_bcd = rBCDSEC;	
		if(0 == sec_bcd)
		{
			year_bcd = rBCDYEAR; month_bcd = rBCDMON; day_bcd = rBCDDAY; date_bcd = rBCDDATE;
			hour_bcd = rBCDHOUR; min_bcd = rBCDMIN; sec_bcd = rBCDSEC;	
		}	
		rRTCCON &= 0xE;
		year = (year_bcd&0xf0)/16*10 + (year_bcd&0xf);
		month = (month_bcd&0xf0)/16*10 + (month_bcd&0xf);
		day = day_bcd&0x7;
		date = (date_bcd&0xf0)/16*10 + (date_bcd&0xf);
		hour = (hour_bcd&0xf0)/16*10 + (hour_bcd&0xf);
		min = (min_bcd&0xf0)/16*10 + (min_bcd&0xf);
		sec = (sec_bcd&0xf0)/16*10 + (sec_bcd&0xf);
		Uart_Printf("\n目前时间：%u年%u月%u日星期%u %u时%u分%u秒\n", year, month, date, day, hour, min, sec);
}

void set_time()
{
	//设置时间
	//year = 12; month = 11; day = 7; date = 25; hour = 9; min = 0; sec = 0;
	Uart_Printf("\n下面开始设置时钟时间\n");
	Uart_Printf("请输入年\n");
	year=Uart_GetIntNum();
	Uart_Printf("请输入月\n");
	month=Uart_GetIntNum();
	Uart_Printf("请输入日\n");
	date=Uart_GetIntNum();
	Uart_Printf("请输入时\n");
	hour=Uart_GetIntNum();
	Uart_Printf("请输入分\n");
	min=Uart_GetIntNum();
	Uart_Printf("请输入秒\n");
	sec=Uart_GetIntNum();
	
	year_bcd = (unsigned char)(year/10*16 + year%10);
	month_bcd = (unsigned char)(month/10*16 + month%10);
	//day_bcd = (unsigned char)day;
	date_bcd = (unsigned char)(date/10*16 + date%10);
	hour_bcd = (unsigned char)(hour/10*16 + hour%10);
	min_bcd = (unsigned char)(min/10*16 + min%10);
	sec_bcd = (unsigned char)(sec/10*16 + sec%10);	
	rRTCCON |= 0x1;
	rBCDYEAR = year_bcd;
	rBCDMON = month_bcd;
	//rBCDDAY = day_bcd;
	rBCDDATE = date_bcd;
	rBCDHOUR = hour_bcd;
	rBCDMIN = min_bcd;
	rBCDSEC = sec_bcd;
	rRTCCON &= 0xE;
}

void set_almtime()
{
	//设置报警时间
	//alm_year = 12; alm_month = 11; alm_date = 25; alm_hour = 9; alm_min = 0; alm_sec = 10;//默认时间
	
	Uart_Printf("当前时间为\n");
	readtime();
	Uart_Printf("\n下面开始设置报警时间\n");
	Uart_Printf("请输入年\n");
	alm_year=Uart_GetIntNum();
	Uart_Printf("请输入月\n");
	alm_month=Uart_GetIntNum();
	Uart_Printf("请输入日\n");
	alm_date=Uart_GetIntNum();
	Uart_Printf("请输入时\n");
	alm_hour=Uart_GetIntNum();
	Uart_Printf("请输入分\n");
	alm_min=Uart_GetIntNum();
	Uart_Printf("请输入秒\n");
	alm_sec=Uart_GetIntNum();
	
	alm_year_bcd = (unsigned char)(alm_year/10*16 + alm_year%10);
	alm_month_bcd = (unsigned char)(alm_month/10*16 + alm_month%10);
	alm_date_bcd = (unsigned char)(alm_date/10*16 + alm_date%10);
	alm_hour_bcd = (unsigned char)(alm_hour/10*16 + alm_hour%10);
	alm_min_bcd = (unsigned char)(alm_min/10*16 + alm_min%10);
	alm_sec_bcd = (unsigned char)(alm_sec/10*16 + alm_sec%10);	
	rALMYEAR = alm_year_bcd;
	rALMMON = alm_month_bcd;
	rALMDATE = alm_date_bcd;
	rALMHOUR = alm_hour_bcd;
	rALMMIN = alm_min_bcd;
	rALMSEC = alm_sec_bcd;
	//报警使能
	rRTCALM = 0x7F;	
}
void Main(void)
{	
	//初始化串口0以方便调试
	Uart0_Init_all();
	//调用初始化程序
	rtc_init();
		
	while(1)
	{
		//Uart_Getch();
		//报警不使能
		//rRTCALM = 0x00;
		
		Uart_Printf("\n 请输入（0.1.2,3）\n输入0读取当前时间。\n输入1设置时钟时间！。\n输入2设置报警时间。\n输入3关闭报警器\n");
		i=Uart_GetIntNum();
		switch(i)
		{
		case 0:readtime();break;
		case 1:set_time();break;
		case 2:set_almtime();break;
		case 3:rGPBDAT &=0;break;
		}

	}
}