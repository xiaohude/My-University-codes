#include "2440addr.h"
#include "2440lib.h"

void __irq timer4_isr(void);

//LED��������ų�ʼ��
void led_init()
{
	rGPFCON &= ~( (3<<8)|(3<<10)|(3<<12)|(3<<14));
	rGPFCON |= ( (1<<8)|(1<<10)|(1<<12)|(1<<14));
	rGPFUP &= 0x0F;
	rGPFDAT |= 0xF0;
}
//��ʱ����ʼ������
void timer4_init()
{
	//����ж���ؼĴ���
	rSRCPND |= (1<<14);
	rINTPND |= (1<<14);
	//ѡ���ж�����
	rINTMSK &= ~(1<<14);
	//��װ�жϴ�����
	pISR_TIMER4 = (unsigned int)timer4_isr;
	//���÷�Ƶ����
	rTCFG0 &= ~(255<<8);
	rTCFG0 |= (249<<8); //����Ԥ��Ƶ������Ϊ249
	rTCFG1 &= ~( (15<<20) | (15<<16) );
	rTCFG1 |= (1<<16);//���ö�����ƵΪ4�������Ƶ��Ϊ50000Hz
	//���ü�����ֵ
	rTCNTB4 = 50000;
	//���ؼ���
	rTCON |= (1<<21);
	rTCON &= ~(1<<21);
	//��ʼ��ʱ��Timer4
	rTCON |= ( (1<<22) | (1<<20) );
}

unsigned char led_no = 0;
//timer4�ж�
void __irq timer4_isr(void)
{
	led_no += 1;
	if(led_no > 4)
	{
		led_no = 1;
	}
	rGPFDAT |= 0xF0;//ȫ��
	switch(led_no)
	{
		case 1:
		{
			rGPFDAT &= 0xEF;
		}
		break;
		case 2:
		{
			rGPFDAT &= 0xDF;
		}
		break;
		case 3:
		{
			rGPFDAT &= 0xBF;
		}
		break;
		case 4:
		{
			rGPFDAT &= 0x7F;
		}
		break;						
	}
	rSRCPND |= (1<<14);
	rINTPND |= (1<<14);
}

void Main(void)
{	
	//��ʼ������0�Է������
	Uart0_Init_all();
	//���ó�ʼ������
	led_init();
	timer4_init();
	Uart_Printf("\n%s\n", "��ʼ��ʱ���������ƣ�������ϸ�Ķ�����~");
	while(1)
	{Uart_Getch();}
}