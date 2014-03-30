#include "edit.h"

static MYSQL *conn_ptr_tableinfo;
static MYSQL_RES *res_ptr_tableinfo;
static MYSQL_ROW sqlrow_tableinfo;

void display_row_tableinfo(MYSQL *);
char*string_row_tableinfo(MYSQL *);
int db_connect_tableinfo();
void db_close_tableinfo();


void tableinfo_insert(struct struct_tableinfo *tableinfoSTR)
{
	if(db_connect_tableinfo())
	{
		printf("db_connect_tableinfo~~~~~\n");
		tableinfoInsert(tableinfoSTR);
		db_close_tableinfo();
	}
	else 
		printf("insert failllllllll\n");
}
void tableinfo_delete(struct struct_tableinfo *tableinfoSTR)
{
	if(db_connect_tableinfo())
	{
		printf("db_connect_tableinfo~~~~~\n");
		tableinfoDelete(tableinfoSTR);
		db_close_tableinfo();
	}
	else 
		printf("delete failllllllll\n");
}

char * tableinfo_select(struct struct_tableinfo *tableinfoSTR)
{
	char buf[4096]="\0";
	char* buff;
	if(db_connect_tableinfo())
	{
		printf("db_connect_tableinfo~~~~~\n");
		buff=tableinfoSelect(tableinfoSTR);
		strcat(buf,buff);
		db_close_tableinfo();
	}
	else 
		printf("select failllllllll\n");
	buff=buf;
	printf("tableinfo_select~~~~%s\n",buff);
	return buff;

}
void tableinfo_update(struct struct_tableinfo *tableinfoSTR)
{
	if(db_connect_tableinfo())
	{
		printf("db_connect_tableinfo~~~~~\n");
		tableinfoUpdate(tableinfoSTR);
		printf("db_close_tableinfo   begin~~~\n");
		db_close_tableinfo();
		printf("tableinfo____update____over!!!\n");
	}
	else 
		printf("update failllllllll\n");
}



int db_connect_tableinfo()       //jian li shu ju ku lian jie
{   
 conn_ptr_tableinfo=mysql_init(NULL);
    if(!conn_ptr_tableinfo)
    {
        fprintf(stderr,"mysql_init failed!\n");
        return -1;
    }
    conn_ptr_tableinfo=mysql_real_connect(conn_ptr_tableinfo,"localhost","root",NULL,"bh1800",0,NULL,0);
    if(conn_ptr_tableinfo) 
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

void db_close_tableinfo()		
{
    mysql_close(conn_ptr_tableinfo);
	printf("db close ~~~\n");
}
char * tableinfoSelect(struct struct_tableinfo *tableinfoSTR)
{
	int res;
    char str[4096];
	char buf[4096]="\0";
	char * buff;
    sprintf(str,"select * from tableinfo where table_number='%s'",tableinfoSTR->table_number);
    res=mysql_query(conn_ptr_tableinfo,str);
	//res=mysql_query(conn_ptr_tableinfo,"select * from tableinfo");
	if(!res) 
	{
		res_ptr_tableinfo=mysql_store_result(conn_ptr_tableinfo);
		if(res_ptr_tableinfo)
		{
			printf("\nselect %lu rows!!!\n\n",(unsigned long)mysql_num_rows(res_ptr_tableinfo));
			while((sqlrow_tableinfo=mysql_fetch_row(res_ptr_tableinfo)))
		    {
				printf("Fetcher data...\n");
				//display_row_tableinfo(conn_ptr_tableinfo);  
				buff=string_row_tableinfo(conn_ptr_tableinfo); 
				//printf("tableinfoSelect000~~~~%s\n",buff);
				strcat(buf,buff); 
				//printf("tableinfoSelect000~~~~%s\n",buf);      
	   		 }
			mysql_free_result(res_ptr_tableinfo);
		}
		buff=buf;
		//printf("tableinfoSelect111~~~~%s\n",buff);
		return buff;
	} 
    else  
	{
		printf("select tableinfo failed!\n"); 
		return NULL;
	}
}
void tableinfoInsert(struct struct_tableinfo *tableinfoSTR)//tian jia 
{
    int res;
    char str[4096];
    sprintf(str,"INSERT INTO tableinfo(table_number,table_status)VALUES('%s','%s')",tableinfoSTR->table_number,tableinfoSTR->table_status);
	printf("string.....%s\n",str);
	res=mysql_query(conn_ptr_tableinfo,str);
	//res=mysql_query(conn_ptr_tableinfo,"INSERT INTO tableinfo(tableinfo_number,tableinfo_name,tableinfo_login_pass,tableinfo_sex,tableinfo_native,tableinfo_address,tableinfo_ID_card_Number,tableinfo_level,tableinfo_age)VALUES('0004','xh','123456','f','beijing','xisanqi','1304251992','3','22')");	
    if(!res) 
    {
		printf("\ninsert %lu rows!!!\n\n",(unsigned long)mysql_affected_rows(conn_ptr_tableinfo));
    }
    else 
    { 
		printf("insert into tableinfo failed!\n"); 
    }
}


void tableinfoDelete(struct struct_tableinfo *tableinfoSTR)	//shan chu 
{
    int res;
    char str[4096];
    sprintf(str,"DELETE FROM tableinfo WHERE table_number='%s'",tableinfoSTR->table_number);
    res=mysql_query(conn_ptr_tableinfo,str);
    if(!res) 
		printf("\ndelete %lu rows!!!\n\n",(unsigned long)mysql_affected_rows(conn_ptr_tableinfo));
    else  
		printf("Delete tableinfo failed!\n"); 	
}

void tableinfoUpdate(struct struct_tableinfo *tableinfoSTR)//geng xin 
{
    int res;
    char str[4096];
	
    sprintf(str,"update tableinfo set table_number='%s',table_status='%s' where table_number='%s'",tableinfoSTR->table_number,tableinfoSTR->table_status,tableinfoSTR->table_number);
	printf("string.....%s\n",str);
    res=mysql_query(conn_ptr_tableinfo,str);
    if(!res) 
		printf("\nupdate %lu rows!!!\n\n",(unsigned long)mysql_affected_rows(conn_ptr_tableinfo)); 
    else  
		printf("Update tableinfo failed!\n"); 
	printf("tableinfoUpdate___over!!!\n");
}



void display_row_tableinfo(MYSQL *ptr)
{
	unsigned int field_count;
	field_count=0;
	while(field_count<mysql_field_count(ptr))
	{
		printf("%s   ",sqlrow_tableinfo[field_count]);
		field_count++;	
	}
	printf("\n");
}
char*string_row_tableinfo(MYSQL *ptr)
{
	char buf[4096]="\0";
	char *buff;
	unsigned int field_count;
	field_count=0;
	while(field_count<mysql_field_count(ptr))
	{
		if(sqlrow_tableinfo[field_count]==NULL)
			return "No massage in sql!!!;";
		strcat(buf,sqlrow_tableinfo[field_count]);
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











