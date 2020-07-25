#include "MATALA3.h"

void scanTHEdishes(manager* M,FILE* in)
{
	
	char tempName[50]; //for malloc
	int count; //for malloc
	int flag1,flag2=0;

	dish* temp = (dish*)malloc(sizeof(dish)); //FIRST NODE FOR THE FIRST ITRASION
	if (!temp)
		Error("allocation faild");

	FILE* IN = fopen("Manot.txt", "rt"); //OPEN THE FILE IN MODE READ
	if (!IN)
		Error("wrong input file, bye bye");


	while (fscanf(IN, "%s %d %d %c", tempName,&(temp->Quantity), &(temp->price), &(temp->Premium))!=EOF)
	{
		flag2++; // for the final, with every row scanned we inc the flag
		flag1 = 0; //for cheak the error messeges in every error we inc the flag
		if (nameEXIST(tempName,*M)||M->size==0) //send the name to the function for cheak if the name already exist
		{
			count = strlen(tempName); //count the length of the temp name
			temp->ProductName = (char*)malloc(count * sizeof(char)); //malloc with the count
			strcpy(temp->ProductName, tempName);//copt tempName to temp->ProductName
		}
		else
		{
			
			printf("this dish already exist");
			flag1++;
		}
		if (temp->price < 0)
		{
			printf("the price you enter is negative");
			flag1++;
		}
		if(temp->Quantity<0)
		{
			printf("the quantity you enter is negative");
			flag1++;
		}

		if (flag1 == 0)////if everything is ok and the user is a good person /////
		{
			if (M->size == 0) //if the list is empty the head and the tail point on the same node
			{
				M->head = M->tail = temp; 
				M->tail->next = M->head->next = NULL; 
				
			}
			else
			{
				temp->next = M->head; //temp push to the start of the list
				M->head = temp; // now temp is the head of the list
			}
			M->size++;
			//flag2--; // we count dish as a error potanshial and now after we see everythings is ok
			// we dec the dish
			//outside the loop : if (flag2 > 0)
		//printf("the scan of the dishes didnt succsed");
		 temp = (dish*)malloc(sizeof(dish)); //create temp node for the rest of the itrasion
		 if (!temp)
			 Error("allocation faild");
	
		}
	}
	if(M->size!=flag2) // if the scanned rows not equale to the number of nods in the list print error messege.
		printf("the scan of the dishes didnt succsed");

	fclose(IN);
	
}

 int nameEXIST(char* tempName,manager M)
{
	int i;
	
	for (i = 0; i < M.size; i++)
	{
		if(!strcmp(M.head->ProductName,tempName))
		return 0;
		M.head = M.head->next;
	}
	return 1;
}

 void Error(char *str)
 {
	 puts(str);
	 exit(1);
 }

 void function2(manager M)
 {
	 while (M.head != NULL)
	 {
		 printf("%s", M.head->ProductName);
		 M.head = M.head->next;
	 }
 }

 void addDish(manager* M, char* name, int num)
 {
	 dish* temp;
	 temp = M->head;
	 if (nameEXIST(name, *M)) //if the function nameEXIST return 1 the name doesnt exist
	 {
		 printf("the dish %s doesnt exist", name);
	 }
	 else
	 {
		 while (temp != NULL)
		 {
			 if (!(strcmp(temp->ProductName, name)))
			 {
				 temp->Quantity = temp->Quantity + num;
				 temp = temp->next;
			 }
			 else temp = temp->next;
		 }
	 }
 }

 void OrderItem(int index, char* name, int count, table* tables, manager* M)
 {
	 dish* dish = NULL;
	 Porder temp;
	 int length;
	 if (index > SIZE) // if the user types a wrong input table
	 {
		 printf("there is no such table as %d", index);
	 }
	 else if (nameEXIST(name, *M)) //if the function return 1 threre is no such dish as name in the kitchen
	 {
		 printf("there is no such dish as %s", name);
	 }
	 else
	 {
		 //if the dish exist in the kitchen we will do couple of cheakes

		 dish = GETtheDISH(*M, name); // if the dish exist in the kitchen we will get the adress of the node and change it diractaly

									  // the first  cheak :

		 if (count <= 0 && count > dish->Quantity) // if the user typed negative count or there is no stock for the dish
			 printf("we are sorry there is no stock such as %d for the dish %s", count, name);

		 //the second cheak:

		 else if (orderEXIST(name, tables[index])) //if the table already order the dish and thay want more just udpate the information
		 {
			 temp = GETtheDISH2(tables[index], name); //get a pointer to node to change it directly 
			 temp->Quantity = temp->Quantity + count;
			 dish->Quantity = dish->Quantity - count; //reduce the stock in the kitchen
			 tables[index].sum = tables[index].sum + dish->price*count; // update the final sum
			 
		 }

		 // if all the cheakes turned out good
// the input is correct and this is the first time the order is placed
		 else

			 //all this cheakes can be used in one function for organization


		 {
			 if (tables[index].head == NULL) // if the table didnt order any dishes
			 {
				 tables[index].sum = 0; // restart the sum of the table 
				 //preapre the first dish to the list of orders
				 temp = (order*)malloc(sizeof(order)); // create node


				 length = strlen(name); //count the length of the temp name
				 temp->name = (char*)malloc(length * sizeof(char)); //malloc with the count
				 strcpy(temp->name, name); // copy the name of the dish

				 temp->right = temp->left = NULL; // restart the pointer left and right to NULL bc this is the only dish

				 temp->price = dish->price; //the price of the dish that order add to the final sum of the table
			     dish->Quantity = dish->Quantity - count; // update the store of the dish
				 temp->Quantity = count; //the first time; restart the count
				 temp->premium = dish->Premium;

				 
				 //after all the preparation we can update the first dish that the table orderd as the first dish
				 tables[index].tail = tables[index].head = temp;
				 tables[index].sum += temp->price*count; // i can update the sum directly from the dish and not from the temp and delete the type price from the node order

			 }
			 else // if the table already order dishes the head is not null
			 {

				 // prepare the dish to linked to the other dishes
				 temp = (order*)malloc(sizeof(order)); // create node
				

				 length = strlen(name); //count the length of the temp name
				 temp->name = (char*)malloc(length * sizeof(char)); //malloc with the length
				 strcpy(temp->name, name); // copy the name of the dish

				 temp->right = NULL; // we prepare the temp to be the last dish so there no dishes afetr him
				 
				 // we dont update the left in this step of function
				 temp->price = dish->price; //the price of the dish that order add to the final sum of the table
				 dish->Quantity = dish->Quantity - count; // the quantity of dishes on now updating due  to the count of dishes that the user order
				 temp->Quantity = count; //update the count 
				 temp->premium = dish->Premium;
				 tables[index].sum += temp->price * count;

				 //after all the preparation we can update the order to the list
				 temp->left = tables[index].tail; // temp is linked to the last order from left to right
				 tables[index].tail->right = temp; // the last dish that order is now linked to temp from right to left
				 tables[index].tail = temp; // the last dish that order is now temp
			 }
		 }
	 }
 }
 dish* GETtheDISH(manager M, char* name)//get the dish from the struct Mangaer
 {
	 while (M.head != NULL)
	 {
		 if (!strcmp((M.head->ProductName), name))
			 return (M.head);
		 M.head = M.head->next;
	 }

 }
 Porder GETtheDISH2(table table, char* name)   //get the dish from struct table
 {
	 while (table.head != NULL)
	 {
		 if (!strcmp((table.head->name), name))
			 return (table.head);
		 table.head = table.head->right;
	 }
	 return NULL;
 } 

 int orderEXIST(char* name, table table)// ------------------ can change the function to IF RETURN NULL AND DELTER THE FUNCTION GET THE DISH 2
 {
	 while (table.head != NULL)
	 {
		 if (!(strcmp(table.head->name, name)))
			 return 1;
		 else table.head = table.head->right;
	 }
	 return 0;
 }
  
 void deleteOrder(int index, char* name, int count, manager* M, table* tables)
 {
	 Porder temp;
	 if (index > SIZE) // if the user types a wrong input table
	 {
		 printf("there is no such table as %d", index);
	 }
	 else
	 { 
		         // -----------if there is table as index we will cheak the exist of the dish------

		 //first cheak: if the order exist in the kitchen
		 if (nameEXIST(name, *M)) //if the function return 1 there is no such dish as name in the kitchen
			 printf("there is no such dish as %s", name);

		 //second cheak: if the dish orderd in the table index
		 if (!orderEXIST(name, tables[index])) //if the function return 0 the table didnt order this dish and there is nothing to delete
			 printf("wrong input - the table didnt order the dish %s", name);

		         //------------if the dish is orderd we will cheak the input 'count' to delete-----

		 temp = GETtheDISH2(tables[index], name); //temp=dish to update //2-from table and not from manager
		 if (!temp) printf("error cant find the dish %s in the memory", name);
		 if (count <= 0 && temp->Quantity < count) //if the count to delete is negative or the table want to delete more than what thay order
			printf("wrong input to delete- negative or grater than the Quantity of the orderd dish");
		 
		      //--------------if all the cheakes turned out good we will update the changes in temp that point on the dish-----
		 
		 else
		 {
			 temp->Quantity = temp->Quantity - count; //reduce the count
			 tables[index].sum = (tables[index].sum) - ((temp->price)*count); //reduce from sum the price of the dish mul the count of the dish to delete
		      

			 //after the reduce we will cheak if the quantity of the dish is zero
			 //we will delete the order (free the node) from the table (bc we dont need that ~
			 //the table will see it in the final recepit)
		  
			 if (temp->Quantity == 0)
			 {
				 //for delete we have 3 option
				 //option 1: if the node to delete is the first node in the list
				 if (tables[index].head == temp)
				 {
					 tables[index].head = tables[index].head->right; //update the head	
					 tables[index].head->left = NULL;//disconecct the link to the old head
					 free(temp); //free the node

				 }
				 //option 2: if the node to delete is the last node in the list
				 if (tables[index].tail == temp)
				 {
					 tables[index].tail = tables[index].tail->left;//update the tail
					 tables[index].tail->right = NULL;//disconect the link to the old tail
					 free(temp);//free the node
				 }


				 //option 3: if the node to delete is in the middle of the list
				 else
				 {
					 temp->left->right = temp->right; 
					 temp->right->left = temp->left;
					 temp->right = temp->left = NULL;//disconect
					 free(temp);
				 }

			 }
		 
		 }

	 }

	

 }

 void CloseTable(table* table,int num)
 {
	 int flag = 0;
	 printf("\n========= recepit table number %d ==========\n",num);
	 printf("count:  name:  price per unit:   primuem:\n");
	 while (table->head != NULL) //print all the info in the end the head will be null so we will free just the tail
	 {
		 printf("X %d   %s\t  %d\t\t  %c\n", table->head->Quantity, table->head->name, table->head->price, table->head->premium);
		 if (table->head->premium == 'Y')
			 flag++;
		 table->head = table->head->right;
	 }
	 if (flag > 0)
		 table->sum = (table->sum) * 1.1;
	 printf("the sum to pay is : %d\n", table->sum);
	 printf("=============== thank you ! =============\n\n\n");
	 table->tail = NULL;
	 table->sum = 0;

 }