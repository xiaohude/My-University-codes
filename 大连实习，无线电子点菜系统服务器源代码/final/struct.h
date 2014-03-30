#ifndef _STRUCT_H
struct struct_bill
{
	char bill_number[32];
	double bill_amount;
	char bill_datetime[32];
	char staff_number[32];
	char table_number[10];
	char bill_status[10];
};

struct struct_staff
{
	char number[32];
	char name[32];
	char login_pass[32];
	char sex;
	char native[32];
	char address[32];
	char ID_card[32];
	char age[2];
	char level[10];
};
struct struct_dishes
{
	char number[32];
	char name[32];
	char shortname[32];
	char category[10];
	double price;
};  
struct struct_dished
{
	char dish_number[32];
	char bill_number[32];
	int dished_count;
};
struct struct_tableinfo
{
	char table_number[10];
	char table_status[10];
};
#endif
