//#include <stdio.h> /*��׼�����������*/ 
//#include <stdlib.h> /*��׼�����ⶨ��*/ 
//#include <unistd.h> /*Unix ��׼��������*/ 
//#include <sys/types.h> 
//#include <sys/stat.h> 
//#include <fcntl.h> /*�ļ����ƶ���*/ 
//#include <termios.h> /*PPSIX �ն˿��ƶ���*/ 
///#include <errno.h> /*����Ŷ���*/ 
//#include <string.h>
#define FALSE -1 
#define TRUE 0 
//static int fd; 

void set_speed(int fd, int speed);

int set_Parity(int fd,int databits,int stopbits,int parity) ;

int OpenDev(char *Dev); 

int uart_send(int fd,char * buf);

int uart_res(int fd );
