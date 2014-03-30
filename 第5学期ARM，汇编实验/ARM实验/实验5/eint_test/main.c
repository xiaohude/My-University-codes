#include "2440addr.h"
#include "2440lib.h"

void __irq eint0_isr(void);
void __irq eint2_isr(void);
void __irq eint8_23_isr(void);


void isr_init()
{
	//���Ź��ܳ�ʼ��
	rGPFCON &= ~((3<<4) | (3<<0));
	rGPFCON |= ((2<<4) | (2<<0));
	rGPFUP |= ((1<<2) | (1<<0));
	rGPGCON &= ~((3<<22) | (3<<6));
	rGPGCON |= ((2<<22) | (2<<6));
	rGPGUP |= ((1<<11) | (1<<3));
	//ѡ�񴥷��źŵ�ƽ���͵�ƽ�����жϣ�
	rEXTINT0 &= ~((7<<8) | (7<<0));
	rEXTINT1 &= ~(7<<12);
	rEXTINT2 &= ~(7<<12);
	//ѡ���ź��˲�
	rEXTINT1 |= (1<<15);
	rEXTINT2 |= (1<<15);
	rEINTFLT2 &= ~((1<<31) | (0x7f<<24));
	rEINTFLT2 |= ((0<<31) | (0x4<<24));
	//����ж���ؼĴ���
	rEINTPEND |= ((1<<19) | (1<<11));
	rSRCPND |= ((1<<5) | (1<<2) | (1<<0));
	rINTPND |= ((1<<5) | (1<<2) | (1<<0));
	//ѡ���ж�����
	rEINTMASK &= ~((1<<19) | (1<<11));
	rINTMSK &= ~((1<<5) | (1<<2) | (1<<0));
	//��װ�жϴ�����
	pISR_EINT0 = (unsigned int)eint0_isr;
	pISR_EINT2 = (unsigned int)eint2_isr;
	pISR_EINT8_23 = (unsigned int)eint8_23_isr;
}
//eint0
void __irq eint0_isr(void)
{
	Uart_Printf("\n%s\n", "SW1����");
	rSRCPND |= (1<<0);
	rINTPND |= (1<<0);
}
//eint2
void __irq eint2_isr(void)
{
	Uart_Printf("\n%s\n", "SW2����");
	rSRCPND |= (1<<2);
	rINTPND |= (1<<2);	
}
//eint8_23
void __irq eint8_23_isr(void)
{
	if( 0 != (rEINTPEND & (1<<19)) )
	{
		Uart_Printf("\n%s\n", "SW4����");
		rEINTPEND |= (1<<19);
	}
	else if( 0 != (rEINTPEND & (1<<11)) )
	{
		Uart_Printf("\n%s\n", "SW3����");
		rEINTPEND |= (1<<11);		
	}
	rSRCPND |= (1<<5);
	rINTPND |= (1<<5);
}

void Main(void)
{	
	//��ʼ������0�Է������
	Uart0_Init_all();
	//�����жϳ�ʼ������
	isr_init();
	
	while(1)
	{
		Uart_Getch();
	}
}