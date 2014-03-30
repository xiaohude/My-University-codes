#include "2440addr.h" // ���мĴ����Ķ���������� 
#include "2440lib.h" //�õ�д�õĴ���ͨ�ų��� 
// ������ʱ 
void delay(void) 
{ 
 int i; 
  for(i=0; i<20000000; i++); 
} 
//Led �����õ������ų�ʼ�� 
void Led_Init(void) 
{ 
  rGPFCON &= ~( (3<<8)|(3<<10)|(3<<12)|(3<<14)); 
  rGPFCON |= ( (1<<8)|(1<<10)|(1<<12)|(1<<14)); 
  rGPFUP &= 0x0F; 
  rGPFDAT |= 0xFF; // ��ʼ��ȫ�� 
}

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

 
// ���������C ��Main����������Сдmain 

void Main(void) 
{ 
 
unsigned int getkey[2],getbuf;
 Uart0_Init_all();//Ϊ��ʹ�ô��ڷ�����ԣ��ʼ��봮����س�ʼ���������� 2440lib.c 2440lib.h 
  Led_Init() ; // �Լ�д�� Led ���ų�ʼ�� 
 Uart_Printf("\n%s\n", "Led��������Ѿ���ʼ����ϣ��밴�������ʼ��˸"); // ���������ʾ 
 Uart_Getch(); //������ȴ�PC���ڷ���1 ���ַ� 
/*
 while(1) 
 {  
  rGPFDAT &=(5<<4) ; // ����~ 
  Uart_Printf("\n%s\n", "Led����"); 
  delay(); 
  rGPFDAT |= 0xFF; //����~~~~~~~~ 
  Uart_Printf("\n%s\n", "Led��"); 
  delay(); 
 }*/
 
 
    
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
					Uart_Printf("\nSW1����\n");//���µ�һ������������ˮ�Ƶ�Ч��
					while(getkey[1]==1)
					{
					
					rGPFDAT |= 0xFF;
					rGPFDAT &=~(1<<4);
					delay();
					rGPFDAT |= 0xFF;
					rGPFDAT &=~(2<<4);
					delay();
					rGPFDAT |= 0xFF;
					rGPFDAT &=~(4<<4);
					delay();
					rGPFDAT |= 0xFF;
					rGPFDAT &=~(8<<4);
					delay();
					
					
					
					getbuf = ~rGPGDAT;            //�����⼸�д�����Ϊ�˲��õ���������ȥ���ٰ������İ�����ʱ����Ա任�Ƶ���˸Ч����
		getkey[1] |= (getbuf&(0x1<<3))>> (3-2);         
		getkey[1] |= (getbuf&(0x1<<11))>> (11-3);
		getbuf = ~rGPFDAT; 
		getkey[1] |= getbuf&0x1;
		getkey[1] |= (getbuf&(0x1<<2))>> (2-1);	
					
					
					}
				break;
				case 2:
					Uart_Printf("\nSW2����\n");//���µڶ�������������Ծ�Ƶ�Ч����
					while(getkey[1]==2)
					{
					
					rGPFDAT |= 0xFF;
					rGPFDAT &=~(6<<4);
					delay();
					rGPFDAT |= 0xFF;
					rGPFDAT &=~(9<<4);
					delay();
					
					
					
					
					getbuf = ~rGPGDAT;
		getkey[1] |= (getbuf&(0x1<<3))>> (3-2);
		getkey[1] |= (getbuf&(0x1<<11))>> (11-3);
		getbuf = ~rGPFDAT; 
		getkey[1] |= getbuf&0x1;
		getkey[1] |= (getbuf&(0x1<<2))>> (2-1);	
					
					
					}
				break;
				case 4:
					Uart_Printf("\nSW3����\n");//���µ�������ť����ָ���һ������˸��Ч��
					while(getkey[1]==4)
					{
					
					rGPFDAT |= 0xFF;
					rGPFDAT &=~(1<<4);
					delay();
					rGPFDAT |= 0xFF;
					rGPFDAT &=~(4<<4);
					delay();
					rGPFDAT |= 0xFF;
					rGPFDAT &=~(2<<4);
					delay();
					rGPFDAT |= 0xFF;
					rGPFDAT &=~(8<<4);
					delay();
					
					
					
					getbuf = ~rGPGDAT;
		getkey[1] |= (getbuf&(0x1<<3))>> (3-2);
		getkey[1] |= (getbuf&(0x1<<11))>> (11-3);
		getbuf = ~rGPFDAT; 
		getkey[1] |= getbuf&0x1;
		getkey[1] |= (getbuf&(0x1<<2))>> (2-1);	
					
					
					}
				break;
				case 8:
					Uart_Printf("\nSW4����\n");//���µ��ĸ�����ֻ�����ĸ��ơ�
					rGPFDAT |= 0xFF;
					rGPFDAT &=~(8<<4);
				break;												
			}
		}
	}
} 




