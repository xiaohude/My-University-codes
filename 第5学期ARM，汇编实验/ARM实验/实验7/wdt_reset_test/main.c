#include "2440addr.h"
#include "2440lib.h"


//��ʼ������
void wdt_init()
{
	//���÷�Ƶ����
	rWTCON &= ~(255<<8);
	rWTCON |= (249<<8);
	rWTCON &= ~(3<<3);
	//��ʱ����
	rWTCNT = 50000;
	//��ʼ
	rWTCON |= (1<<0);
	rWTCON |= (0<<2);
	rWTCON |= (1<<5);
}

void Main(void)
{	
	//��ʼ������0�Է������
	Uart0_Init_all();
	//���ó�ʼ������
	wdt_init();
	while(1)
	{
		Uart_Printf("\n%s\n", "4�����ڰ��������������ϵͳ������");
		Uart_Getch();
		rWTCNT = 50000;
	}
}