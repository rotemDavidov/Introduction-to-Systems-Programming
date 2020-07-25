#define _CRT_SECURE_NO_WARNINGS
#ifndef _MATALA3
#define _MATALA3
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 15

typedef struct dish {
	char* ProductName; // name of the dish
	int price; // price of the dish
	int Quantity; 
	char Premium; // Y for yes N for not a premiun
	struct dish* next; // for the next dish
}dish;

typedef struct manager {
	dish* head;
    dish* tail;
	int size;// how many dishes there is in the restruant
}manager;

typedef struct order { // the linked list that set in each table is from type node order
	char* name;
	int price;
	int Quantity;
	char premium;
	struct order* left;
	struct order* right;
}order,*Porder;

typedef struct table { // struct for arrays of tables
	Porder head;
	Porder tail;
	int sum;
}table;

int nameEXIST(char* tempName, manager M); //for scanTHEdishes,addDish,OrderItem
void scanTHEdishes(manager* M);
void Error(char* str);

void addDish(manager *M, char* name, int num); 

void OrderItem(int index,char* name,int count,table * tables,manager* M);

dish* GETtheDISH(manager M, char* name);
int orderEXIST(char* name, table table);

void deleteOrder(int index, char* name, int count,manager* M, table* tables);// the function update the count of dishes if there is need she delete the node from the list

Porder GETtheDISH2(table table, char* name);
void CloseTable(table* table,int num);
#endif