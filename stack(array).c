#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
 

typedef struct Stack {
	int top;         //index of the last member in array of a stack;
	int* Array;   //pointer to array of members of a stack
	int size;      //size of the array of a stack
	int count;   //the current number of members
}Stack, * PStack;

void InitStack(PStack s, int size);    //initialization of a new stack with capacity of size elements
void Push(PStack s, int   new_elem);  //add a new member to array of the stack 
int Pop(PStack s, int* del_value); //delete member from the array of the stack and  return the deleted value  using  int * del_value

int main()
{
	Stack st;
	int del_value, flag;
	InitStack(&st, 4);
	Push(&st, 3);
	Push(&st, 5);
	Push(&st, 1);
	Push(&st, 10);
	flag = Pop(&st, &del_value);
	if (flag)
		printf("\n%d was deleted", del_value);
	Push(&st, 8);
	flag = Pop(&st, &del_value);
	if (flag)
		printf("\n%d was deleted", del_value);
	flag = Pop(&st, &del_value);
	if (flag)
		printf("\n%d was deleted", del_value);
	Push(&st, 7);
	Push(&st, 4);
	Push(&st, 100);
	flag = Pop(&st, &del_value);
	if (flag)
		printf("\n%d was deleted", del_value);
	while (st.count)
	{
		flag = Pop(&st, &del_value);
		if (flag)
			printf("\n%d was deleted", del_value);
	}
	printf("\n");
	flag = Pop(&st, &del_value);
	if (flag)
		printf("\n%d was deleted", del_value);

	free(st.Array);

	return 0;
}
void InitStack(PStack s, int size) { 

	//alocation for araay in the size size
	s->Array = (int*)malloc(size * sizeof(int));
	if (!(s->Array))
	{
		printf("allcation faild");
		exit(1);//we want to close the program if there is no location for out stack
	}
	s->size = size; 
	s->count = 0; //there is no members in the stack right now

	// i cant reset the top because zero is a real place for value, another soultion is reset the top to be
	//in place -1 
}
void Push(PStack s, int   new_elem)
{
	if (s->count == s->size) { //if the stack is full i cant add another member
		printf("the stack is full");
		return;
	}
	if (s->count == 0)
		s->top = 0;//bc in the array every index count from zero than the first elemnt will be in zero place
	else s->top++;
	s->Array[s->top] = new_elem;
	s->count++;
}
int Pop(PStack s, int* del_value)
{
	if (s->count == 0)
	{
		printf("the stack is empty");
		return 0;
	}
	*del_value = s->Array[s->top];
	s->top--;
	s->count--;
	return 1;
}