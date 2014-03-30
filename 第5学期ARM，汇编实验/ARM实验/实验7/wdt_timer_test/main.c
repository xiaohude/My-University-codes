#include "2440addr.h"
#include "2440lib.h"

void __irq wdt_ac97_isr(void);

//��ʼ������
void wdt_init()
{
	//����ж���ؼĴ���
	rSUBSRCPND |= (1<<13);	
	rSRCPND |= (1<<9);
	rINTPND |= (1<<9);
	//ѡ���ж�����
	rINTSUBMSK &=  ~(1<<13);
	rINTMSK &= ~(1<<9);
	//��װ�жϴ�����
	pISR_WDT_AC97 = (unsigned int)wdt_ac97_isr;
	//���÷�Ƶ����
	rWTCON &= ~(255<<8);
	rWTCON |= (249<<8);
	rWTCON &= ~(3<<3);
	//��ʱ����
	rWTDAT = 50000;
	rWTCNT = 50000;
	//��ʼ
	rWTCON &= ~(1<<0);
	rWTCON |= (1<<2);
	rWTCON |= (1<<5);
}

//wdt_ac97�ж�
void __irq wdt_ac97_isr(void)
{
	if( 0 != (rSUBSRCPND & (1<<13)) )
	{
		Uart_Printf("\n%s\n", "���Ź�4����ʱ�䵽��");	
		rSUBSRCPND |= (1<<13);	
	}
	rSRCPND |= (1<<9);
	rINTPND |= (1<<9);
}


void Main(void)
{	
	//��ʼ������0�Է������
	Uart0_Init_all();
	//���ó�ʼ������
	wdt_init();

	while(1)
	{}
}