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


void Uart0_Init_all(void);//初始化串口0
void Uart_Select(int ch);
void Uart_TxEmpty(int ch);
void Uart_Init(int mclk,int baud);
char Uart_Getch(void);//等待从PC串口获取1个字符
void Uart_GetString(char *string);//等待从PC串口获取字符串
int  Uart_GetIntNum(void);//等待从PC串口获取1个int，支持：十进制如1234，-1234，十六进制形式如0x1234，-0x234
void Uart_SendByte(int data);//开发板向PC发送1个字节
void Uart_Printf(char *fmt,...);//开发板向PC发送内容，参数与printf函数相同
void Uart_SendString(char *pt);//开发板向PC发送字符串



#ifdef __cplusplus
}
#endif

#endif 