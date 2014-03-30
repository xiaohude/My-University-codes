#include "2440addr.h"
#include "2440lib.h"

void __irq adc_isr(void);

//��������ʼ������
void ts_init()
{	
	//��װ�жϴ�����
	pISR_ADC = (unsigned int)adc_isr;
	//����ж���ؼĴ���
	rSUBSRCPND |= ((1<<10) | (1<<9));
	rSRCPND |= (1<<31);
	rINTPND |= (1<<31);
	//ѡ���ж�����
	rINTSUBMSK &= ~((1<<10) | (1<<9));
	rINTMSK &= ~(1<<31);
	
	rADCCON &= ~((1<<14) | (0xff<<6) | (7<<3) | (1<<2) | (1<<1) | (1<<0) );
	rADCCON |= ((1<<14) | (9<<6));
	rADCDLY=40000;
	
	rADCUPDN = 0;
	rADCTSC = 0xd3;			
}

volatile unsigned short x_pos = 0;
volatile unsigned short y_pos = 0;

void __irq adc_isr(void)
{	
	if( 0 != (rSUBSRCPND & (1<<9)) ) //INT_TC
	{
		if( 0 != (rADCUPDN & (1<<0)) ) //����
		{
			rADCTSC = 0x5c;//ģʽ��ΪAuto X/Y
			rADCCON |= (1<<0);//��ʼADת��
			while(rADCCON & (1<<0));//�ȴ�ת����ʼ		
		}
		else if( 0 != (rADCUPDN & (1<<1)) ) //̧��
		{
			rADCTSC = 0xd3;//ģʽ��Ϊ�ȴ������ж�ģʽ
		}	
		rSUBSRCPND |= (1<<9);//������ж�
		rADCUPDN = 0;//������±�־
	}
	else if( 0 != (rSUBSRCPND & (1<<10)) ) //INT_ADC_S
	{
		//��ȡX/Yλ��
		x_pos = (unsigned short)(rADCDAT0 & 0x3ff);
		y_pos = (unsigned short)(rADCDAT1 & 0x3ff);
		Uart_Printf("\n%s%u, %u\n", "����Ϊ��", x_pos, y_pos);
		rADCTSC = 0x1d3;//ģʽ��Ϊ�ȴ�̧���ж�ģʽ
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
	ts_init();
	Uart_Printf("\n%s\n", "��ʼ����������������ϸ�Ķ�����~");
	while(1)
	{Uart_Getch();}
}