#include "edit.h"

static MYSQL *conn_ptr_staff;
static MYSQL_RES *res_ptr_staff;
static MYSQL_ROW sqlrow_staff;

void display_row_staff(MYSQL *);
char*string_row_staff(MYSQL *);
int db_connect_staff();
void db_close_staff();


void staff_insert(struct struct_staff *staffSTR)
{
	if(db_connect_staff())
	{
		printf("db_connect_staff~~~~~\n");
		staffInsert(staffSTR);
		db_close_staff();
	}
	else 
		printf("insert failllllllll\n");
}
void staff_delete(struct struct_staff *staffSTR)
{
	if(db_connect_staff())
	{
		printf("db_connect_staff~~~~~\n");
		staffDelete(staffSTR);
		db_close_staff();
	}
	else 
		printf("delete failllllllll\n");
}

char * staff_select(struct struct_staff *staffSTR)
{
	char buf[4096]="\0";
	char* buff;
	if(db_connect_staff())
	{
		printf("db_connect_staff~~~~~\n");
		buff=staffSelect(staffSTR);
		strcat(buf,buff);
		db_close_staff();
	}
	else 
		printf("select failllllllll\n");
	buff=buf;
	printf("staff_select~~~~%s\n",buff);
	return buff;

}
void staff_update(struct struct_staff *staffSTR)
{
	if(db_connect_staff())
	{
		printf("db_connect_staff~~~~~\n");
		staffUpdate(staffSTR);
		printf("db_close_staff   begin~~~\n");
		db_close_staff();
		printf("sfaff____update____over!!!\n");
	}
	else 
		printf("update failllllllll\n");
}



int db_connect_staff()       //jian li shu ju ku lian jie
{   
 conn_ptr_staff=mysql_init(NULL);
    if(!conn_ptr_staff)
    {
        fprintf(stderr,"mysql_init failed!\n");
        return -1;
    }
    conn_ptr_staff=mysql_real_connect(conn_ptr_staff,"localhost","root",NULL,"bh1800",0,NULL,0);
    if(conn_ptr_staff) 
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

void db_close_staff()		
{
    mysql_close(conn_ptr_staff);
	printf("db close ~~~\n");
}
char * staffSelect(struct struct_staff *staffSTR)
{
	int res;
    char str[4096];
	char buf[4096]="\0";
	char * buff;
    sprintf(str,"select * from staff where staff_number='%s'",staffSTR->number);
    res=mysql_query(conn_ptr_staff,str);
	//res=mysql_query(conn_ptr_staff,"select * from staff");
	if(!res) 
	{
		res_ptr_staff=mysql_store_result(conn_ptr_staff);
		if(res_ptr_staff)
		{
			printf("\nselect %lu rows!!!\n\n",(unsigned long)mysql_num_rows(res_ptr_staff));
			while((sqlrow_staff=mysql_fetch_row(res_ptr_staff)))
		    {
				printf("Fetcher data...\n");
				//display_row_staff(conn_ptr_staff);  
				buff=string_row_staff(conn_ptr_staff); 
				//printf("staffSelect000~~~~%s\n",buff);
				strcat(buf,buff); 
				//printf("staffSelect000~~~~%s\n",buf);      
	   		 }
			mysql_free_result(res_ptr_staff);
		}
		buff=buf;
		//printf("staffSelect111~~~~%s\n",buff);
		return buff;
	} 
    else  
	{
		printf("select staff failed!\n"); 
		return NULL;
	}
}
void staffInsert(struct struct_staff *staffSTR)//tian jia 
{
    int res;
    char str[4096];
    sprintf(str,"INSERT INTO staff(staff_number,staff_name,staff_login_pass,staff_sex,staff_native,staff_address,staff_ID_card_Number,staff_level,staff_age)VALUES('%s','%s','%s','%c','%s','%s','%s','%s','%s')",staffSTR->number,staffSTR->name,staffSTR->login_pass,staffSTR->sex,staffSTR->native,staffSTR->address,staffSTR->ID_card,staffSTR->age,staffSTR->level);
	printf("string.....%s\n",str);
	res=mysql_query(conn_ptr_staff,str);
	//res=mysql_query(conn_ptr_staff,"INSERT INTO staff(staff_number,staff_name,staff_login_pass,staff_sex,staff_native,staff_address,staff_ID_card_Number,staff_level,staff_age)VALUES('0004','xh','123456','f','beijing','xisanqi','1304251992','3','22')");	
    if(!res) 
    {
		printf("\ninsert %lu rows!!!\n\n",(unsigned long)mysql_affected_rows(conn_ptr_staff));
    }
    else 
    { 
		printf("insert into staff failed!\n"); 
    }
}


void staffDelete(struct struct_staff *staffSTR)	//shan chu 
{
    int res;
    char str[4096];
    sprintf(str,"DELETE FROM staff WHERE staff_number='%s'",staffSTR->number);
    res=mysql_query(conn_ptr_staff,str);
    if(!res) 
		printf("\ndelete %lu rows!!!\n\n",(unsigned long)mysql_affected_rows(conn_ptr_staff));
    else  
		printf("Delete staff failed!\n"); 	
}

void staffUpdate(struct struct_staff *staffSTR)//geng xin 
{
    int res;
    char str[4096];
	
    sprintf(str,"update staff set staff_number='%s',staff_name='%s',staff_login_pass='%s',staff_sex='%c',staff_native='%s',staff_address='%s',staff_ID_card_Number='%s',staff_level='%s',staff_age='%s' where staff_number='%s'",staffSTR->number,staffSTR->name,staffSTR->login_pass,staffSTR->sex,staffSTR->native,staffSTR->address,staffSTR->ID_card,staffSTR->age,staffSTR->level,staffSTR->number);
	printf("string.....%s\n",str);
    res=mysql_query(conn_ptr_staff,str);
    if(!res) 
		printf("\nupdate %lu rows!!!\n\n",(unsigned long)mysql_affected_rows(conn_ptr_staff)); 
    else  
		printf("Update staff failed!\n"); 
	printf("staffUpdate___over!!!\n");
}



void display_row_staff(MYSQL *ptr)
{
	unsigned int field_count;
	field_count=0;
	while(field_count<mysql_field_count(ptr))
	{
		printf("%s   ",sqlrow_staff[field_count]);
		field_count++;	
	}
	printf("\n");
}
char*string_row_staff(MYSQL *ptr)
{
	char buf[4096]="\0";
	char *buff;
	unsigned int field_count;
	field_count=0;
	while(field_count<mysql_field_count(ptr))
	{
		if(sqlrow_staff[field_count]==NULL)
			return "No massage in sql!!!;";
		strcat(buf,sqlrow_staff[field_count]);
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











