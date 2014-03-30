#include "2440addr.h"
#include "2440lib.h"


void __irq adc_isr(void);

//adc��ʼ������
void adc_init()
{
	//ADC������ʼ��
	rADCCON &= ~((1<<14) | (0xff<<6) | (7<<3) | (1<<2) | (1<<1) | (1<<0) );
	rADCCON |= ((1<<14) | (49<<6));
	rADCTSC |= ~(1<<2);
	//����ж���ؼĴ���
	rSUBSRCPND |= (1<<10);
	rSRCPND |= (1<<31);
	rINTPND |= (1<<31);
	//ѡ���ж�����
	rINTSUBMSK &= ~(1<<10);
	rINTMSK &= ~(1<<31);
	//��װ�жϴ�����
	pISR_ADC = (unsigned int)adc_isr;
}

volatile unsigned short ad_value = 0;
volatile unsigned char adc_done = 0;
void __irq adc_isr(void)
{
	if( 0 != (rSUBSRCPND & (1<<10)) )
	{
		ad_value = (unsigned short)(rADCDAT0 & 0x3ff);
		adc_done = 1;
		rSUBSRCPND |= (1<<10);
	}
	rSRCPND |= (1<<31);
	rINTPND |= (1<<31);
}


void Main(void)
{	
	
	//��ʼ������0�Է������
	Uart0_Init_all();
	//���ó�ʼ������
	adc_init();
	Uart_Printf("\n%s\n", "��ʼadc�жϳ���������ϸ�Ķ�����~");
	while(1)
	{
		Uart_Printf("\n%s\n", "�������������ȡAIN1~");
		Uart_Getch();
		//ѡ��adcͨ��ΪAIN1������
		adc_done = 0;
		rADCCON &= ~(7<<3);
		rADCCON |= ((1<<3) | (1<<0));
		//�ȴ�ADC���
		while(rADCCON & (1<<0));
		while(!adc_done);
		//ADת�����
		Uart_Printf("\n%s%u\n", "AIN1ֵΪ��", ad_value);
	}
}