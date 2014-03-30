#ifndef _SQL_H
#include "edit.h"
#include <strings.h>
#include <pthread.h>

static char ccc[10]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
static char num[10]={'0','1','2','3','4','5','6','7','8','9'};
static char send_buf[200];
static char ok_buff2[200];
static char table_buff[200];
static char bill_buff[200];
//static char staff_buff[200];


struct struct_tableinfo tableinfo;
struct struct_dished dished;
struct struct_dishes dishes;
struct struct_bill bill;
struct struct_staff staff;

void clear_ok_buff();
void send_buff(int ,char*,int ,char *);
void division_buff(char *res_buff);


//static struct struct_bill *bill;
static struct struct_bill bi;
//struct struct_bill *bil=(void *)malloc(sizeof(struct struct_bill));
static struct struct_bill *bil =&bi;
 


char * structTOstring_bill(struct struct_bill *);

struct struct_bill * stringTOstruct_bill(char *);

//////////////////////////


char * structTOstring_staff (struct struct_staff *);


struct struct_staff * stringTOstruct_staff(char *);


////////////////////////


char * structTOstring_dishes(struct struct_dishes * );

struct struct_dishes * stringTOstruct_dishes(char *);

///////////////////////

char * structTOstring_dished(struct struct_dished *);


struct struct_dished * stringTOstruct_dished(char *);

///////////////
char * structTOstring_tableinfo(struct struct_tableinfo *);

struct struct_tableinfo * stringTOstruct_tableinfo(char *);

void bill_add_pth(char *);
//void bill_delete(char *);
//void bill_find(struct struct_bill *);
void bill_find_pth(char *);
void bill_find_all();


//void bill_change(char *);
//void bill_amount(struct struct_bill *);
void staff_add_pth(char *staff);
void staff_delete_pth(char *staff);
void staff_find_pth(char *staff);
void staff_change_pth(char *staff);

//void table_add_pth(char *);
//void table_delete_pth(char *);
void table_check_pth(char *);
void table_new_pth(char *);
//void table_trattic_pth(char *);

void dishes_add_pth(char *);
void dishes_delete_pth(char *);
void dishes_find_pth(char *);
void dishes_change_pth(char *);

void dished_add_pth(char *);

void manage_dishes(char *);
void manage_staff(char *);
void manage_money(char*);
void month_bill(char *);


double char_change_double(char *);
char *double_change_char(double b);

#endif
