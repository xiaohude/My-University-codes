#include "base.h"
#include "sql.h"
#include <stddef.h>
#include "uart.h"
int speed_arr[] = { B38400, B19200, B9600, B4800, B2400, B1200, B300, 
B38400, B19200, B9600, B4800, B2400, B1200, B300, }; 
int name_arr[] = {38400, 19200, 9600, 4800, 2400, 1200, 300, 38400, 
19200, 9600, 4800, 2400, 1200, 300, }; 


int base_recv(int dm_node_id);
int base_send(int dm_node_id, char * dm_buff, int dm_num);
char res_buff[4096]="\0";
int flag=0;


int  main()
{
 	int res_num;
 	int res_id=1;
	pid_t p2;
	pthread_t th1;
	void *rev;
	char *returnchar;

	


 while (1)
{
	//res_buff[0]='\0';
    int fd;
    char *dev = "/dev/ttyS1";
	fd = OpenDev(dev); 
	set_speed(fd,9600); 
	if (set_Parity(fd,8,1,'N' )== FALSE)
 	{ 
	printf("Set Parity Errorn"); 
	exit (0); 
	} 
	//strcat(res_buff,"000000001+ba+0001;");
	//printf("moni recive  res_buff=%s\n",res_buff);
	//res_num=25;


  	do
   	{
        res_num = uart_res(fd);
		sleep(1);
   		printf("main___res_num=%d\n",res_num);
  	}while(res_num<2);
    close(fd);
	if(res_num>=2)
	{ 
  		 switch(res_buff[10])
  		{
   		 case  's' : flag = 0 ;  p2=fork() ; break;
   		 case  't' : flag = 1 ;  p2=fork() ; break;
   	 	 case  'd' : flag = 2 ;  p2=fork() ; break;
    	 case  'b' : flag = 3 ;  p2=fork() ; break;
		 case  'T' : flag = 4 ;  p2=fork() ; break;
		 case  'D' : flag = 5 ;  p2=fork() ; break;
  		};
		res_num = 0;
    }
	if(p2==0)
		break;
    sleep(1);
}
  
	if(p2==0)
	{
  		printf("in zi jincheng ~~~~~\n");
       
  		if(flag == 0)
  		{
    		switch(res_buff[11])
    		{
     			case  'a' : pthread_create(&th1,NULL,(void*)			(&staff_add_pth),(void *)res_buff) ;  break;
    			case  'd'  :  pthread_create(&th1,NULL,(void*)			(&staff_delete_pth),(void *)res_buff) ;  break;
    			case  'u'  :  pthread_create(&th1,NULL,(void*)			(&staff_change_pth),(void *)res_buff) ;  break;
    			case  'l'  :  pthread_create(&th1,NULL,(void*)			(&staff_find_pth),(void *)res_buff) ;  break;
	 
   		};
    		pthread_join(th1,&rev);
      
 		}

  		else if(flag  == 1)
  		{
 			switch(res_buff[11])
    		{
     			case  'n' : pthread_create(&th1,NULL,(void*)			(&table_new_pth),(void *)res_buff) ;  break;
    			case  'o'  :  pthread_create(&th1,NULL,(void*)			(&table_new_pth),(void *)res_buff) ;  break;
   				case  'c'  :  pthread_create(&th1,NULL,(void*)			(&table_check_pth),(void *)res_buff) ;  break;
    			//case  'k'  :  pthread_create(&th1,NULL,(void*)			(&table_trattic_pth),(void *)res_buff) ;  break;
   			};
    		pthread_join(th1,&rev);
   		}
 	 	else if(flag  == 2)
  		{
			switch(res_buff[11])
    		{
    	 		case  'n' : pthread_create(&th1,NULL,(void*)			(&dishes_add_pth),(void *)res_buff) ;  break;
    			case  'd'  :  pthread_create(&th1,NULL,(void*)			(&dishes_delete_pth),(void *)res_buff) ;  break;
    			case  'u'  :  pthread_create(&th1,NULL,(void*)			(&dishes_change_pth),(void *)res_buff) ;  break;
	 
   			};
    	pthread_join(th1,&rev);
  		}
		else if(flag == 3)
  		{
      		switch(res_buff[11])
    		{
    		 	case  'q' : pthread_create(&th1,NULL,(void*)(&bill_find_pth),(void *)res_buff) ;  break; 
	 			case  'a' : pthread_create(&th1,NULL,(void*)(&bill_find_all),(void *)res_buff) ;  break; 
 				//case  's' : pthread_create(&th1,NULL,(void*)			(&manage_staff),(void *)res_buff) ;  break; 
   			};
    		pthread_join(th1,&rev);
 	 	}  

  		else if(flag == 4)
  		{
    	  	switch(res_buff[11])
    		{
    		 	case  'b' : pthread_create(&th1,NULL,(void*)			(&manage_money),(void *)res_buff) ;  break; 
	 			case  'd' : pthread_create(&th1,NULL,(void*)			(&manage_dishes),(void *)res_buff) ;  break; 
 				case  's' : pthread_create(&th1,NULL,(void*)			(&manage_staff),(void *)res_buff) ;  break; 
				//case  'm' : pthread_create(&th1,NULL,(void*)			(&manage_staff),(void *)res_buff) ;  break; 
   			};
    		pthread_join(th1,&rev);
 		} 
		else if(flag == 5)
  		{
    	  	switch(res_buff[11])
    		{
    	 		case  'd' : pthread_create(&th1,NULL,(void*)			(&dished_add_pth),(void *)res_buff) ;  break; 
	 			//case  'd' : pthread_create(&th1,NULL,(void*)			(&manage_dishes),(void *)res_buff) ;  break; 
 				//case  's' : pthread_create(&th1,NULL,(void*)			(&manage_staff),(void *)res_buff) ;  break; 
   			};
    		pthread_join(th1,&rev);
 	 	} 
   
    exit(0);
	printf("jincheng mowei    \n");
    }
	sleep(1);//////////very  important!!!!
	

  //}

	printf("main    over!!\n");
	return 0;
}
int base_recv(int dm_node_id)
{
	int fd,c=0,res,ret_temp,i,j,hoho,hohonum,okres,uou,ret_mm=0,test_id;
	struct termios newtio;
	unsigned char char_temp,sum,num_temp;
	static char mama[60],ok_buff[70],mid_num[60];
	char yu,oof,rfe;
	printf("Start...\n");
	/*Žò¿ªpcµÄcom1ÍšÑ¶¶Ë¿Ú*/
	fd = open( MODEMDEVICE,O_RDWR|O_NOCTTY);
	if (fd<0) {
		perror("MODEMDEVICE");
		exit(1);
		}
	printf("Open...\n");
	/*³õÊŒ»¯ÐÂµÄnewtioœá¹¹*/
	bzero(&newtio,sizeof(newtio));
	/*ÍšÑ¶Ð­Òé8n1*/
	newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD ;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;

	newtio.c_lflag = 0;

	tcflush (fd, TCIOFLUSH);//zhao

	tcsetattr(fd, TCSANOW, &newtio);
	printf("Writing....\n");

	sum = 0;
	char_temp=DLE;
	res = write(fd,&char_temp,1);
	char_temp=STX;
	res = write(fd,&char_temp,1);

	//char_temp=I_O_COM;
	char_temp=0x60;/////
	sum+= char_temp;
	res = write(fd,&char_temp,1);

	char_temp=0;
	sum+= char_temp;
	res = write(fd,&char_temp,1);

	char_temp=0;
	sum+= char_temp;
	res = write(fd,&char_temp,1);

	//char_temp=(unsigned char)(dm_node_id>>8);//(ÕÔ)žÄÎª(dm_node_id<<8)ÊÔÒ»ÏÂ
    char_temp=0x00;
	sum+= char_temp;
	res = write(fd,&char_temp,1);

	char_temp=(unsigned char)(dm_node_id);
	sum+= char_temp;
	res = write(fd,&char_temp,1);

	char_temp=UART_RES;
	sum+= char_temp;
	res = write(fd,&char_temp,1);

	char_temp=sum;
	res = write(fd,&char_temp,1);
	char_temp=DLE;
	res = write(fd,&char_temp,1);
	char_temp=ETX;
	res = write(fd,&char_temp,1);
       ret_temp=0;

		bzero(res_buff,sizeof(*res_buff));
		sleep(1);
		res =read(fd,res_buff,80);		//printf("s1=%c\n",res_buff[9]);
		okres=res-4;
		if(res==0)
		{
          printf("\n waiting input a string.....\n");
		  printf("\n");
		  return (1);
		}
		if(res_buff[okres]==0x09)
		       {
			   printf("**** no string ****  \n");
			   printf("\n");
			   ret_mm=1;
			   return (1);
			   }
	   else
	        if(res==2)
			   ret_mm=1;
	        else
   		       ret_mm=2;
	      printf("the received string is: %d \n",res-11);
		for(i=8;i<okres+1;i++)
		   {
		      bzero(mama,sizeof(*mama));
			  sprintf(mama,"%c",res_buff[i]);
			  if ((mama[0]=='f')&&(mama[1]=='f'))
			   {
				printf("%c%c",mama[6],mama[7]);
			    bzero(mama,sizeof(*mama));
			   }
			   else
			   {
	//		   	 printf("i  = %d",i);
			     printf("%c%c",mama[0],mama[1]);
			   }
			}
		if(res==2) {
			printf("in base_recv   res=%d buff= %s\n",res,res_buff);

			if(res_buff[0]==DLE)	{
				switch (res_buff[1]) {
					case COM_ACCEPTED:
						ret_temp=-1;
						break;
					case COM_NO_OP:
						printf("COM_NO_OP\n");
						ret_temp=-2;
						break;
					case  RESPONSE_TIMEOUT:
						printf("RESPONSE_TIMEOU\n");
						ret_temp=-3;
						break;
					case  NETWORK_TIMEOUT:
						printf("NETWORK_TIMEOUT\n");
						ret_temp=-4;
						break;
					case  RESPONSE_ERROR:
						printf("RESPONSE_ERROR\n");
						ret_temp=-5;
						break;
					case  SERIAL_ERROR:
						printf("SERIAL_ERROR\n");
						ret_temp=-6;
						break;
					case  INVALID_LENGTH:
						printf("INVALID_LENGTH\n");
						ret_temp=-7;
						break;
					case  INVALID_DLE_SEQUENCE:
						printf("INVALID_DLE_SEQUENCE\n");
						ret_temp=-8;
						break;
					default:
						printf("ERROR\n");
						ret_temp=-9;
						break;

					}
				}

		     }
			//char  *b;
			//b=res_buff[8];
		
			 // printf("\ns3=%c\n",res_buff[8]);
		  	bzero(res_buff,sizeof(*res_buff));///clear--zhao
			bzero(ok_buff,sizeof(*ok_buff));///clear--zhao
			printf("\n receive end\n");

//The buffer can be cleared by a Write UART Buffer command with no payload
	sum = 0;
	char_temp=DLE;
	res = write(fd,&char_temp,1);
	char_temp=STX;
	res = write(fd,&char_temp,1);

	char_temp=I_O_COM;
	sum+= char_temp;
	res = write(fd,&char_temp,1);

	char_temp=0x00;
	sum+= char_temp;
	res = write(fd,&char_temp,1);

	char_temp=0x00;
	sum+= char_temp;
	res = write(fd,&char_temp,1);

	//char_temp=(unsigned char)(dm_node_id>>8);//£šÕÔ£©žÄÎª(dm_node_id<<8)ÊÔÊÔ
	char_temp=0x00;
        sum+= char_temp;
	res = write(fd,&char_temp,1);

	char_temp=(unsigned char)(dm_node_id);
        printf("the dmnood is %d",dm_node_id);
	sum+= char_temp;
	res = write(fd,&char_temp,1);

	char_temp=UART_SEND;//41
	sum+= char_temp;
	res = write(fd,&char_temp,1);

	char_temp=sum;
	res = write(fd,&char_temp,1);

	char_temp=DLE;
	res = write(fd,&char_temp,1);
	char_temp=ETX;
	res = write(fd,&char_temp,1);
       // printf("\ns2=%s\n",res_buff);
	printf("CLose...\n");
	close (fd);
	return ret_mm;
}
int base_send(int dm_node_id, char * dm_buff, int dm_num)
{
	int fd,c=0,res,ret_temp;
	struct termios newtio;
	unsigned char char_temp,sum,num_temp;
	static char res_buff[4096];
	printf("Start...\n");
	/*Žò¿ªpcµÄcom1ÍšÑ¶¶Ë¿Ú*/
	fd = open( MODEMDEVICE,O_RDWR|O_NOCTTY);
	if (fd<0) {
		perror("MODEMDEVICE");
		exit(1);
		}
	printf("Open...\n");
	/*³õÊŒ»¯ÐÂµÄnewtioœá¹¹*/
	bzero(&newtio,sizeof(newtio));
	/*ÍšÑ¶Ð­Òé8n1*/
	newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD ;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;

	newtio.c_lflag = 0;
	tcflush (fd, TCIOFLUSH);//add a o --zhao

	tcsetattr(fd, TCSANOW, &newtio);


	sum = 0;
	char_temp=DLE;
	printf("Writing.\n");
	res = write(fd,&char_temp,1);

	char_temp=STX;
	res = write(fd,&char_temp,1);

	char_temp=I_O_COM;
	sum+= char_temp;
	res = write(fd,&char_temp,1);

	char_temp=0;
	sum+= char_temp;
	res = write(fd,&char_temp,1);

	char_temp=0;
	sum+= char_temp;
	res = write(fd,&char_temp,1);

	//char_temp=(unsigned char)(dm_node_id>>8);
	char_temp=0x00;//zhao
        sum+= char_temp;
	res = write(fd,&char_temp,1);

	char_temp=(unsigned char)(dm_node_id);
	sum+= char_temp;
	res = write(fd,&char_temp,1);

	char_temp=UART_SEND;
	sum+= char_temp;
	res = write(fd,&char_temp,1);

	for(num_temp=0;num_temp<dm_num;num_temp++) {
		char_temp=*(dm_buff+num_temp);
		res= write(fd,&char_temp,1);
		sum+= char_temp;
		}
       char_temp=sum;
	res = write(fd,&char_temp,1);

	char_temp=DLE;
	res = write(fd,&char_temp,1);

	char_temp=ETX;
	res = write(fd,&char_temp,1);

       ret_temp=0;
	do{
		bzero(res_buff,sizeof(*res_buff));
		sleep(1);
		res =read(fd,res_buff,10);
		if(res==2) {
			printf("res=%d buff= %s\n",res,res_buff);

			if(res_buff[0]==DLE)	{
				switch (res_buff[1]) {
					case COM_ACCEPTED:
						ret_temp=-1;
						break;
					case COM_NO_OP:
						printf("COM_NO_OP\n");
						ret_temp=-2;
						break;
					case  RESPONSE_TIMEOUT:
						printf("RESPONSE_TIMEOU\n");
						ret_temp=-3;
						break;
					case  NETWORK_TIMEOUT:
						printf("NETWORK_TIMEOUT\n");
						ret_temp=-4;
						break;
					case  RESPONSE_ERROR:
						printf("RESPONSE_ERROR\n");
						ret_temp=-5;
						break;
					case  SERIAL_ERROR:
						printf("SERIAL_ERROR\n");
						ret_temp=-6;
						break;
					case  INVALID_LENGTH:
						printf("INVALID_LENGTH\n");
						ret_temp=-7;
						break;
					case  INVALID_DLE_SEQUENCE:
						printf("INVALID_DLE_SEQUENCE\n");
						ret_temp=-8;
						break;
					default:
						printf("ERROR\n");
						ret_temp=-9;
						break;

					}
				}

		}

		if(res==10) {

			if( (res_buff[2]&0xf0)==I_O_RES) {

				printf("APPLICATION I/O RESPONSE\n");
				ret_temp=1;
				}

			}
		}while(ret_temp==0);

	printf("CLose...\n");
	close (fd);

	return ret_temp;
}
void set_speed(int fd, int speed)
{ 
	int i; 
	int status; 
	struct termios Opt; 
	tcgetattr(fd, &Opt); 
	for ( i= 0; i < sizeof(speed_arr) / sizeof(int); i++) 
	{ 
		if (speed == name_arr[i])
		 { 
		tcflush(fd, TCIOFLUSH); 
		cfsetispeed(&Opt, speed_arr[i]); 
		cfsetospeed(&Opt, speed_arr[i]); 
		status = tcsetattr(fd, TCSANOW, &Opt); 
			if (status != 0) 
			{ 
			perror("tcsetattr fd1"); 
			return; 
			} 
		tcflush(fd,TCIOFLUSH); 
		} 
	} 
} 
/** 
*@brief ÉèÖÃŽ®¿ÚÊýŸÝÎ»£¬Í£Ö¹Î»ºÍÐ§ÑéÎ» 
*@param fd ÀàÐÍ int Žò¿ªµÄŽ®¿ÚÎÄŒþŸä±ú 
*@param databits ÀàÐÍ int ÊýŸÝÎ» È¡Öµ Îª 7 »òÕß8 
*@param stopbits ÀàÐÍ int Í£Ö¹Î» È¡ÖµÎª 1 »òÕß2 
*@param parity ÀàÐÍ int Ð§ÑéÀàÐÍ È¡ÖµÎªN,E,O,,S 
*/ 
int set_Parity(int fd,int databits,int stopbits,int parity) 
{ 
	struct termios options; 
	if ( tcgetattr( fd,&options) != 0) 
	{ 
	perror("SetupSerial 1"); 
	return(FALSE); 
	} 
	options.c_cflag &= ~CSIZE; 
	switch (databits) /*ÉèÖÃÊýŸÝÎ»Êý*/ 
	{ 
	case 7: 
	options.c_cflag |= CS7; 
	break; 
	case 8: 
	options.c_cflag |= CS8; 
	break; 
	default: 
	fprintf(stderr,"Unsupported data sizen"); return (FALSE); 
	} 
	switch (parity) 
	{ 
	case 'n': 
	case 'N': 
	options.c_cflag &= ~PARENB; /* Clear parity enable */ 
	options.c_iflag &= ~INPCK; /* Enable parity checking */ 
	break; 
	case 'o': 
	case 'O': 
	options.c_cflag |= (PARODD | PARENB); /* ÉèÖÃÎªÆæÐ§Ñé*/ 
	options.c_iflag |= INPCK; /* Disnable parity checking */ 
	break; 
	case 'e': 
	case 'E': 
	options.c_cflag |= PARENB; /* Enable parity */ 
	options.c_cflag &= ~PARODD; /* ×ª»»ÎªÅŒÐ§Ñé*/ 
	options.c_iflag |= INPCK; /* Disnable parity checking */ 
	break; 
	case 'S': 
	case 's': /*as no parity*/ 
	options.c_cflag &= ~PARENB; 
	options.c_cflag &= ~CSTOPB;break; 
	default: 
	fprintf(stderr,"Unsupported parityn"); 
	return (FALSE); 
	} 
/* ÉèÖÃÍ£Ö¹Î»*/ 
	switch (stopbits) 
	{ 
	case 1: 
	options.c_cflag &= ~CSTOPB; 
	break; 
	case 2: 
	options.c_cflag |= CSTOPB; 
	break; 
	default: 
	fprintf(stderr,"Unsupported stop bitsn"); 
	return (FALSE); 
	} 
/* Set input parity option */ 
	if (parity != 'N')
	options.c_iflag |= INPCK; 
	tcflush(fd,TCIFLUSH); 
	options.c_cc[VTIME] = 0; /* ÉèÖÃ³¬Ê±5 seconds*/ 
	options.c_cc[VMIN] = 0; /* Update the options and do it NOW */ 
//////////////////////////////
       //options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); /*Input*/ 
       //options.c_oflag &= ~OPOST; /*Output*/ 

	if (tcsetattr(fd,TCSANOW,&options) != 0) 
	{ 
	perror("SetupSerial 3"); 
	return (FALSE); 
	} 
	return (TRUE); 
} 
int OpenDev(char *Dev) 
{ 
	int fd = open( Dev, O_RDWR ); 
	//| O_NOCTTY | O_NDELAY 
	if (-1 == fd) 
	{ 
	perror("Can't Open Serial Port"); 
	return -1; 
	} 
	else 
	return fd; 
} 
int uart_send(int fd,char * buf)
{

	   int nwrite;
	   char buff[4096]="\0"; 
       strcat(buff,buf);
       printf("send start........\n");  
       printf("fd==%d\n",fd);
		if((nwrite = write(fd, buff, strlen(buff)))>0) 
		{ 
			printf("nwrite %d\n",nwrite); 
			buf[nwrite+1] = ' '; 
			printf( "write=%s\n", buff); 		
   		}
	return nwrite; 
}
int uart_res(int fd )
{
  
	//int fd; 
	int nread; 
	//int nwrite;
	//char res_buff[4096];
    bzero(res_buff,sizeof(res_buff)); 
    //char buf[4096];
    char *aa;
   // sprintf(buf,"00000000");
	sprintf(res_buff,"00000000");
    aa=res_buff+8;
	//char *dev = "/dev/ttyS1";
	//fd = OpenDev(dev); 
	//set_speed(fd,9600); 
	//if (set_Parity(fd,8,1,'N' )== FALSE)
 	//{ 
	//printf("Set Parity Errorn"); 
	//exit (0); 
	//} 

        printf("read start........\n");  
		if((nread = read(fd, aa, 512))>0) 
		{ 
			printf("%d\n", nread); 
           // buf[nread+1] = '\0';
           // strcat(buf,res_buff);
			//res_buff=buf;
			printf( "read=%s\n", res_buff); 
			//
	     } 
	//close(fd);
return nread; 
}

