#include "2440addr.h"
#include "2440lib.h"

void __irq timer0_isr(void);

//��ʼ������
void timer0_init()
{
	//���Ź��ܳ�ʼ��
	rGPBCON &= ~(3<<0);
	rGPBCON |= (2<<0);
	rGPGUP |= (1<<0);
	//����ж���ؼĴ���
	rSRCPND |= (1<<10);
	rINTPND |= (1<<10);
	//ѡ���ж�����
	rINTMSK &= ~(1<<10);
	//��װ�жϴ�����
	pISR_TIMER0 = (unsigned int)timer0_isr;
	//���÷�Ƶ����
	rTCFG0 &= ~(255<<0);
	rTCFG0 |= (49<<0);
	rTCFG1 &= ~( (15<<20) | (15<<0) );
	rTCFG1 |= (1<<0);
	//���ü�����ֵ
	rTCNTB0 = 25000;
	rTCMPB0 = 12500;
	//���ؼ���
	rTCON |= (1<<1);
	rTCON &= ~(1<<1);
	//��ʼ��ʱ��Timer0
	rTCON |= ( (1<<3) | (1<<2) | (1<<0) );
}

unsigned short highval = 12500;
//timer0�ж�
void __irq timer0_isr(void)
{
	rTCMPB0 = highval;
	rSRCPND |= (1<<10);
	rINTPND |= (1<<10);
}


void Main(void)
{	
	//��ʼ������0�Է������
	Uart0_Init_all();
	//���ó�ʼ������
	timer0_init();
	Uart_Printf("\n%s\n", "������������ߵ�ƽռ50/100");
	Uart_Getch();
	highval = 12500;
	Uart_Printf("\n%s\n", "������������ߵ�ƽռ90/100");
	Uart_Getch();
	highval = 22500;	
	Uart_Printf("\n%s\n", "������������ߵ�ƽռ20/100");
	Uart_Getch();
	highval = 5000;	
	while(1)
	{}
}