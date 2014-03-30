#include<stdio.h>
#include<stdlib.h>
#include"struct.h"
#include<string.h>
#include<mysql/mysql.h>





void bill_insert(struct struct_bill *);
void bill_delete(struct struct_bill *);
char*bill_select(struct struct_bill *);
void bill_update(struct struct_bill *);
char*bill_select_all();
char * billSelectAll();


void billInsert(struct struct_bill *);
void billDelete(struct struct_bill *);
char*billSelect(struct struct_bill *);
void billUpdate(struct struct_bill *);

char * staff_getBill(char *,char *);
char * staffGetBill(char *,char *);

char * dish_getDished(char *,char *);
char * dishGetDished(char *,char *);

char * money_getBill(char *,char *);
char * moneyGetBill(char *,char *);

char * money_month();




void staff_insert(struct struct_staff *);
void staff_delete(struct struct_staff *);
char*staff_select(struct struct_staff *);
void staff_update(struct struct_staff *);


void staffInsert(struct struct_staff *);
void staffDelete(struct struct_staff *);
char*staffSelect(struct struct_staff *);
void staffUpdate(struct struct_staff *);


void dishes_insert(struct struct_dishes *);
void dishes_delete(struct struct_dishes *);
char*dishes_select(struct struct_dishes *);
void dishes_update(struct struct_dishes *);


void dishesInsert(struct struct_dishes *);
void dishesDelete(struct struct_dishes *);
char*dishesSelect(struct struct_dishes *);
void dishesUpdate(struct struct_dishes *);


void dished_insert(struct struct_dished *);
void dished_delete(struct struct_dished *);
char*dished_select(struct struct_dished *);
void dished_update(struct struct_dished *);


void dishedInsert(struct struct_dished *);
void dishedDelete(struct struct_dished *);
char*dishedSelect(struct struct_dished *);
void dishedUpdate(struct struct_dished *);




void tableinfo_insert(struct struct_tableinfo *);
void tableinfo_delete(struct struct_tableinfo *);
char*tableinfo_select(struct struct_tableinfo *);
void tableinfo_update(struct struct_tableinfo *);



void tableinfoInsert(struct struct_tableinfo *);
void tableinfoDelete(struct struct_tableinfo *);
char*tableinfoSelect(struct struct_tableinfo *);
void tableinfoUpdate(struct struct_tableinfo *);



