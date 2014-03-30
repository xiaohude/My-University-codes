#include "2440addr.h" // 所有寄存器的定义包含进来 
#include "2440lib.h" //用到写好的串口通信程序 
// 粗略延时 
void delay(void) 
{ 
 int i; 
  for(i=0; i<20000000; i++); 
} 
//Led 连接用到的引脚初始化 
void Led_Init(void) 
{ 
  rGPFCON &= ~( (3<<8)|(3<<10)|(3<<12)|(3<<14)); 
  rGPFCON |= ( (1<<8)|(1<<10)|(1<<12)|(1<<14)); 
  rGPFUP &= 0x0F; 
  rGPFDAT |= 0xFF; // 初始灯全灭 
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

 
// 汇编跳到的C 的Main函数，不是小写main 

void Main(void) 
{ 
 
unsigned int getkey[2],getbuf;
 Uart0_Init_all();//为了使用串口方便调试，故加入串口相关初始化函数，在 2440lib.c 2440lib.h 
  Led_Init() ; // 自己写的 Led 引脚初始化 
 Uart_Printf("\n%s\n", "Led相关引脚已经初始化完毕！请按任意键开始闪烁"); // 串口输出提示 
 Uart_Getch(); //开发板等待PC串口发来1 个字符 
/*
 while(1) 
 {  
  rGPFDAT &=(5<<4) ; // 灯亮~ 
  Uart_Printf("\n%s\n", "Led亮啊"); 
  delay(); 
  rGPFDAT |= 0xFF; //灯灭~~~~~~~~ 
  Uart_Printf("\n%s\n", "Led灭"); 
  delay(); 
 }*/
 
 
    
	Key_Init();
	Uart_Printf("\n%s\n", "Key相关引脚已经初始化完毕！开始运行~~");
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
					Uart_Printf("\nSW1按下\n");//按下第一个按键出现流水灯的效果
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
					
					
					
					getbuf = ~rGPGDAT;            //下面这几行代码是为了不让灯无限闪下去，再按其他的按键的时候可以变换灯的闪烁效果。
		getkey[1] |= (getbuf&(0x1<<3))>> (3-2);         
		getkey[1] |= (getbuf&(0x1<<11))>> (11-3);
		getbuf = ~rGPFDAT; 
		getkey[1] |= getbuf&0x1;
		getkey[1] |= (getbuf&(0x1<<2))>> (2-1);	
					
					
					}
				break;
				case 2:
					Uart_Printf("\nSW2按下\n");//按下第二个按键出现跳跃灯的效果。
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
					Uart_Printf("\nSW3按下\n");//按下第三个按钮后出现隔着一个灯闪烁的效果
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
					Uart_Printf("\nSW4按下\n");//按下第四个按键只亮第四个灯。
					rGPFDAT |= 0xFF;
					rGPFDAT &=~(8<<4);
				break;												
			}
		}
	}
} 




