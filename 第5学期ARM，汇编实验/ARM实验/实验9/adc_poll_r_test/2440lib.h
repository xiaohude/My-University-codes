#ifndef __2440lib_h__
#define __2440lib_h__

#ifdef __cplusplus
extern "C" {
#endif

#include "typedef.h"
#define FIN 	(12000000)

extern U32 FCLK;
extern U32 HCLK;
extern U32 PCLK;
extern U32 UCLK;
extern U32 UPLL;


void Uart0_Init_all(void);//��ʼ������0
void Uart_Select(int ch);
void Uart_TxEmpty(int ch);
void Uart_Init(int mclk,int baud);
char Uart_Getch(void);//�ȴ���PC���ڻ�ȡ1���ַ�
void Uart_GetString(char *string);//�ȴ���PC���ڻ�ȡ�ַ���
int  Uart_GetIntNum(void);//�ȴ���PC���ڻ�ȡ1��int��֧�֣�ʮ������1234��-1234��ʮ��������ʽ��0x1234��-0x234
void Uart_SendByte(int data);//��������PC����1���ֽ�
void Uart_Printf(char *fmt,...);//��������PC�������ݣ�������printf������ͬ
void Uart_SendString(char *pt);//��������PC�����ַ���



#ifdef __cplusplus
}
#endif

#endif 