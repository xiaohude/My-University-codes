#include "edit.h"

static MYSQL *conn_ptr_bill;
static MYSQL_RES *res_ptr_bill;
static MYSQL_ROW sqlrow_bill;

void display_row_bill(MYSQL *);
char*string_row_bill(MYSQL *);
int db_connect_bill();
void db_close_bill();

char * sumDishedMoney(struct struct_bill *billSTR)
{
	printf("sumDishedMoney\n");
	int res;
    char str[4096];
	char buf[4096]="\0";
	char * buff;
	printf("bill_number ===%s\n",billSTR->bill_number);
    sprintf(str,"select sum(dish_price) from dishes where dish_number in (select dish_number from dished where bill_number='%s')",billSTR->bill_number);
    res=mysql_query(conn_ptr_bill,str);
	printf("sql string =====%s\n",str);
	//res=mysql_query(conn_ptr_dished,"select * from dished");
	if(!res) 
	{
		res_ptr_bill=mysql_store_result(conn_ptr_bill);
		if(res_ptr_bill)
		{
			printf("\nselect %lu rows!!!!\n\n",(unsigned long)mysql_num_rows(res_ptr_bill));
			while((sqlrow_bill=mysql_fetch_row(res_ptr_bill)))
		    {
				printf("Fetcher data...\n");
				//display_row_dished(conn_ptr_bill);  
				buff=string_row_bill(conn_ptr_bill); 
				printf("dishGetDished~~~~%s\n",buff);
				strcat(buf,buff); 
				//printf("dishedSelect000~~~~%s\n",buf);      
	   		 }
			mysql_free_result(res_ptr_bill);
		}
		buff=buf;
		printf("sumDishedMoney~~~~~%s\n",buff);
		return buff;
	} 
    else  
	{
		printf("sumDishedMoney failed!\n"); 
		return NULL;
	}
}

void updateAmountMoney(struct struct_bill *billSTR)
{
	double amount;
	char buf[4096]="\0";
	char * buff;
	
	
	if(db_connect_bill())
	{
		printf("db_connect_bill~~~~~\n");
		
		
		buff=sumDishedMoney(billSTR);
		strcat(buf,buff);
		buff=buf;
		printf("amount string ===%s\n",buff);
		amount=strtod(buf,&buff);
		printf("amount double ===%f\n",amount);
	


		int res;
    	char str[4096];
    	sprintf(str,"update bill set bill_amountMoney='%f' where bill_number='%s'",amount,billSTR->bill_number);
    	res=mysql_query(conn_ptr_bill,str);
 	    if(!res) 
			printf("update %lu rows!!!!\n\n",(unsigned long)mysql_affected_rows(conn_ptr_bill)); 
   	 	else  
			printf("Update staff failed!\n"); 






		db_close_bill();
	}
	else 
		printf("insert failllllllll\n");
}


char * money_month()
{
	char buf[4096]="\0";
	char * buff;
	if(db_connect_bill())
	{
		printf("db_connect_bill_month~~~~~\n");
		buff=moneyGetBill("2013-01","2013-02");
		strcat(buf,buff);
		buff=moneyGetBill("2013-02","2013-03");
		strcat(buf,buff);
		buff=moneyGetBill("2013-03","2013-04");
		strcat(buf,buff);
		buff=moneyGetBill("2013-04","2013-05");
		strcat(buf,buff);
		buff=moneyGetBill("2013-05","2013-06");
		strcat(buf,buff);
		buff=moneyGetBill("2013-06","2013-07");
		strcat(buf,buff);
		buff=moneyGetBill("2013-07","2013-08");
		strcat(buf,buff);
		buff=moneyGetBill("2013-08","2013-09");
		strcat(buf,buff);
		buff=moneyGetBill("2013-09","2013-10");
		strcat(buf,buff);
		buff=moneyGetBill("2013-10","2013-11");
		strcat(buf,buff);
		buff=moneyGetBill("2013-11","2013-12");
		strcat(buf,buff);
		buff=moneyGetBill("2013-12","2013-01");
		strcat(buf,buff);
		buff=buf;
		db_close_bill();
	}
	else 
		printf("db_connect money_month failllllllll\n");
	return buff;
}


char * money_getBill(char *start,char *end)
{
	char buf[4096]="\0";
	char * buff;
	if(db_connect_bill())
	{
		printf("db_connect_bill~~~~~\n");
		buff=moneyGetBill(start,end);
		strcat(buf,buff);
		buff=buf;
		db_close_bill();
	}
	else 
		printf("db_connect money failllllllll\n");
	return buff;
}
char * moneyGetBill(char *start,char *end)
{

	int res;
    char str[4096];
	char buf[4096]="\0";
	char * buff;
    sprintf(str,"select sum(bill_amountMoney) from bill where bill_datetime between '%s' and '%s'",start,end);
	printf("sql----str=====%s\n",str);
    res=mysql_query(conn_ptr_bill,str);
	//res=mysql_query(conn_ptr_bill,"select sum(bill_amountMoney) from bill where bill_datetime between '2013-07' and '2013-08'");
	printf("res______%d\n",res);
	if(!res) 
	{
		res_ptr_bill=mysql_store_result(conn_ptr_bill);
		if(res_ptr_bill)
		{
			printf("money_select %lu rows!!!!\n\n",(unsigned long)mysql_num_rows(res_ptr_bill));
			while((sqlrow_bill=mysql_fetch_row(res_ptr_bill)))
		    {
				printf("Fetcher data...\n");
				display_row_bill(conn_ptr_bill);  
				buff=string_row_bill(conn_ptr_bill); 
				printf("bill Sum=====~~~~%s\n",buff);
				strcat(buf,buff);     
	   		 }
			mysql_free_result(res_ptr_bill);
		}
		buff=buf;
		return buff;
	} 
    else  
	{
		printf("select bill failed!\n"); 
		return NULL;
	}
}





char * staff_getBill(char *start,char *end)
{
	char buf[4096]="\0";
	char * buff;
	if(db_connect_bill())
	{
		printf("db_connect_staff_getBill~~~~~\n");
		buff=staffGetBill(start,end);
		strcat(buf,buff);
		buff=buf;
		db_close_bill();
	}
	else 
		printf("db_connect staff_getBill failllllllll\n");
	return buff;
}
char * staffGetBill(char *start,char *end)
{
	int res;
    char str[4096];
	char buf[4096]="\0";
	char * buff;
    sprintf(str,"select staff_number,count(bill_number) from bill where bill_datetime between '%s' and '%s' group by staff_number",start,end);
	printf("sql----str=====%s\n",str);
    res=mysql_query(conn_ptr_bill,str);
	//res=mysql_query(conn_ptr_bill,"select sum(bill_amountMoney) from bill where bill_datetime between '2013-07' and '2013-08' group by staff_number");
	printf("res______%d\n",res);
	if(!res) 
	{
		res_ptr_bill=mysql_store_result(conn_ptr_bill);
		if(res_ptr_bill)
		{
			printf("\nstaffBill_select %lu rows!!!!\n\n",(unsigned long)mysql_num_rows(res_ptr_bill));
			while((sqlrow_bill=mysql_fetch_row(res_ptr_bill)))
		    {
				printf("Fetcher data...\n");
				display_row_bill(conn_ptr_bill);  
				buff=string_row_bill(conn_ptr_bill); 
				printf("bill Sum=====~~~~%s\n",buff);
				strcat(buf,buff);     
	   		 }
			mysql_free_result(res_ptr_bill);
		}
		buff=buf;
		return buff;
	} 
    else  
	{
		printf("select bill failed!\n"); 
		return NULL;
	}
}







void bill_insert(struct struct_bill *billSTR)
{
	if(db_connect_bill())
	{
		printf("db_connect_bill~~~~~\n");
		billInsert(billSTR);
		db_close_bill();
	}
	else 
		printf("insert failllllllll\n");
}
void bill_delete(struct struct_bill *billSTR)
{
	if(db_connect_bill())
	{
		printf("db_connect_bill~~~~~\n");
		billDelete(billSTR);
		db_close_bill();
	}
	else 
		printf("delete failllllllll\n");
}

char * bill_select(struct struct_bill *billSTR)
{
	char buf[4096]="\0";
	char* buff;
	if(db_connect_bill())
	{
		printf("db_connect_bill~~~~~\n");
		buff=billSelect(billSTR);
		strcat(buf,buff);
		db_close_bill();
	}
	else 
		printf("select failllllllll\n");
	buff=buf;
	printf("bill_select~~~~%s\n",buff);
	return buff;

}

char * bill_select_all()
{
	char buf[4096]="\0";
	char* buff;
	if(db_connect_bill())
	{
		printf("db_connect_bill~~~~~\n");
		buff=billSelectAll();
		strcat(buf,buff);
		db_close_bill();
	}
	else 
		printf("select failllllllll\n");
	buff=buf;
	printf("bill_select_all~~~~%s\n",buff);
	return buff;
}
void bill_update(struct struct_bill *billSTR)
{
	if(db_connect_bill())
	{
		printf("db_connect_bill~~~~~\n");
		billUpdate(billSTR);
		db_close_bill();
	}
	else 
		printf("update failllllllll\n");
}



int db_connect_bill()       //jian li shu ju ku lian jie
{   
 conn_ptr_bill=mysql_init(NULL);
    if(!conn_ptr_bill)
    {
        fprintf(stderr,"mysql_init failed!\n");
        return -1;
    }
    conn_ptr_bill=mysql_real_connect(conn_ptr_bill,"localhost","root",NULL,"bh1800",0,NULL,0);
    if(conn_ptr_bill) 
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

void db_close_bill()		
{
    mysql_close(conn_ptr_bill);
	printf("db close ~~~\n");
}



char * billSelect(struct struct_bill *billSTR)
{
	int res;
    char str[4096];
	char buf[4096]="\0";
	char * buff;
    sprintf(str,"select * from bill where bill_number='%s'",billSTR->bill_number);
    res=mysql_query(conn_ptr_bill,str);
	//res=mysql_query(conn_ptr_bill,"select * from bill");
	if(!res) 
	{
		res_ptr_bill=mysql_store_result(conn_ptr_bill);
		if(res_ptr_bill)
		{
			printf("\nselect %lu rows!!!!\n\n",(unsigned long)mysql_num_rows(res_ptr_bill));
			while((sqlrow_bill=mysql_fetch_row(res_ptr_bill)))
		    {
				printf("Fetcher data...\n");
				//display_row_bill(conn_ptr_bill);  
				buff=string_row_bill(conn_ptr_bill); 
				//printf("billSelect000~~~~%s\n",buff);
				strcat(buf,buff); 
				//printf("billSelect000~~~~%s\n",buf);      
	   		 }
			mysql_free_result(res_ptr_bill);
		}
		buff=buf;
		//printf("billSelect111~~~~%s\n",buff);
		return buff;
	} 
    else  
	{
		printf("select bill failed!\n"); 
		return NULL;
	}
}


char * billSelectAll()
{
	int res;
    //char str[4096];
	char buf[4096]="\0";
	char * buff;
    //sprintf(str,"select * from bill where bill_number='%s'",billSTR->bill_number);
    //res=mysql_query(conn_ptr_bill,str);
	res=mysql_query(conn_ptr_bill,"select * from bill");
	if(!res) 
	{
		res_ptr_bill=mysql_store_result(conn_ptr_bill);
		if(res_ptr_bill)
		{
			printf("\nselectAll %lu rows!!!!\n\n",(unsigned long)mysql_num_rows(res_ptr_bill));
			while((sqlrow_bill=mysql_fetch_row(res_ptr_bill)))
		    {
				printf("Fetcher data...\n");
				//display_row_bill(conn_ptr_bill);  
				buff=string_row_bill(conn_ptr_bill); 
				//printf("billSelect000~~~~%s\n",buff);
				strcat(buf,buff); 
				//printf("billSelect000~~~~%s\n",buf);      
	   		 }
			mysql_free_result(res_ptr_bill);
		}
		buff=buf;
		//printf("billSelect111~~~~%s\n",buff);
		return buff;
	} 
    else  
	{
		printf("select all bill  failed!\n"); 
		return NULL;
	}
}



void billInsert(struct struct_bill *billSTR)//tian jia 
{
    int res;
    char str[4096];
    sprintf(str,"INSERT INTO bill(bill_number,bill_amountMoney,bill_datetime,staff_number,table_number,bill_status)VALUES('%s',%f,'%s','%s','%s','%s')",billSTR->bill_number,billSTR->bill_amount,billSTR->bill_datetime,billSTR->staff_number,billSTR->table_number,billSTR->bill_status);
	printf("string.....%s\n",str);
	res=mysql_query(conn_ptr_bill,str);
	//res=mysql_query(conn_ptr_bill,"INSERT INTO bill(bill_number,bill_amountMoney,bill_datetime,staff_number,table_number,bill_status)VALUES('201307180011',66.660000,'2013-07-18 20:00:00','0001','2','3')");
    if(!res) 
    {
		printf("\ninsert %lu rows!!!!\n\n",(unsigned long)mysql_affected_rows(conn_ptr_bill));
    }
    else 
    { 
		printf("insert into bill failed!\n"); 
    }
}


void billDelete(struct struct_bill *billSTR)	//shan chu 
{
    int res;
    char str[4096];
    sprintf(str,"DELETE FROM bill WHERE bill_number='%s'",billSTR->bill_number);
    res=mysql_query(conn_ptr_bill,str);
    if(!res)  
		printf("\ndelete %lu rows!!!!\n\n",(unsigned long)mysql_affected_rows(conn_ptr_bill));
    else  
		printf("Delete staff failed!\n"); 	
}

void billUpdate(struct struct_bill *billSTR)//geng xin 
{
    int res;
    char str[4096];
    sprintf(str,"update bill set bill_number='%s',bill_amountMoney='%f',bill_datetime='%s',staff_number='%s',table_number='%s',bill_status='%s' where bill_number='%s'",billSTR->bill_number,billSTR->bill_amount,billSTR->bill_datetime,billSTR->staff_number,billSTR->table_number,billSTR->bill_status,billSTR->bill_number);
    res=mysql_query(conn_ptr_bill,str);
    if(!res) 
		printf("\nupdate %lu rows!!!!\n\n",(unsigned long)mysql_affected_rows(conn_ptr_bill)); 
    else  
		printf("Update staff failed!\n"); 
}



void display_row_bill(MYSQL *ptr)
{
	unsigned int field_count;
	field_count=0;
	while(field_count<mysql_field_count(ptr))
	{
		printf("%s   ",sqlrow_bill[field_count]);
		field_count++;	
	}
	printf("\n");
}
char*string_row_bill(MYSQL *ptr)
{
	char buf[4096]="\0";
	char *buff;
	unsigned int field_count;
	field_count=0;
	while(field_count<mysql_field_count(ptr))
	{
		if(sqlrow_bill[field_count]==NULL)
			return "No massage in sql!!!;";
		strcat(buf,sqlrow_bill[field_count]);
		if(field_count==(mysql_field_count(ptr)-1))
			strcat(buf,";");
		else 
			strcat(buf,"+");
		
		field_count++;	
	}
	buff=buf;
	printf("string_row_bill-----%s\n",buff);
	return buff;
	
}










