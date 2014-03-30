#include "2440addr.h"

//初始化，无缓冲，查询方式
void uart0_no_fifo_poll_init()
{
	//初始化引脚
	rGPHCON &= ~(0xff);
	rGPHCON |= ( (2<<6) | (2<<4) | (2<<4) | (2<<0) );
	rGPHUP |= (0xf);
	//参数
	rULCON0 = 0x3; //无校验，1停止位，8数据位
	rUCON0 = 0x5;
	rUFCON0 = 0x0;
	rUMCON0 = 0x0;
	rUBRDIV0=( (int)(50000000/16.0/115200.0+0.5) -1 );
}

//发送字符串，字符串以\0结束
void uart0_send_string(char *buf)
{
	char *p = buf;
	while(*p)
    {
        while(!(rUTRSTAT0 & 0x2));
        rUTXH0 = *p++;
    }
}
//接收字符串，接收内容以\r结束
void uart0_get_string(char *buf)
{
	char c = '\0';
	char *p = buf;
	while('\r' != c)
	{
		//接收1个字符
		while(!(rUTRSTAT0 & 0x1));
		c = rURXH0;
		*p++ = c;	
	}
	*(p-1) ='\0';
}


void Main(void)
{	
	char recvbuf[128];
	//调用初始化程序
	uart0_no_fifo_poll_init();
	while(1)
	{
		uart0_send_string("输入字符串并按回车");
		uart0_get_string(recvbuf);
		uart0_send_string("输入的字符为： ");
		uart0_send_string(recvbuf);
	}
}