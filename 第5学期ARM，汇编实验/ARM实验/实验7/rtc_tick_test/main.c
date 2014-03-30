#include "2440addr.h"
#include "2440lib.h"

void __irq tick_isr(void);

//��ʼ������
void tick_init()
{
	//����ж���ؼĴ���
	rSRCPND |= (1<<8);
	rINTPND |= (1<<8);
	//ѡ���ж�����
	rINTMSK &= ~(1<<8);
	//��װ�жϴ�����
	pISR_TICK = (unsigned int)tick_isr;
	//����ʱ��Ƭ���������ж�ʹ��
	rTICNT = 0x83;
}

unsigned int counter = 0;
//tick�ж�
void __irq tick_isr(void)
{
	counter += 1;
	if(96 == counter)
	{
		Uart_Printf("\n%s\n", "3����ʱ�䵽��");
		counter = 0;
	}
	rSRCPND |= (1<<8);
	rINTPND |= (1<<8);
}


void Main(void)
{	
	//��ʼ������0�Է������
	Uart0_Init_all();
	//���ó�ʼ������
	tick_init();
	while(1)
	{}
}