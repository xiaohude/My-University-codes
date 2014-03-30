#include "2440addr.h"
#include "2440lib.h"

#define	ROM_BASE 0x0 //Nor Flash开始地址
#define	CMD_ADDR0 *((volatile unsigned short *)(0x5555*2+ROM_BASE)) //命令寄存器0地址
#define	CMD_ADDR1 *((volatile unsigned short *)(0x2aaa*2+ROM_BASE)) //命令寄存器1地址

//读取一个存储单元
unsigned short flash_read(unsigned int addr)
{
	//使用指针的方式直接可以读取
	return *((volatile unsigned short *)(addr));
}
//写入一个存储单元一些内容
void flash_write(unsigned int addr, unsigned short data)
{
	unsigned short tmp;
	//命令序列
	CMD_ADDR0 = 0xaaaa;
	CMD_ADDR1 = 0x5555;
	CMD_ADDR0 = 0xa0a0;
	*(volatile unsigned short *)addr = data;
	//等待完成
	while(1)
	{
		//判断DQ6
		tmp = *(volatile unsigned short *)addr & 0x40;
		if(tmp != (*(volatile unsigned short *)addr & 0x40) )
		{continue;}
		//判断DQ7
		if( (*(volatile unsigned short *)addr & 0x80) == (data&0x80) )	
		{break;}
	}
}
//擦除1个扇区，地址要满足4KB对齐
void flash_erase_sector(unsigned int sector_start_addr)
{
	unsigned short tmp;
	
	sector_start_addr += ROM_BASE;	
	
	CMD_ADDR0 = 0xaaaa;
	CMD_ADDR1 = 0x5555;
	CMD_ADDR0 = 0x8080;
	CMD_ADDR0 = 0xaaaa;
	CMD_ADDR1 = 0x5555;
	*(volatile unsigned short *)sector_start_addr = 0x3030;
	//等待完成
	while(1)
	{
		//判断DQ6
		tmp = *(volatile unsigned short *)sector_start_addr & 0x40;
		if(tmp != (*(volatile unsigned short *)sector_start_addr & 0x40) )
		{continue;}
		//判断DQ7
		if(*((volatile unsigned short *)sector_start_addr) & 0x80)		
		{break;}
	}
}
//擦除1个块，地址要满足32KB对齐
void flash_erase_block(unsigned int block_start_addr)
{
	unsigned short tmp;
	
	block_start_addr += ROM_BASE;	
	
	CMD_ADDR0 = 0xaaaa;
	CMD_ADDR1 = 0x5555;
	CMD_ADDR0 = 0x8080;
	CMD_ADDR0 = 0xaaaa;
	CMD_ADDR1 = 0x5555;
	*(volatile unsigned short *)block_start_addr = 0x5050;
	//等待完成
	while(1)
	{
		//判断DQ6
		tmp = *(volatile unsigned short *)block_start_addr & 0x40;
		if(tmp != (*(volatile unsigned short *)block_start_addr & 0x40) )
		{continue;}
		//判断DQ7
		if(*((volatile unsigned short *)block_start_addr) & 0x80)		
		{break;}
	}
}

void Main(void)
{	
	//最后1个扇区的地址为0x1ff000，最后1个块的地址为0x1f8000
	unsigned int addr;
	unsigned short w_datas[4];
	
	//初始化串口0以方便调试
	Uart0_Init_all();
	
	
	//以下程序为测试擦除扇区、写入、读取
	addr = 0x1ff000;
	Uart_Printf("\n%s %x\n", "按下任意键，开始擦除1个扇区，开始地址：", addr);
	Uart_Getch();
	flash_erase_sector(addr);
	
	//以下程序为测试擦除块、写入、读取
	addr = 0x1f8000;
	Uart_Printf("\n%s %x\n", "按下任意键，开始擦除1个块，开始地址：", addr);
	Uart_Getch();
	flash_erase_block(addr);	
	
	//以下程序为测试写入、读取
	Uart_Printf("\n%s\n", "按下任意键，开始写入~~");
	Uart_Getch();
	w_datas[0] = 0x12; w_datas[1] = 0x34;
	w_datas[2] = 0x56; w_datas[3] = 0x78;
	addr = 0x1ff000;
	flash_write(addr, w_datas[0]);
	addr += 2;
	flash_write(addr, w_datas[1]);
	addr += 2;
	flash_write(addr, w_datas[2]);
	addr += 2;
	flash_write(addr, w_datas[3]);	
	
	Uart_Printf("\n%s\n", "按下任意键，开始读取~~");
	Uart_Getch();
	addr = 0x1ff000;
	Uart_Printf("\n%x\n", flash_read(addr));
	addr += 2;
	Uart_Printf("\n%x\n", flash_read(addr));
	addr += 2;
	Uart_Printf("\n%x\n", flash_read(addr));
	addr += 2;
	Uart_Printf("\n%x\n", flash_read(addr));
		
	Uart_Getch();
	
	while(1)
	{
		
	}
}