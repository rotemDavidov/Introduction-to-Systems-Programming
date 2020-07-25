#include "MATALA3.h"

void main()
{
	int option,num,count,i;
	char cheak;
	char name[40];
	int flag;

	manager manager;
    table tables[SIZE]; //create array from struct table , evrey box will get table temp if the cheaking will be good
	for(i=0;i<SIZE;i++) //there is no orderes in each table 
		tables[i].head = NULL;
	manager.size = 0;

	printf("\t\t\t\t\t ~ HELLO AND WELCOME TO THE RESTAURANT ~\n \t\t\t\t\t\t   \"The Krusty Krab\"\n");
	printf("\ngood day waitress :)\n\n");
	printf("to scan the dishes that the chef spongebob made today please press ~ 1\n");
	printf("to adding dishes to the stock please press ~ 2\n");
	printf("to scan the order of the table please press ~ 3\n");
	printf("to delete the order that the table made please press ~ 4\n");
	printf("to close the table and print the receipt please press ~ 5\n");

	printf("\nfor start working first press 0 -> \n");
	scanf("%c", &cheak);
	while (cheak != '0') //we start scann the file only if the user typed 0
	{
		printf("wrong input plz enter 0 ");
		scanf("%c", &cheak);
	}
	FILE* in = fopen("Instructions.txt", "rt");
	if (!in)
		Error("wrong input file, bye bye");
	
	fscanf(in, "%d", &option);
	if (option != 1)
	{
		Error("you must scan the dishes that the chef create today , bye bye");
	}
	else
		scanTHEdishes(&manager);
 
		while (fscanf(in, "%d", &option)!=EOF)
		{
			
			switch (option)
			{
			case 1:
			scanTHEdishes(&manager);
			function2(manager.head); //for cheak if the function scanTH.. work 
			break;
			case 2:
				fscanf(in, "%s %d", name, &num);
				addDish(&manager, name, num); //the function get a dish name and num and update the dish due to the num
				break;
			case 3:
				fscanf(in, "%d %s %d", &num ,name, &count);
				OrderItem(num, name, count,&tables , &manager);
				break;
			case 4 : //delete or resduce dish from orders
				fscanf(in, "%d %s %d", &num, name, &count);
				deleteOrder(num, name, count, &manager,&tables);
				break;
			case 5:
				fscanf(in, "%d", &num); //scan the table to close
				CloseTable(&(tables[num]),num); //send a pointer to change it dircatly
			}
		}
	

		

}
