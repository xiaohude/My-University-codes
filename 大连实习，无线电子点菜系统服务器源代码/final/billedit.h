#include<mysql/mysql.h>
#include<stdio.h>
#include<stdlib.h>
#include"struct.h"
#include<string.h>

void display_row(MYSQL *);
char*string_row(MYSQL *);
int db_connect();
void db_close();
void bill_insert(struct struct_bill *);
void bill_delete(struct struct_bill *);
char*bill_select(struct struct_bill *);
void bill_update(struct struct_bill *);


void billInsert(struct struct_bill *);
void billDelete(struct struct_bill *);
char*billSelect(struct struct_bill *);
void billUpdate(struct struct_bill *);


