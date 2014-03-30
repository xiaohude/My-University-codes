#include "2440addr.h"
#include "2440lib.h"

void __irq rtc_isr(void);

//初始化函数
void rtc_init()
{
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
	rSRCPND |= (1<<30);
	rINTPND |= (1<<30);
}


void Main(void)
{	
	unsigned char year, month, day, date, hour, min, sec;
	unsigned char year_bcd, month_bcd, day_bcd, date_bcd, hour_bcd, min_bcd, sec_bcd;
	unsigned char alm_year, alm_month, alm_date, alm_hour, alm_min, alm_sec;
	unsigned char alm_year_bcd, alm_month_bcd, alm_date_bcd, alm_hour_bcd, alm_min_bcd, alm_sec_bcd;	
	
	//初始化串口0以方便调试
	Uart0_Init_all();
	//调用初始化程序
	rtc_init();
	//设置时间
	year = 12; month = 11; day = 3; date = 14; hour = 13; min = 25; sec = 38;
	year_bcd = (unsigned char)(year/10*16 + year%10);
	month_bcd = (unsigned char)(month/10*16 + month%10);
	day_bcd = (unsigned char)day;
	date_bcd = (unsigned char)(date/10*16 + date%10);
	hour_bcd = (unsigned char)(hour/10*16 + hour%10);
	min_bcd = (unsigned char)(min/10*16 + min%10);
	sec_bcd = (unsigned char)(sec/10*16 + sec%10);	
	rRTCCON |= 0x1;
	rBCDYEAR = year_bcd;
	rBCDMON = month_bcd;
	rBCDDAY = day_bcd;
	rBCDDATE = date_bcd;
	rBCDHOUR = hour_bcd;
	rBCDMIN = min_bcd;
	rBCDSEC = sec_bcd;
	rRTCCON &= 0xE;
	//设置报警时间
	alm_year = 12; alm_month = 11; alm_date = 14; alm_hour = 13; alm_min = 25; alm_sec = 49;
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
	
	while(1)
	{
		Uart_Getch();
		//报警不使能
		rRTCALM = 0x00;
	}
}