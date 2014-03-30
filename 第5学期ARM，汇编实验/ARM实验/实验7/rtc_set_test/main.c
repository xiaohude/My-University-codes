#include "2440addr.h"
#include "2440lib.h"



void Main(void)
{	
	unsigned char year, month, day, date, hour, min, sec;
	unsigned char year_bcd, month_bcd, day_bcd, date_bcd, hour_bcd, min_bcd, sec_bcd;
	
		
	//��ʼ������0�Է������
	Uart0_Init_all();
	
	
	year = 12; month = 11; day = 3; date = 14; hour = 13; min = 25; sec = 38;
	//��ΪBCD��
	year_bcd = (unsigned char)(year/10*16 + year%10);
	month_bcd = (unsigned char)(month/10*16 + month%10);
	day_bcd = (unsigned char)day;
	date_bcd = (unsigned char)(date/10*16 + date%10);
	hour_bcd = (unsigned char)(hour/10*16 + hour%10);
	min_bcd = (unsigned char)(min/10*16 + min%10);
	sec_bcd = (unsigned char)(sec/10*16 + sec%10);
	
	Uart_Printf("\n���������������ʱ��%u��%u��%u������%u %uʱ%u��%u��\n", year, month, date, day, hour, min, sec);
	Uart_Getch();
	
	//���üĴ���
	rRTCCON |= 0x1;
	rBCDYEAR = year_bcd;
	rBCDMON = month_bcd;
	rBCDDAY = day_bcd;
	rBCDDATE = date_bcd;
	rBCDHOUR = hour_bcd;
	rBCDMIN = min_bcd;
	rBCDSEC = sec_bcd;
	rRTCCON &= 0xE;
	
	while(1)
	{
		Uart_Printf("\n%s\n", "�������������ȡʱ��");
		Uart_Getch();	
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
		Uart_Printf("\nĿǰʱ�䣺%u��%u��%u������%u %uʱ%u��%u��\n", year, month, date, day, hour, min, sec);
	}
}