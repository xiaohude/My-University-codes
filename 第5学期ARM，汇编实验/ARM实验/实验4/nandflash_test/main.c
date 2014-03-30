#include "2440addr.h"
#include "2440lib.h"

#define CMD_READ1 0x00
#define CMD_READ1_2ndhalf 0x01
#define CMD_RESET 0xFF
#define CMD_WRITE_1stcycle 0x80
#define CMD_WRITE_2ndcycle 0x10
#define CMD_ERASE_1stcycle 0x60
#define CMD_ERASE_2ndcycle 0xD0


#define NF_Send_Cmd(cmd)	{rNFCMD  = (cmd); }
#define NF_Send_Addr(addr)	{rNFADDR = (addr); }
#define NF_Send_Data(data)	{rNFDATA8 = (data); }	
#define NF_Enable()			{rNFCONT &= ~(1<<1);} //片选
#define NF_Disable()		{rNFCONT |= (1<<1); } //取消片选
#define NF_Read_Byte()		(rNFDATA8) //读数据
#define NF_CLEAR_RB()    	{rNFSTAT |= (1<<2);} //清除忙
#define NF_DETECT_RB()    	{while(!(rNFSTAT&(1<<2)));} //检测忙

#define TACLS		28 
#define TWRPH0		28
#define TWRPH1		28

//初始化nand flash控制器
void nand_init()
{
	//初始化引脚设置
	rGPACON &= ~(0x3f<<17);
	rGPACON |=  (0x3f<<17);
	//初始化配置寄存器
	rNFCONF &= ~( (3<<12)|(7<<8)|(7<<4)|1 );
	rNFCONF |=  ( (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4)|0 );
	//初始化控制寄存器
	rNFCONT &= ~( (1<<12)|(1<<10)|(1<<9)|(1<<8)|(1<<1)|1 );
	rNFCONT |=  ( (0<<12)|(0<<10)|(0<<9)|(0<<8)|(1<<1)|1 );
}
//复位
void nand_reset()
{
	NF_Enable();//片选
	NF_CLEAR_RB();//清除完成标志
	NF_Send_Cmd(CMD_RESET);//发送复位命令
	NF_DETECT_RB();//检测是否完成
	NF_Disable();//取消片选
}
//写1页数据
void nand_write_page(unsigned int block, unsigned int page, unsigned char* buf)
{
	unsigned int i;
	unsigned int blockpage = (block<<5) + page;
	unsigned char *pbuf = buf;
	nand_reset();
	NF_Enable();
	NF_CLEAR_RB();
	NF_Send_Cmd(CMD_WRITE_1stcycle);
	NF_Send_Addr(0);
	NF_Send_Addr(blockpage & 0xff);
	NF_Send_Addr((blockpage>>8) & 0xff);
	NF_Send_Addr((blockpage>>16) & 0xff);
	for(i=0; i<512; i++)
	{
		NF_Send_Data(*pbuf++);
	}
	NF_Send_Cmd(CMD_WRITE_2ndcycle);
	NF_DETECT_RB();
	NF_Disable();	
}
//读1页数据
void nand_read_page(unsigned int block, unsigned int page, unsigned char* buf)
{
	unsigned int i;
	unsigned int blockpage = (block<<5) + page;
	unsigned char *pbuf = buf;
	nand_reset();
	NF_Enable();
	NF_CLEAR_RB();
	NF_Send_Cmd(CMD_READ1);
	NF_Send_Addr(0);
	NF_Send_Addr(blockpage & 0xff);
	NF_Send_Addr((blockpage>>8) & 0xff);
	NF_Send_Addr((blockpage>>16) & 0xff);
	NF_DETECT_RB();
	for(i=0; i<512; i++)
	{
		*pbuf++ = NF_Read_Byte();
	}
	NF_Disable();	
}
//读下半页数据
void nand_read_2nd_half_page(unsigned int block, unsigned int page, unsigned char* buf)
{
	unsigned int i;
	unsigned int blockpage = (block<<5) + page;
	unsigned char *pbuf = buf;
	nand_reset();
	NF_Enable();
	NF_CLEAR_RB();
	NF_Send_Cmd(CMD_READ1_2ndhalf);
	NF_Send_Addr(0);
	NF_Send_Addr(blockpage & 0xff);
	NF_Send_Addr((blockpage>>8) & 0xff);
	NF_Send_Addr((blockpage>>16) & 0xff);
	NF_DETECT_RB();
	for(i=0; i<256; i++)
	{
		*pbuf++ = NF_Read_Byte();
	}
	NF_Disable();		
}
//擦除1块数据
void nand_erase_block(unsigned int block)
{
	unsigned int blockpage = (block<<5);
	nand_reset();
	NF_Enable();
	NF_CLEAR_RB();
	NF_Send_Cmd(CMD_ERASE_1stcycle);
	NF_Send_Addr(blockpage & 0xff);
	NF_Send_Addr((blockpage>>8) & 0xff);
	NF_Send_Addr((blockpage>>16) & 0xff);
	NF_Send_Cmd(CMD_ERASE_2ndcycle);
	NF_DETECT_RB();
	NF_Disable();	
}


//主函数
void Main(void)
{		
	unsigned char w_buf[512];
	unsigned char r_buf[512];
	unsigned char r2_buf[256];
	unsigned int i;
	//初始化串口0以方便调试
	Uart0_Init_all();
	nand_init();
	
	Uart_Printf("\n%s\n", "按下任意键，开始擦除");
	Uart_Getch();
	nand_erase_block(4095);
	Uart_Printf("\n%s\n", "按下任意键，开始写入数据");
	Uart_Getch();	
	for(i=0; i<512; i++)
	{
		w_buf[i] = i%256;
	}
	nand_write_page(4095, 31, w_buf);
	Uart_Printf("\n%s\n", "按下任意键，开始读出数据");
	Uart_Getch();
	nand_read_page(4095, 31, r_buf);
	for(i=0; i<512; i++)
	{
		Uart_Printf("%x\n", r_buf[i]);
	}	
	
	
	Uart_Printf("\n%s\n", "按下任意键，开始读取下半页");
	Uart_Getch();	
	nand_read_2nd_half_page(4095, 31, r2_buf);
	for(i=0; i<256; i++)
	{
		Uart_Printf("%x\n", r2_buf[i]);
	}
	
	Uart_Getch();
	while(1)
	{
		
	}
}