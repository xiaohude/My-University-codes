#include "edit.h"

static MYSQL *conn_ptr_dished;
static MYSQL_RES *res_ptr_dished;
static MYSQL_ROW sqlrow_dished;

void display_row_dished(MYSQL *);
char*string_row_dished(MYSQL *);
int db_connect_dished();
void db_close_dished();



char * dish_getDished(char *start,char *end)
{
	char buf[4096]="\0";
	char* buff;
	if(db_connect_dished())
	{
		printf("db_connect_dished~~~~~\n");
		buff=dishGetDished(start,end);
		strcat(buf,buff);
		db_close_dished();
	}
	else 
		printf("select failllllllll\n");
	buff=buf;
	printf("dished_select~~~~%s\n",buff);
	return buff;
}
char * dishGetDished(char *start,char *end)
{
	int res;
    char str[4096];
	char buf[4096]="\0";
	char * buff;
    sprintf(str,"select dish_number,sum(dished_count) from dished where bill_number in (select bill_number from bill where bill_datetime between '%s' and '%s') group by dish_number",start,end);
    res=mysql_query(conn_ptr_dished,str);
	//res=mysql_query(conn_ptr_dished,"select * from dished");
	if(!res) 
	{
		res_ptr_dished=mysql_store_result(conn_ptr_dished);
		if(res_ptr_dished)
		{
			printf("\nselect %lu rows!!!\n\n",(unsigned long)mysql_num_rows(res_ptr_dished));
			while((sqlrow_dished=mysql_fetch_row(res_ptr_dished)))
		    {
				printf("Fetcher data...\n");
				//display_row_dished(conn_ptr_dished);  
				buff=string_row_dished(conn_ptr_dished); 
				printf("dishGetDished~~~~%s\n",buff);
				strcat(buf,buff); 
				//printf("dishedSelect000~~~~%s\n",buf);      
	   		 }
			mysql_free_result(res_ptr_dished);
		}
		buff=buf;
		printf("dishGetDished~~~~~%s\n",buff);
		return buff;
	} 
    else  
	{
		printf("select dished failed!\n"); 
		return NULL;
	}
}



void dished_insert(struct struct_dished *dishedSTR)
{
	if(db_connect_dished())
	{
		printf("db_connect_dished~~~~~\n");
		dishedInsert(dishedSTR);
		db_close_dished();
	}
	else 
		printf("insert failllllllll\n");
}
void dished_delete(struct struct_dished *dishedSTR)
{
	if(db_connect_dished())
	{
		printf("db_connect_dished~~~~~\n");
		dishedDelete(dishedSTR);
		db_close_dished();
	}
	else 
		printf("delete failllllllll\n");
}

char * dished_select(struct struct_dished *dishedSTR)
{
	char buf[4096]="\0";
	char* buff;
	if(db_connect_dished())
	{
		printf("db_connect_dished~~~~~\n");
		buff=dishedSelect(dishedSTR);
		strcat(buf,buff);
		db_close_dished();
	}
	else 
		printf("select failllllllll\n");
	buff=buf;
	printf("dished_select~~~~%s\n",buff);
	return buff;

}
void dished_update(struct struct_dished *dishedSTR)
{
	if(db_connect_dished())
	{
		printf("db_connect_dished~~~~~\n");
		dishedUpdate(dishedSTR);
		printf("db_close_dished   begin~~~\n");
		db_close_dished();
		printf("dished____update____over!!!\n");
	}
	else 
		printf("update failllllllll\n");
}



int db_connect_dished()       //jian li shu ju ku lian jie
{   
 conn_ptr_dished=mysql_init(NULL);
    if(!conn_ptr_dished)
    {
        fprintf(stderr,"mysql_init failed!\n");
        return -1;
    }
    conn_ptr_dished=mysql_real_connect(conn_ptr_dished,"localhost","root",NULL,"bh1800",0,NULL,0);
    if(conn_ptr_dished) 
    {  
        printf("Connection succeed!\n");
	return 1;
    }
    else
    {
        printf("Connection failed!\n");
        return -2;
    }
}

void db_close_dished()		
{
    mysql_close(conn_ptr_dished);
	printf("db close ~~~\n");
}
char * dishedSelect(struct struct_dished *dishedSTR)
{
	int res;
    char str[4096];
	char buf[4096]="\0";
	char * buff;
    sprintf(str,"select * from dished where dish_number='%s'",dishedSTR->dish_number);
    res=mysql_query(conn_ptr_dished,str);
	//res=mysql_query(conn_ptr_dished,"select * from dished");
	if(!res) 
	{
		res_ptr_dished=mysql_store_result(conn_ptr_dished);
		if(res_ptr_dished)
		{
			printf("\nselect %lu rows!!!\n\n",(unsigned long)mysql_num_rows(res_ptr_dished));
			while((sqlrow_dished=mysql_fetch_row(res_ptr_dished)))
		    {
				printf("Fetcher data...\n");
				//display_row_dished(conn_ptr_dished);  
				buff=string_row_dished(conn_ptr_dished); 
				//printf("dishedSelect000~~~~%s\n",buff);
				strcat(buf,buff); 
				//printf("dishedSelect000~~~~%s\n",buf);      
	   		 }
			mysql_free_result(res_ptr_dished);
		}
		buff=buf;
		//printf("dishedSelect111~~~~%s\n",buff);
		return buff;
	} 
    else  
	{
		printf("select dished failed!\n"); 
		return NULL;
	}
}
void dishedInsert(struct struct_dished *dishedSTR)//tian jia 
{
    int res;
    char str[4096];
    sprintf(str,"INSERT INTO dished(dish_number,bill_number,dished_count)VALUES('%s','%s',%d)",dishedSTR->dish_number,dishedSTR->bill_number,dishedSTR->dished_count);
	printf("string.....%s\n",str);
	res=mysql_query(conn_ptr_dished,str);
	//res=mysql_query(conn_ptr_dished,"INSERT INTO dished(dished_number,dished_name,dished_login_pass,dished_sex,dished_native,dished_address,dished_ID_card_Number,dished_level,dished_age)VALUES('0004','xh','123456','f','beijing','xisanqi','1304251992','3','22')");	
    if(!res) 
    {
		printf("\ninsert %lu rows!!!\n\n",(unsigned long)mysql_affected_rows(conn_ptr_dished));
    }
    else 
    { 
		printf("insert into dished failed!\n"); 
    }
}


void dishedDelete(struct struct_dished *dishedSTR)	//shan chu 
{
    int res;
    char str[4096];
    sprintf(str,"DELETE FROM dished WHERE dish_number='%s'",dishedSTR->dish_number);
    res=mysql_query(conn_ptr_dished,str);
    if(!res) 
		printf("\ndelete %lu rows!!!\n\n",(unsigned long)mysql_affected_rows(conn_ptr_dished));
    else  
		printf("Delete dished failed!\n"); 	
}

void dishedUpdate(struct struct_dished *dishedSTR)//geng xin 
{
    int res;
    char str[4096];
	
    sprintf(str,"update dished set dish_number='%s',bill_number='%s',dished_count=%d where dish_number='%s'",dishedSTR->dish_number,dishedSTR->bill_number,dishedSTR->dished_count,dishedSTR->dish_number);
	printf("string.....%s\n",str);
    res=mysql_query(conn_ptr_dished,str);
    if(!res) 
		printf("\nupdate %lu rows!!!\n\n",(unsigned long)mysql_affected_rows(conn_ptr_dished)); 
    else  
		printf("Update dished failed!\n"); 
	printf("dishedUpdate___over!!!\n");
}



void display_row_dished(MYSQL *ptr)
{
	unsigned int field_count;
	field_count=0;
	while(field_count<mysql_field_count(ptr))
	{
		printf("%s   ",sqlrow_dished[field_count]);
		field_count++;	
	}
	printf("\n");
}
char*string_row_dished(MYSQL *ptr)
{
	char buf[4096]="\0";
	char *buff;
	unsigned int field_count;
	field_count=0;
	while(field_count<mysql_field_count(ptr))
	{
		if(sqlrow_dished[field_count]==NULL)
			return "No massage in sql!!!;";
		strcat(buf,sqlrow_dished[field_count]);
		if(field_count==(mysql_field_count(ptr)-1))
			strcat(buf,";");
		else 
			strcat(buf,"+");
		
		field_count++;	
	}
	buff=buf;
	printf("string-----%s\n",buff);
	return buff;
	
}











