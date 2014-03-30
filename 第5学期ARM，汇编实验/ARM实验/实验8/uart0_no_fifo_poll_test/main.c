#include "2440addr.h"

//��ʼ�����޻��壬��ѯ��ʽ
void uart0_no_fifo_poll_init()
{
	//��ʼ������
	rGPHCON &= ~(0xff);
	rGPHCON |= ( (2<<6) | (2<<4) | (2<<4) | (2<<0) );
	rGPHUP |= (0xf);
	//����
	rULCON0 = 0x3; //��У�飬1ֹͣλ��8����λ
	rUCON0 = 0x5;
	rUFCON0 = 0x0;
	rUMCON0 = 0x0;
	rUBRDIV0=( (int)(50000000/16.0/115200.0+0.5) -1 );
}

//�����ַ������ַ�����\0����
void uart0_send_string(char *buf)
{
	char *p = buf;
	while(*p)
    {
        while(!(rUTRSTAT0 & 0x2));
        rUTXH0 = *p++;
    }
}
//�����ַ���������������\r����
void uart0_get_string(char *buf)
{
	char c = '\0';
	char *p = buf;
	while('\r' != c)
	{
		//����1���ַ�
		while(!(rUTRSTAT0 & 0x1));
		c = rURXH0;
		*p++ = c;	
	}
	*(p-1) ='\0';
}


void Main(void)
{	
	char recvbuf[128];
	//���ó�ʼ������
	uart0_no_fifo_poll_init();
	while(1)
	{
		uart0_send_string("�����ַ��������س�");
		uart0_get_string(recvbuf);
		uart0_send_string("������ַ�Ϊ�� ");
		uart0_send_string(recvbuf);
	}
}