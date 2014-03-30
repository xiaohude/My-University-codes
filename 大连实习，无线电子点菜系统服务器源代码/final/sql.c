#include "sql.h"
#include "base.h"
#include <stdio.h>
//#include "uart.h"
#include <string.h>

void division_buff(char *res_buff)
{
  //  printf("ss=%s",res_buff+8);
  char c='+';
  int i=12;
  int t=2;
  int j=12;
  int flag =0;
  while(c!=';')
  {
    
    if(c=='#')
    {
       table_buff[j]=';';
        t--;
	j=12;
        flag= 1 ;
    }
    if(flag==0)
   {
    switch(t)
     {
	case 2: table_buff[j]=c; break;
	case 1: bill_buff[j] =c; break;
      }
      j++;
   }
    flag=0;
     i++;
    
     c=res_buff[i];
  }
bill_buff[j]=';';
//strcat(table_buff,";");
//strcat(bill_buff,";");
printf("table=%s\n",table_buff+12);
printf("bill=%s\n",bill_buff+12);
}

void send_buff(int id,char *ag,int n,char *fla)
{




    int fd;
    char *dev = "/dev/ttyS1";
	fd = OpenDev(dev); 
	set_speed(fd,9600); 
	if (set_Parity(fd,8,1,'N' )== -1)
 	{ 
	printf("Set Parity Errorn"); 
	exit (0); 
	} 
	char buf[4096]="\0";
    char flag[4096]="\0";
    strcat(flag,fla);
    printf("flag==%s\n",flag);
	strcat(ag,"&");
	strcat(buf,ag);
	ag=buf;
	printf("ag=%s\n",ag);
	int t=0;
	char c='1';
	int j=0;
    int res;
    int i;
	c=ag[j];
  

/*  

	char buff[4096]="\0";
	int jj;
	int ii;
	char fh=';';
	printf("buf======%s,,flag=====%s\n",buf,flag);
	for(jj=0;'&'!=buf[jj]&&jj<20;jj++)
	{
		for(ii=0;';'!=buff[ii]Z;ii++,jj++)
		{
			buff[ii]=buf[jj];
			printf("~~~~~buff[%d]=========%c\n",ii,buff[ii]);
		}
		printf("~~~~~jj====%d\n",jj);
		strcat(flag,buff);
		printf("for  jj  flag===%s\n",flag);
		uart_send(fd,flag);
		flag[5]='\0';
	}


*/
 			
	while('&'!=c)
	{
         while(';'!=c)
		{
			send_buf[t]=c;
        	t++;
  			j++;
			c=ag[j];
		}
        send_buf[t]=c;
		res=-1;
		  i=0;
		//int flag_break=0;
    	do
		{
      		
			printf("in  send_buff    buff====%s\n",send_buf);
			if(i==0)
			strcat(flag,send_buf);
			
			printf("in  send_buff    flag====%s\n",flag);
            res = uart_send(fd,flag);
      		sleep(3);
      		if(i == 5)
      		exit(0);//
			 i++;
      		
     	}while(res<0);
		t=0;
        j++;
        c=ag[j];
        bzero(send_buf,sizeof(send_buf));
  		//bzero(flag,sizeof(flag));
		sprintf(flag,"\0");
		strcat(flag,fla);
	}	




    close(fd);
}
/*

void send_buff(int id,char *ag,int n)
{
      printf("id=%d,  cc=%s,  n=%d",id,ag,n);
     int res=0;
     int i=0; 
    do{
      i++;
      res = base_send(id,ag,n);
      sleep(3);
      //printf("res=%d\n",res);
      if(i==5)
      break;
	  }while(res!=1);
}*/

void clear_ok_buff(char *res_buff)
{
  int i;
  for(i=0;i<70;i++)
   res_buff[i]='\0';
}

void bill_add_pth(char *buff)
{

  struct struct_bill *bill;
  bill = stringTOstruct_bill(buff);
// printf("buff_num=%s",bill->bill_number);
 //printf("ccc=%s\n" ,bill->table_number);
 //printf("ddd=%s\n" ,bill->bill_status);
  //bill_add();
    bill_insert(bill);

}
void bill_find_pth(char *buff)
{

   //char flag[5]="1+bq+";
   struct struct_bill *bill;
   int id;   
   printf("bb=%s\n",buff+8);
   char buf[4096]="\0";
   id=buff[8]-'0';
   
   bill = stringTOstruct_bill(buff);
   
  buff=bill_select(bill);
  strcat(buf,buff);
  buff=buf;
  printf("before  send_buff    buff====%s\n",buff);
  char flag[6]="1+bq+\0";
  send_buff(id,buff,strlen(buff),flag);
	//return ;
}

void bill_find_all(char *buff)
{
   int id;   
  // printf("bb=%s\n",buff+8);
   char buf[4096]="\0";
   id=buff[8]-'0';
   buff=bill_select_all();
   strcat(buf,buff);
  buff=buf;
  printf("before  send_buff    buff====%s\n",buff);
  char flag[6]="1+ba+\0";
  send_buff(id,buff,strlen(buff),flag);
   
}

void staff_add_pth(char *buff)
{
  struct struct_staff *staff;
  staff = stringTOstruct_staff(buff);
  staff_insert(staff);
}
void staff_delete_pth(char *buff)
{
 struct struct_staff *staff;
  staff = stringTOstruct_staff(buff);
  staff_delete(staff);
}
void staff_find_pth(char *buff)
{
    int id;
   char buf[4096]="\0";
   id=buff[8]-'0';
  struct struct_staff *staff;
  staff = stringTOstruct_staff(buff);
  buff=staff_select(staff);
  strcat(buf,buff);
  buff=buf;
  printf("staff_find_pth staff.number=%s\n",staff->number);
  //send_buff(id,buff,strlen(buff));
  char flag[6]="1+sl+\0";
  send_buff(id,buff,strlen(buff),flag);
  //return ;
}
void staff_change_pth(char *buff)
{
 struct struct_staff *staff;
  staff = stringTOstruct_staff(buff);
  staff_update(staff);
}




void table_new_pth(char *buff)
{
 
  division_buff(buff);
  struct struct_tableinfo* table;
  struct struct_bill* bill;
  table = stringTOstruct_tableinfo(table_buff);
  bill =  stringTOstruct_bill(bill_buff);
  tableinfo_update(table);
  bill_insert(bill);

}


void table_check_pth(char *buff)
{
  int id;
  char buf[4096]="\0";
  id=buff[8]-'0';

   division_buff(buff);

  struct struct_tableinfo * table;
  struct struct_bill* bill;
  // printf("table2=%s\n",table_buff+12);
  table = stringTOstruct_tableinfo(table_buff);
  bill =  stringTOstruct_bill(bill_buff);
 // printf("table_number=%s\n",table->table_number);
 // printf("bill_number=%s\n",bill->bill_number);
   //tableinfo_insert
  buff=bill_select(bill);
  strcat(buf,buff);
  buff=buf;
  //printf("bb=%s\n",bill->bill_number);
 // send_buff(id,buff,strlen(buff));
  char flag[6]="1+tc+\0";
  send_buff(id,buff,strlen(buff),flag);
}






void dishes_add_pth(char *buff)
{
  struct struct_dishes * dishes;
  dishes = stringTOstruct_dishes(buff);
  dishes_insert(dishes);
  
}
void dishes_delete_pth(char *buff)
{
     struct struct_dishes * dishes;
  dishes = stringTOstruct_dishes(buff);
  dishes_delete(dishes);
}
//void dishes_find_pth(char *);
void dishes_change_pth(char *buff)
{
 // int id;
  //char buf[4096]="\0";
 // id=buff[8]-'0';
  struct struct_dishes * dishes;
  dishes = stringTOstruct_dishes(buff);
  dishes_update(dishes);
//  strcat(buf,buff);
//  buff=buf;
  // printf("bb=%s\n",bill->bill_number);
  //send_buff(id,buff,strlen(buff)); 
  //char flag[6]="1+du+";
 // send_buff(id,buff,strlen(buff),flag);  
}



void dished_add_pth(char *buff)
{

  struct struct_dished * dished;
  dished = stringTOstruct_dished(buff);
  dished_insert(dished);
   
}

void manage_dishes(char *buff)
{
  int id;
  char buf[4096]="\0";
  id=buff[8]-'0';
  struct struct_dished * dished;
  dished = stringTOstruct_dished(buff);
  buff=dish_getDished(dished->dish_number,dished->bill_number);
  strcat(buf,buff);
  buff=buf;
  // printf("bb=%s\n",bill->bill_number);
  //send_buff(id,buff,strlen(buff)); 
  char flag[6]="1+Td+\0";
   
  send_buff(id,buff,strlen(buff),flag);
  
}

void manage_staff(char *buff)
{
  int id;
  char buf[4096]="\0";
  id=buff[8]-'0';
  struct struct_dished * dished;
  dished = stringTOstruct_dished(buff);
  buff=staff_getBill(dished->dish_number,dished->bill_number);
  strcat(buf,buff);
  buff=buf;
  // printf("bb=%s\n",bill->bill_number);
  //send_buff(id,buff,strlen(buff)); 
  char flag[6]="1+Ts+\0";
	printf("init_flag==%s\n",flag);
  send_buff(id,buff,strlen(buff),flag);
}
void manage_money(char*buff)
{
    int id;
  char buf[4096]="\0";
  id=buff[8]-'0';
  struct struct_dished * dished;
  dished = stringTOstruct_dished(buff);
  buff=money_getBill(dished->dish_number,dished->bill_number);
  strcat(buf,buff);
  buff=buf;
  
  // printf("bb=%s\n",bill->bill_number);
  //send_buff(id,buff,strlen(buff));
  char flag[6]="1+Tm+\0";
  send_buff(id,buff,strlen(buff),flag);
}
/*void month_bill(char *buff)
{
  int id;
  char buf[4096]="\0";
  id=buff[8]-'0';
  //struct struct_dished * dished;
  buff=manage_month();
  strcat(buf,buff);
  buff=buf;
  char flag[6]="1+Tm+\0";
  send_buff(id,buff,strlen(buff),flag);
  
}
*/

char * structTOstring_bill(struct struct_bill *a)
{	
  printf("b=%s\n",a->bill_number);
  //printf("a=%d\n",sizeof(*a));
  int i=0;
  for(i=0;i<70;i++)
   ok_buff2[i]='\0';
  int z=6;
  char *a_amount;
  ok_buff2[0]='1';
  ok_buff2[1]='+';
  ok_buff2[2]='b';
  ok_buff2[3]='6';
  ok_buff2[4]='+';
  int j=0;
  int t=5;
  while(z)
   {
   if(z==5)
     {
      a_amount=double_change_char(a->bill_amount); 
     }
    switch(z)
    {
      case 6 : strcat(ok_buff2,a->bill_number);strcat(ok_buff2,"+");break;
      case 5 : strcat(ok_buff2,a_amount); strcat(ok_buff2,"+");  break;
      case 4 : strcat(ok_buff2,a->bill_datetime);strcat(ok_buff2,"+");break;
      case 3 : strcat(ok_buff2,a->staff_number); strcat(ok_buff2,"+");break;
      case 2 : strcat(ok_buff2,a->table_number); strcat(ok_buff2,"+"); break;
      case 1 : strcat(ok_buff2,a->bill_status); strcat(ok_buff2,"+"); break;
    }
   z--;
   }
 // printf("%s\n",ok_buff2);
 /* while(z)
  {  
     if(z==5)
     {
      a_amount=double_change_char(a->bill_amount); 
     }
    switch(z)oid *)ok_b
      {
     case 6 : sprintf(ok_buff2,"+%s",a->bill_number); break;
      case 5 : sprintf(ok_buff2,"+%s",a_amount);   break;
      case 4 : sprintf(ok_buff2,"+%s",a->bill_datetime); break;
      case 3 : sprintf(ok_buff2,"+%s",a->staff_number);  break;
      case 2 : sprintf(ok_buff2,"+%s",a->table_number);  break;
      case 1 : sprintf(ok_buff2,"+%s",a->bill_status);   break;
      case 6 : { 
                  while(a->bill_number[j])
                 {
                    // printf("%s\n",ok_buff2);  
                   ok_buff2[t]=a->bill_number[j];
                   t++;
                   j++;
                  }
                 // printf("%s\n",ok_buff2); 
                 // 
                  ok_buff2[t]='+';
                  printf("tttt=%s\n",ok_buff2); 
                  j=0;
                   t++;
                  break;
                }
      case 5 :  while(a_amount[j])
                 {
                   ok_buff2[t]=a_amount[j];
                   t++;
                   j++;
                  }
                    
                  ok_buff2[t]='+';
                   t++;
                  j=0;
                  break;
     case 4 :  while(a->bill_datetime[j])
                 {  return &bill;
                   ok_buff2[t]=a->bill_datetime[j];
                   t++;
                   j++;
                  }
                  //t=t+1;
                  ok_buff2[t]='+';
                   t++;
                  j=0;
                  break;
     case 3 :  while(a->staff_number[j])
                 {
                   ok_buff2[t]=a->staff_number[j];
                   t++;
                   j++;
                  }
                  ok_buff2[t]='+';  return ok_buff2;
                   t++;
                  j=0;
                  break;
     case 2 :  while(a->table_number[j])
                 {
                   ok_buff2[t]=a->table_number[j];
                   t++;
                   j++;
                  }
                  ok_buff2[t]='+';
                   t++;
                  j=0;
                  break;
     case 1 :  while(a->bill_status[j])
                 {
                   ok_buff2[t]=a->bill_status[j];
                   t++;
                   j++;
                  }
                  ok_buff2[t]='+';
                   t++;
                  j=0;
                  break;
      }
    z--;
   }*/
  // printf("2=%s\n",ok_buff2); printf("sss=%s\n",a+8);
  return ok_buff2;
}

struct struct_bill * stringTOstruct_bill(char *a)
{

    int i=12;
    char c='+';
    int t=6;
    int j=0;
    int flag = 1;
    int flag_1 = 1;
    char char_double[10]="\0";
    // printf("sts=%s\n",a+8);
   ///struct struct_bill bill;
   while(c!=';')
  {
   // c=a[i];
    if(c=='+')
      {
        t--;
        j=0;
        flag_1 = 0;
      }
      if(flag_1==1)
     {
       switch(t)
       {
         case 5: bill.bill_number[j]=c; break;
         case 4: char_double[j]=c; break;
         case 3: bill.bill_datetime[j]=c; break;
         case 2: bill.staff_number[j]=c; break;
         case 1: bill.table_number[j]=c; break;
         case 0: bill.bill_status[j]=c; break;
           default : break;
         }
        if(t==3 && flag == 1)
        {
          bill.bill_amount=char_change_double(char_double);
          flag = 0;
         }
        j++;

      
       }
     flag_1 = 1;
    i++;
   c=a[i];
   }
   strcat(bill.bill_status,"\0");
  clear_ok_buff(a);
 // printf("bb=%s\n",bill.bill_number);
 // printf("cc=%s\n" ,bill.table_number);
//bill.bill_status
// printf("dd=%s\n" ,bill.bill_status);
  return &bill;
}
//////////////////////////


char * structTOstring_staff (struct struct_staff *a)
{}

struct struct_staff * stringTOstruct_staff(char *a)
{

    int i=12;
    char c='+';
    int t=9;
    int j=0;
    int flag = 1;
    int flag_1 = 1;
  //  char char_double[10];
   // struct struct_staff staff;
   while(';'!=c)
  {
   // c=a[i];
    if(c=='+')
      {
        t--;
        j=0;
        flag_1 = 0;
      }
      if(flag_1)
     {
       switch(t)
       {
 	 case 8: staff.number[j]=c; break;
 	 case 7: staff.name[j]=c; break;
 	 case 6: staff.login_pass[j]=c; break;
 	 case 5: staff.sex=c; break;	
         case 4: staff.native[j]=c; break;
         case 3: staff.address[j]=c; break;
         case 2: staff.ID_card[j]=c; break;
         case 1: staff.age[j]=c; break;
         case 0: staff.level[j]=c; break;
 	default : flag = 1; break;
         }
        j++;
       }
     flag_1 = 1;
    i++;
    c=a[i];
   }
 clear_ok_buff(a);
  return &staff;
}

////////////////////////


char * structTOstring_dishes(struct struct_dishes * a)
{}
struct struct_dishes * stringTOstruct_dishes(char *a)
{
    int i=12;
    char c='1';
    int t=5;
    int j=0;
    int flag = 0;
    int flag_1 = 1;
    char char_double[10]="\0";
    //struct struct_dishes dishes;
  //bzero(&dishes,sizeof(struct_dishes));
   while(';'!=c)
  {
    //c=a[i];
    if(c=='+')
      {
        t--;
        j=0;
        flag_1 = 0;
      }
      if(flag_1)
     {
       switch(t)
       {
 

         case 4: dishes.number[j]=c; break;
         case 3: dishes.name[j]=c; break;
         case 2: dishes.shortname[j]=c; break;
         case 1: dishes.category[j]=c; break;
         case 0: char_double[j]=c;  flag = 1;break;
         default : flag = 1; break;
         }
        if(t==0 && flag == 1)
        {
          dishes.price=char_change_double(char_double);
          flag = 0;
         }
        j++;    
       }
     flag_1 = 1;
    i++;
c=a[i];
   }
//printf("number1=%s\n",dishes.number);
//printf("number2=%s\n",dishes.name);
//printf("number3=%s\n",dishes.shortname);
//printf("number4=%s\n",dishes.category);
//printf("number5=%8.2f\n",dishes.price);
  clear_ok_buff(a);
//printf("number23=%s\n",ok_buff);

  return &dishes;
}
///////////////////////double_change_char(double b)

char * structTOstring_dished(struct struct_dished *a)
{}
struct struct_dished * stringTOstruct_dished(char *a)
{

    int i=12;
    char c='+';
    int t=3;
    int j=0;
    int flag = 0;
    int flag_1 = 1;
    char char_double[10]="\0";
  // struct struct_dished dished;
   while(';'!=c)
  {
    //c=a[i];
    if(c=='+')
      {
        t--;
        j=0;
        flag_1 = 0;
      }
      if(flag_1)
     {
       switch(t)
       {
 
         case 2: dished.dish_number[j]=c; break;
         case 1: dished.bill_number[j]=c; break;
         case 0: char_double[j]=c; flag = 1; break;
         default : flag = 1; break;
         }
         //printf("s=%s\n",char_double);
        if(t==0 && flag == 1)
        {
          double double_count=char_change_double(char_double);
          //printf("numberss=%f\n",double_count);
          dished.dished_count=(long int)double_count;
          flag = 0;
         }
        j++;
      
       }
     flag_1 = 1;
    i++;
    c=a[i];
   }
   clear_ok_buff(a);
  return &dished;
}
///////////////
char * structTOstring_tableinfo(struct struct_tableinfo *a)
{}
struct struct_tableinfo * stringTOstruct_tableinfo(char *a)
{
   // printf("tostruct=%s\n",a+12);
    int i=12;
    char c='+';
    int t=2;
    int j=0;
    int flag_1 = 1;
    //char char_double[10]=;
           //tableinfo.table_number=NULL;
          //  tableinfo.table_status=NULL;
 //struct struct_tableinfo tableinfo;
   while(';'!=c)
  {
    //c=a[i];
	//printf("c=%c\n",c);
    if(c=='+')
      {
        t--;
        j=0;
        flag_1 = 0;
      }
      if(flag_1)
     {
       switch(t)
       {
         case 1: tableinfo.table_number[j]=c; break;
         case 0: tableinfo.table_status[j]=c; break;
         default : break;
       }
        j++;
     }
     flag_1 = 1;
     i++;
     c=a[i];
   }
 //printf("number=%s\n",tableinfo.table_number);
 //printf("status=%s\n",tableinfo.table_status);
   clear_ok_buff(a);
  return &tableinfo;
}

double char_change_double(char *a)
{
 //printf("hhhhhhhh flag_1 = 1;h\n");
  double dou=0,d=0;
  int i,j=0;
  while(a[j]!='\0')
   {
   
   d=a[j]-'0';
   printf("%f\n",d);
   dou=dou+d;
   dou=dou*10;
   printf("%f\n",dou);
   j++;
   d=0;
   }
   dou=dou/1000;
  return dou;
}
char * double_change_char(double b)
{

  char c[10]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},cc;
  double bb;
  int  a;
  int j=0;
  bb=b*100;
  a=(int)bb;
  int i=0;

  do
 {
  cc=num[a%10];
  a=a/10;
  c[i]=cc;
  i++;
 }
  while (a);
  //printf("%s\n",c);
 //printf("%d\n",i);
 i--;
 for(;i>=0;i--)
   {
    //printf("%c\n",c[i]);
    ccc[j]=c[i];
    //printf("%c",ccc[j]);
    j++;
    }
 // printf("\n");
  return ccc;    
}
