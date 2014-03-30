#include "2440addr.h"



void __irq uart0_isr(void);

//��ʼ�����޻��壬�жϷ�ʽ
void uart0_no_fifo_int_init()
{
	//��ʼ������
	rGPHCON &= ~(0xff);
	rGPHCON |= ( (2<<6) | (2<<4) | (2<<4) | (2<<0) );
	rGPHUP |= (0xf);
	//����
	rULCON0 = 0x3; //��У�飬1ֹͣλ��8����λ
	rUCON0 = 0x305;
	rUFCON0 = 0x0;
	rUMCON0 = 0x0;
	rUBRDIV0=( (int)(50000000/16.0/115200.0+0.5) -1 );
	//�������ڲ��жϣ��������ж�
	rSUBSRCPND |= (0x07);
	rSRCPND |= (1<<28);
	rINTPND |= (1<<28);
	
	pISR_UART0 = (unsigned int)uart0_isr;
	rINTSUBMSK |= (0x07);
	rINTMSK &= ~(1<<28);
}

volatile char *psend;
volatile unsigned char senddone;

volatile char *pget;
char c;
volatile unsigned char getdone;


void __irq uart0_isr(void)
{	
	//�����ж�
 	if( (0!=(rSUBSRCPND & (1<<0))) && (rUTRSTAT0 & 0x1) )
 	{
		c = rURXH0;
		if('\r' != c)
		{
			*pget++ = c;
		}
		else
		{
			*pget ='\0';
			//�ؽ����ж�
    		rINTSUBMSK |= (1<<0);
			getdone = 1;
		}
		rSUBSRCPND |= (1<<0);
 	}	
	//�����ж�
	else if( (0!=(rSUBSRCPND & (1<<1))) && (rUTRSTAT0 & 0x2) )
	{
		//����
		if(*psend)
	    {
	        rUTXH0 = *psend++;
	    }
        else
        {
        	//�ط����ж�
    		rINTSUBMSK |= (1<<1);
        	senddone = 1;
        }
        rSUBSRCPND |= (1<<1);
	}
	else
	{
		rSUBSRCPND |= (0x07);
	}
	rSRCPND |= (1<<28);
	rINTPND |= (1<<28);	
}

//�����ַ������ַ�����\0����
void uart0_send_string(char *buf)
{    
    psend = buf;
    senddone = 0;
	rSUBSRCPND |= (1<<1);    
    //�������ж�
    rINTSUBMSK &= ~(1<<1);
    while(!senddone);   
}
//�����ַ���������������\r����
void uart0_get_string(char *buf)
{
	c = '\0';
	pget = buf;
	getdone = 0;
	rSUBSRCPND |= (1<<0);	
	//�������ж�
    rINTSUBMSK &= ~(1<<0);
	while(!getdone);
}

void Main(void)
{	
	char recvbuf[128];
	//���ó�ʼ������
	uart0_no_fifo_int_init();
	while(1)
	{
		uart0_send_string("�����ַ��������س�");
		uart0_get_string(recvbuf);
		uart0_send_string("������ַ�Ϊ�� ");
		uart0_send_string(recvbuf);
	}
}