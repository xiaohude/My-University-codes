#include "2440addr.h"
#include "2440lib.h"

#define	ROM_BASE 0x0 //Nor Flash��ʼ��ַ
#define	CMD_ADDR0 *((volatile unsigned short *)(0x5555*2+ROM_BASE)) //����Ĵ���0��ַ
#define	CMD_ADDR1 *((volatile unsigned short *)(0x2aaa*2+ROM_BASE)) //����Ĵ���1��ַ

//��ȡһ���洢��Ԫ
unsigned short flash_read(unsigned int addr)
{
	//ʹ��ָ��ķ�ʽֱ�ӿ��Զ�ȡ
	return *((volatile unsigned short *)(addr));
}
//д��һ���洢��ԪһЩ����
void flash_write(unsigned int addr, unsigned short data)
{
	unsigned short tmp;
	//��������
	CMD_ADDR0 = 0xaaaa;
	CMD_ADDR1 = 0x5555;
	CMD_ADDR0 = 0xa0a0;
	*(volatile unsigned short *)addr = data;
	//�ȴ����
	while(1)
	{
		//�ж�DQ6
		tmp = *(volatile unsigned short *)addr & 0x40;
		if(tmp != (*(volatile unsigned short *)addr & 0x40) )
		{continue;}
		//�ж�DQ7
		if( (*(volatile unsigned short *)addr & 0x80) == (data&0x80) )	
		{break;}
	}
}
//����1����������ַҪ����4KB����
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
	//�ȴ����
	while(1)
	{
		//�ж�DQ6
		tmp = *(volatile unsigned short *)sector_start_addr & 0x40;
		if(tmp != (*(volatile unsigned short *)sector_start_addr & 0x40) )
		{continue;}
		//�ж�DQ7
		if(*((volatile unsigned short *)sector_start_addr) & 0x80)		
		{break;}
	}
}
//����1���飬��ַҪ����32KB����
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
	//�ȴ����
	while(1)
	{
		//�ж�DQ6
		tmp = *(volatile unsigned short *)block_start_addr & 0x40;
		if(tmp != (*(volatile unsigned short *)block_start_addr & 0x40) )
		{continue;}
		//�ж�DQ7
		if(*((volatile unsigned short *)block_start_addr) & 0x80)		
		{break;}
	}
}

void Main(void)
{	
	//���1�������ĵ�ַΪ0x1ff000�����1����ĵ�ַΪ0x1f8000
	unsigned int addr;
	unsigned short w_datas[4];
	
	//��ʼ������0�Է������
	Uart0_Init_all();
	
	
	//���³���Ϊ���Բ���������д�롢��ȡ
	addr = 0x1ff000;
	Uart_Printf("\n%s %x\n", "�������������ʼ����1����������ʼ��ַ��", addr);
	Uart_Getch();
	flash_erase_sector(addr);
	
	//���³���Ϊ���Բ����顢д�롢��ȡ
	addr = 0x1f8000;
	Uart_Printf("\n%s %x\n", "�������������ʼ����1���飬��ʼ��ַ��", addr);
	Uart_Getch();
	flash_erase_block(addr);	
	
	//���³���Ϊ����д�롢��ȡ
	Uart_Printf("\n%s\n", "�������������ʼд��~~");
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
	
	Uart_Printf("\n%s\n", "�������������ʼ��ȡ~~");
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