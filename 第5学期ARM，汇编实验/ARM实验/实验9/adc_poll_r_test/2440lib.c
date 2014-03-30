#include "typedef.h"
#include "2440addr.h"
#include "2440lib.h"

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


U32 FCLK;
U32 HCLK;
U32 PCLK;
U32 UCLK;
U32 UPLL;


static int atoi_new(char * str)
{
	char * pch;
	int  tmp=0, i=0;
	for(pch=str;*pch!='\0';pch++)
	{
		if( ((*pch)>='0') && ( (*pch)<='9' ) )
		{
			i   = (*pch)-'0';
			tmp = tmp*10+i;	
		}
		else
		{
			return 0xefffffff;
		}
	}
	return tmp;
}

static void cal_cpu_bus_clk(void)
{
	U32 val;
	U8 m, p, s;
	
	val = rMPLLCON;
	m = (val>>12)&0xff;
	p = (val>>4)&0x3f;
	s = val&3;

	//(m+8)*FIN*2 不要超出32位数!
	FCLK = ((m+8)*(FIN/100)*2)/((p+2)*(1<<s))*100;
	
	val = rCLKDIVN;
	m = (val>>1)&3;
	p = val&1;	
	val = rCAMDIVN;
	s = val>>8;
	
	switch (m) {
	case 0:
		HCLK = FCLK;
		break;
	case 1:
		HCLK = FCLK>>1;
		break;
	case 2:
		if(s&2)
			HCLK = FCLK>>3;
		else
			HCLK = FCLK>>2;
		break;
	case 3:
		if(s&1)
			HCLK = FCLK/6;
		else
			HCLK = FCLK/3;
		break;
	}
	
	if(p)
		PCLK = HCLK>>1;
	else
		PCLK = HCLK;
		
	val = rUPLLCON;
	m = (val>>12)&0xff;
	p = (val>>4)&0x3f;
	s = val&3;
	UPLL = ((m+8)*FIN)/((p+2)*(1<<s));
	UCLK = (rCLKDIVN&8)?(UPLL>>1):UPLL;
}


void Uart0_Init_all(void)
{
    //*** PORT H GROUP
    //Ports  :  GPH10    GPH9  GPH8 GPH7  GPH6  GPH5 GPH4 GPH3 GPH2 GPH1  GPH0 
    //Signal : CLKOUT1 CLKOUT0 UCLK nCTS1 nRTS1 RXD1 TXD1 RXD0 TXD0 nRTS0 nCTS0
    //Binary :   10   ,  10     10 , 11    11  , 10   10 , 10   10 , 10    10
    rGPHCON = 0x2afaaa;
    rGPHUP  = 0x7ff;    // The pull up function is disabled GPH[10:0]
    cal_cpu_bus_clk();
    Uart_Init(0,115200);  //串口初始化 波特率为115200
    Uart_Select(0);  //选者串口0
}

static int whichUart=0;

void Uart_Init(int pclk,int baud)
{
    int i;
    if(pclk == 0)
    pclk    = PCLK;
    rUFCON0 = 0x0;   //UART channel 0 FIFO control register, FIFO disable
    rUFCON1 = 0x0;   //UART channel 1 FIFO control register, FIFO disable
    rUFCON2 = 0x0;   //UART channel 2 FIFO control register, FIFO disable
    rUMCON0 = 0x0;   //UART chaneel 0 MODEM control register, AFC disable
    rUMCON1 = 0x0;   //UART chaneel 1 MODEM control register, AFC disable
//UART0
    rULCON0 = 0x3;   //Line control register : Normal,No parity,1 stop,8 bits
     //    [10]       [9]     [8]        [7]        [6]      [5]         [4]           [3:2]        [1:0]
     // Clock Sel,  Tx Int,  Rx Int, Rx Time Out, Rx err, Loop-back, Send break,  Transmit Mode, Receive Mode
     //     0          1       0    ,     0          1        0           0     ,       01          01
     //   PCLK       Level    Pulse    Disable    Generate  Normal      Normal        Interrupt or Polling
    rUCON0  = 0x245;   // Control register
    rUBRDIV0=( (int)(pclk/16./baud+0.5) -1 );   //Baud rate divisior register 0
//UART1
    rULCON1 = 0x3;
    rUCON1  = 0x245;
    rUBRDIV1=( (int)(pclk/16./baud+0.5) -1 );
//UART2
    rULCON2 = 0x3;
    rUCON2  = 0x245;
    rUBRDIV2=( (int)(pclk/16./baud+0.5) -1 );    

    for(i=0;i<100;i++);
}

void Uart_Select(int ch)
{
    whichUart = ch;
}

void Uart_TxEmpty(int ch)
{
    if(ch==0)
    {
        while(!(rUTRSTAT0 & 0x4)); //Wait until tx shifter is empty.
    }      
    else if(ch==1)
    {
        while(!(rUTRSTAT1 & 0x4)); //Wait until tx shifter is empty.
    }   
    else if(ch==2)
    {
        while(!(rUTRSTAT2 & 0x4)); //Wait until tx shifter is empty.
    }
}

char Uart_Getch(void)
{
    if(whichUart==0)
    {       
        while(!(rUTRSTAT0 & 0x1)); //Receive data ready
        return RdURXH0();
    }
    else if(whichUart==1)
    {       
        while(!(rUTRSTAT1 & 0x1)); //Receive data ready
        return RdURXH1();
    }
    else if(whichUart==2)
    {
        while(!(rUTRSTAT2 & 0x1)); //Receive data ready
        return RdURXH2();
    }
    
    return 0 ;
}

void Uart_GetString(char *string)
{
    char *string2 = string;
    char c;
    while((c = Uart_Getch())!='\r')
    {
        if(c=='\b')
        {
            if( (int)string2 < (int)string )
            {
                Uart_Printf("\b \b");
                string--;
            }
        }
        else 
        {
            *string++ = c;
            Uart_SendByte(c);
        }
    }
    *string='\0';
    Uart_SendByte('\n');
}

int Uart_GetIntNum(void)
{
    char str[32];
    char *string = str;
    int base     = 10;
    int minus    = 0;
    int result   = 0;
    int lastIndex;    
    int i;
    
    Uart_GetString(string);
    
    if(string[0]=='-')
    {
        minus = 1;
        string++;
    }
    
    if(string[0]=='0' && (string[1]=='x' || string[1]=='X'))
    {
        base    = 16;
        string += 2;
    }
    
    lastIndex = strlen(string) - 1;
    
    if(lastIndex<0)
    {
        return -1;
    }
    
    if(string[lastIndex]=='h' || string[lastIndex]=='H' )
    {
        base = 16;
        string[lastIndex] = 0;
        lastIndex--;
    }

    if(base==10)
    {
        result = atoi_new(string);
        result = minus ? (-1*result):result;
    }
    else
    {
        for(i=0;i<=lastIndex;i++)
        {
            switch(string[i])
            {
            	case '0':
            		result = (result<<4);
            	break;
            	case '1':
            		result = (result<<4) + 1;
            	break; 
            	case '2':
            		result = (result<<4) + 2;
            	break;             	           	
            	case '3':
            		result = (result<<4) + 3;
            	break; 
            	case '4':
            		result = (result<<4) + 4;
            	break;  
             	case '5':
            		result = (result<<4) + 5;
            	break; 
            	case '6':
            		result = (result<<4) + 6;
            	break;  
            	case '7':
            		result = (result<<4) + 7;
            	break; 
            	case '8':
            		result = (result<<4) + 8;
            	break;   
            	case '9':
            		result = (result<<4) + 9;
            	break; 
            	case 'A':
            	case 'a':
            		result = (result<<4) + 10;
            	break;   
             	case 'B':
             	case 'b':
            		result = (result<<4) + 11;
            	break; 
            	case 'C':
            	case 'c':
            		result = (result<<4) + 12;
            	break;  
            	case 'D':
            	case 'd':
            		result = (result<<4) + 13;
            	break; 
            	case 'E':
            	case 'e':
            		result = (result<<4) + 14;
            	break; 
            	case 'F':
            	case 'f':
            		result = (result<<4) + 15;
            	break;              	             	           	            	
            }
        }
        result = minus ? (-1*result):result;        
    }
    return result;
}

void Uart_SendByte(int data)
{
    if(whichUart==0)
    {
        if(data=='\n')
        {
            while(!(rUTRSTAT0 & 0x2));
           // Delay(1);                 //because the slow response of hyper_terminal 
            WrUTXH0('\r');
        }
        while(!(rUTRSTAT0 & 0x2));   //Wait until THR is empty.
      //  Delay(1);
        WrUTXH0(data);
    }
    else if(whichUart==1)
    {
        if(data=='\n')
        {
            while(!(rUTRSTAT1 & 0x2));
            //Delay(1);                 //because the slow response of hyper_terminal 
            rUTXH1 = '\r';
        }
        while(!(rUTRSTAT1 & 0x2));   //Wait until THR is empty.
        //Delay(1);
        rUTXH1 = data;
    }   
    else if(whichUart==2)
    {
        if(data=='\n')
        {
            while(!(rUTRSTAT2 & 0x2));
            //Delay(1);                 //because the slow response of hyper_terminal 
            rUTXH2 = '\r';
        }
        while(!(rUTRSTAT2 & 0x2));   //Wait until THR is empty.
        //Delay(1);
        rUTXH2 = data;
    }       
}               

void Uart_SendString(char *pt)
{
    while(*pt)
    {
        Uart_SendByte(*pt++);
    }
}

void Uart_Printf(char *fmt,...)
{
    va_list ap;
    char string[256];

    va_start(ap,fmt);
    vsprintf(string,fmt,ap);
    Uart_SendString(string);
    va_end(ap);
}