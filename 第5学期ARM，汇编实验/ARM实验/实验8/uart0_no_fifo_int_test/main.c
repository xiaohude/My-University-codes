#include "2440addr.h"



void __irq uart0_isr(void);

//初始化，无缓冲，中断方式
void uart0_no_fifo_int_init()
{
	//初始化引脚
	rGPHCON &= ~(0xff);
	rGPHCON |= ( (2<<6) | (2<<4) | (2<<4) | (2<<0) );
	rGPHUP |= (0xf);
	//参数
	rULCON0 = 0x3; //无校验，1停止位，8数据位
	rUCON0 = 0x305;
	rUFCON0 = 0x0;
	rUMCON0 = 0x0;
	rUBRDIV0=( (int)(50000000/16.0/115200.0+0.5) -1 );
	//允许总内部中断，屏蔽子中断
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
	//接收中断
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
			//关接收中断
    		rINTSUBMSK |= (1<<0);
			getdone = 1;
		}
		rSUBSRCPND |= (1<<0);
 	}	
	//发送中断
	else if( (0!=(rSUBSRCPND & (1<<1))) && (rUTRSTAT0 & 0x2) )
	{
		//发送
		if(*psend)
	    {
	        rUTXH0 = *psend++;
	    }
        else
        {
        	//关发送中断
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

//发送字符串，字符串以\0结束
void uart0_send_string(char *buf)
{    
    psend = buf;
    senddone = 0;
	rSUBSRCPND |= (1<<1);    
    //开发送中断
    rINTSUBMSK &= ~(1<<1);
    while(!senddone);   
}
//接收字符串，接收内容以\r结束
void uart0_get_string(char *buf)
{
	c = '\0';
	pget = buf;
	getdone = 0;
	rSUBSRCPND |= (1<<0);	
	//开接收中断
    rINTSUBMSK &= ~(1<<0);
	while(!getdone);
}

void Main(void)
{	
	char recvbuf[128];
	//调用初始化程序
	uart0_no_fifo_int_init();
	while(1)
	{
		uart0_send_string("输入字符串并按回车");
		uart0_get_string(recvbuf);
		uart0_send_string("输入的字符为： ");
		uart0_send_string(recvbuf);
	}
}