#include "2440addr.h"
#include "2440lib.h"



//adc��ʼ������
void adc_init()
{
	rADCCON &= ~((1<<14) | (0xff<<6) | (7<<3) | (1<<2) | (1<<1) | (1<<0) );
	rADCCON |= ((1<<14) | (49<<6));
	rADCTSC |= ~(1<<2);
}


void Main(void)
{	
	unsigned short ad_value = 0;
	//��ʼ������0�Է������
	Uart0_Init_all();
	//���ó�ʼ������
	adc_init();
	Uart_Printf("\n%s\n", "��ʼadc����������ϸ�Ķ�����~");
	while(1)
	{
		Uart_Printf("\n%s\n", "�������������ȡAIN1~");
		Uart_Getch();
		//ѡ��adcͨ��ΪAIN1������
		rADCCON &= ~(7<<3);
		rADCCON |= ((1<<3) | (1<<1));
		ad_value = (unsigned short)(rADCDAT0 & 0x3ff);
		//�ȴ�ADC���
		while(!(rADCCON & (1<<15)));
		//��ȡADת�����
		ad_value = (unsigned short)(rADCDAT0 & 0x3ff);
		Uart_Printf("\n%s%u\n", "AIN1ֵΪ��", ad_value);
	}
}