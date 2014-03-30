#include "2440addr.h"
#include "2440lib.h"

void delay_s(void)
{
	int i;
	for(i=0; i<100; i++);
}

void Key_Init(void)
{
	rGPGCON &= ~( (3<<6)|(3<<22));
	rGPGUP &= 0xF7F7;
	
	rGPFCON &= ~( (3)|(3<<4));
	rGPFUP &= 0xFA;	
}

void Main(void)
{	
	unsigned int getkey[2] , getbuf;
	Uart0_Init_all();
	Key_Init();
	Uart_Printf("\n%s\n", "Key��������Ѿ���ʼ����ϣ���ʼ����~~");
	while(1)
	{
		getkey[1] = getkey[0] = 0;
		
		
		getbuf = ~rGPGDAT;
		getkey[0] |= (getbuf&(0x1<<3))>> (3-2);
		getkey[0] |= (getbuf&(0x1<<11))>> (11-3);
		getbuf = ~rGPFDAT; 
		getkey[0] |= getbuf&0x1;
		getkey[0] |= (getbuf&(0x1<<2))>> (2-1);
		
		delay_s();
		
		getbuf = ~rGPGDAT;
		getkey[1] |= (getbuf&(0x1<<3))>> (3-2);
		getkey[1] |= (getbuf&(0x1<<11))>> (11-3);
		getbuf = ~rGPFDAT; 
		getkey[1] |= getbuf&0x1;
		getkey[1] |= (getbuf&(0x1<<2))>> (2-1);		
		
		
		if( (getkey[1] == getkey[0]) && (0 != getkey[1]))
		{
			//Uart_Printf("\n%u, %u\n",getkey[1], getkey[0]);
			switch(getkey[1])
			{
				case 1:
					Uart_Printf("\nSW1����\n");
				break;
				case 2:
					Uart_Printf("\nSW2����\n");
				break;
				case 4:
					Uart_Printf("\nSW3����\n");
				break;
				case 8:
					Uart_Printf("\nSW4����\n");
				break;												
			}
		}
	}
}