//#include <stdio.h> /*标准输入输出定义*/ 
//#include <stdlib.h> /*标准函数库定义*/ 
//#include <unistd.h> /*Unix 标准函数定义*/ 
//#include <sys/types.h> 
//#include <sys/stat.h> 
//#include <fcntl.h> /*文件控制定义*/ 
//#include <termios.h> /*PPSIX 终端控制定义*/ 
///#include <errno.h> /*错误号定义*/ 
//#include <string.h>
#define FALSE -1 
#define TRUE 0 
//static int fd; 

void set_speed(int fd, int speed);

int set_Parity(int fd,int databits,int stopbits,int parity) ;

int OpenDev(char *Dev); 

int uart_send(int fd,char * buf);

int uart_res(int fd );
