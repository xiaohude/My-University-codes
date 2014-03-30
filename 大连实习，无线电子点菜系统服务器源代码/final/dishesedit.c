#include "edit.h"

static MYSQL *conn_ptr_dishes;
static MYSQL_RES *res_ptr_dishes;
static MYSQL_ROW sqlrow_dishes;

void display_row_dishes(MYSQL *);
char*string_row_dishes(MYSQL *);
int db_connect_dishes();
void db_close_dishes();


void dishes_insert(struct struct_dishes *dishesSTR)
{
	if(db_connect_dishes())
	{
		printf("db_connect_dishes~~~~~\n");
		dishesInsert(dishesSTR);
		db_close_dishes();
	}
	else 
		printf("insert failllllllll\n");
}
void dishes_delete(struct struct_dishes *dishesSTR)
{
	if(db_connect_dishes())
	{
		printf("db_connect_dishes~~~~~\n");
		dishesDelete(dishesSTR);
		db_close_dishes();
	}
	else 
		printf("delete failllllllll\n");
}

char * dishes_select(struct struct_dishes *dishesSTR)
{
	char buf[4096]="\0";
	char* buff;
	if(db_connect_dishes())
	{
		printf("db_connect_dishes~~~~~\n");
		buff=dishesSelect(dishesSTR);
		strcat(buf,buff);
		db_close_dishes();
	}
	else 
		printf("select failllllllll\n");
	buff=buf;
	printf("dishes_select~~~~%s\n",buff);
	return buff;

}
void dishes_update(struct struct_dishes *dishesSTR)
{
	if(db_connect_dishes())
	{
		printf("db_connect_dishes~~~~~\n");
		dishesUpdate(dishesSTR);
		printf("db_close_dishes   begin~~~\n");
		db_close_dishes();
		printf("dishes____update____over!!!\n");
	}
	else 
		printf("update failllllllll\n");
}



int db_connect_dishes()       //jian li shu ju ku lian jie
{   
 conn_ptr_dishes=mysql_init(NULL);
    if(!conn_ptr_dishes)
    {
        fprintf(stderr,"mysql_init failed!\n");
        return -1;
    }
    conn_ptr_dishes=mysql_real_connect(conn_ptr_dishes,"localhost","root",NULL,"bh1800",0,NULL,0);
    if(conn_ptr_dishes) 
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

void db_close_dishes()		
{
    mysql_close(conn_ptr_dishes);
	printf("db close ~~~\n");
}
char * dishesSelect(struct struct_dishes *dishesSTR)
{
	int res;
    char str[4096];
	char buf[4096]="\0";
	char * buff;
    sprintf(str,"select * from dishes where dish_number='%s'",dishesSTR->number);
    res=mysql_query(conn_ptr_dishes,str);
	//res=mysql_query(conn_ptr_dishes,"select * from dishes");
	if(!res) 
	{
		res_ptr_dishes=mysql_store_result(conn_ptr_dishes);
		if(res_ptr_dishes)
		{
			printf("\nselect %lu rows!!!\n\n",(unsigned long)mysql_num_rows(res_ptr_dishes));
			while((sqlrow_dishes=mysql_fetch_row(res_ptr_dishes)))
		    {
				printf("Fetcher data...\n");
				//display_row_dishes(conn_ptr_dishes);  
				buff=string_row_dishes(conn_ptr_dishes); 
				//printf("dishesSelect000~~~~%s\n",buff);
				strcat(buf,buff); 
				//printf("dishesSelect000~~~~%s\n",buf);      
	   		 }
			mysql_free_result(res_ptr_dishes);
		}
		buff=buf;
		//printf("dishesSelect111~~~~%s\n",buff);
		return buff;
	} 
    else  
	{
		printf("select dishes failed!\n"); 
		return NULL;
	}
}
void dishesInsert(struct struct_dishes *dishesSTR)//tian jia 
{
    int res;
    char str[4096];
    sprintf(str,"INSERT INTO dishes(dish_number,dish_name,dish_short_name,dish_category,dish_price)VALUES('%s','%s','%s','%s',%f)",dishesSTR->number,dishesSTR->name,dishesSTR->shortname,dishesSTR->category,dishesSTR->price);
	printf("string.....%s\n",str);
	res=mysql_query(conn_ptr_dishes,str);
	//res=mysql_query(conn_ptr_dishes,"INSERT INTO dishes(dishes_number,dishes_name,dishes_login_pass,dishes_sex,dishes_native,dishes_address,dishes_ID_card_Number,dishes_level,dishes_age)VALUES('0004','xh','123456','f','beijing','xisanqi','1304251992','3','22')");	
    if(!res) 
    {
		printf("\ninsert %lu rows!!!\n\n",(unsigned long)mysql_affected_rows(conn_ptr_dishes));
    }
    else 
    { 
		printf("insert into dishes failed!\n"); 
    }
}


void dishesDelete(struct struct_dishes *dishesSTR)	//shan chu 
{
    int res;
    char str[4096];
    sprintf(str,"DELETE FROM dishes WHERE dish_number='%s'",dishesSTR->number);
    res=mysql_query(conn_ptr_dishes,str);
    if(!res) 
		printf("\ndelete %lu rows!!!\n\n",(unsigned long)mysql_affected_rows(conn_ptr_dishes));
    else  
		printf("Delete dishes failed!\n"); 	
}

void dishesUpdate(struct struct_dishes *dishesSTR)//geng xin 
{
    int res;
    char str[4096];
	
    sprintf(str,"update dishes set dish_number='%s',dish_name='%s',dish_short_name='%s',dish_category='%s',dish_price=%f where dish_number='%s'",dishesSTR->number,dishesSTR->name,dishesSTR->shortname,dishesSTR->category,dishesSTR->price,dishesSTR->number);
	printf("string.....%s\n",str);
    res=mysql_query(conn_ptr_dishes,str);
    if(!res) 
		printf("\nupdate %lu rows!!!\n\n",(unsigned long)mysql_affected_rows(conn_ptr_dishes)); 
    else  
		printf("Update dishes failed!\n"); 
	printf("dishesUpdate___over!!!\n");
}



void display_row_dishes(MYSQL *ptr)
{
	unsigned int field_count;
	field_count=0;
	while(field_count<mysql_field_count(ptr))
	{
		printf("%s   ",sqlrow_dishes[field_count]);
		field_count++;	
	}
	printf("\n");
}
char*string_row_dishes(MYSQL *ptr)
{
	char buf[4096]="\0";
	char *buff;
	unsigned int field_count;
	field_count=0;
	while(field_count<mysql_field_count(ptr))
	{
		if(sqlrow_dishes[field_count]==NULL)
			return "No massage in sql!!!;";
		strcat(buf,sqlrow_dishes[field_count]);
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











