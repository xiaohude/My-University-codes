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
#define NF_Enable()			{rNFCONT &= ~(1<<1);} //Ƭѡ
#define NF_Disable()		{rNFCONT |= (1<<1); } //ȡ��Ƭѡ
#define NF_Read_Byte()		(rNFDATA8) //������
#define NF_CLEAR_RB()    	{rNFSTAT |= (1<<2);} //���æ
#define NF_DETECT_RB()    	{while(!(rNFSTAT&(1<<2)));} //���æ

#define TACLS		28 
#define TWRPH0		28
#define TWRPH1		28

//��ʼ��nand flash������
void nand_init()
{
	//��ʼ����������
	rGPACON &= ~(0x3f<<17);
	rGPACON |=  (0x3f<<17);
	//��ʼ�����üĴ���
	rNFCONF &= ~( (3<<12)|(7<<8)|(7<<4)|1 );
	rNFCONF |=  ( (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4)|0 );
	//��ʼ�����ƼĴ���
	rNFCONT &= ~( (1<<12)|(1<<10)|(1<<9)|(1<<8)|(1<<1)|1 );
	rNFCONT |=  ( (0<<12)|(0<<10)|(0<<9)|(0<<8)|(1<<1)|1 );
}
//��λ
void nand_reset()
{
	NF_Enable();//Ƭѡ
	NF_CLEAR_RB();//�����ɱ�־
	NF_Send_Cmd(CMD_RESET);//���͸�λ����
	NF_DETECT_RB();//����Ƿ����
	NF_Disable();//ȡ��Ƭѡ
}
//д1ҳ����
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
//��1ҳ����
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
//���°�ҳ����
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
//����1������
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


//������
void Main(void)
{		
	unsigned char w_buf[512];
	unsigned char r_buf[512];
	unsigned char r2_buf[256];
	unsigned int i;
	//��ʼ������0�Է������
	Uart0_Init_all();
	nand_init();
	
	Uart_Printf("\n%s\n", "�������������ʼ����");
	Uart_Getch();
	nand_erase_block(4095);
	Uart_Printf("\n%s\n", "�������������ʼд������");
	Uart_Getch();	
	for(i=0; i<512; i++)
	{
		w_buf[i] = i%256;
	}
	nand_write_page(4095, 31, w_buf);
	Uart_Printf("\n%s\n", "�������������ʼ��������");
	Uart_Getch();
	nand_read_page(4095, 31, r_buf);
	for(i=0; i<512; i++)
	{
		Uart_Printf("%x\n", r_buf[i]);
	}	
	
	
	Uart_Printf("\n%s\n", "�������������ʼ��ȡ�°�ҳ");
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