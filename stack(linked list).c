#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NUM 5
typedef struct node {
	int data;
	struct node *next;
}node;

typedef struct stack {
	node* head;
	int size;
}st;

void push(st* S, int data);
int pop(st* Q, int* del_elem);
void print_list(node* head);
void free_list(node** head);

void main() {

	int flag = 1, option,new_elem,del_elem,cheack;
	st stack;
	stack.size = 0;
	stack.head = NULL;//the stack is empty
	while (flag) {
		printf("\nfor push elemnt to the stack press 1\nfor pop elemnt from the stack press 2\n"
			"for print the stack press 3\nfor exit the program press 4\n->");
		scanf("%d", &option);
		switch (option)
		{
		case 1: //push elemnt to the stack 
			printf("what the value you want to be insert");
			scanf("%d", &new_elem);
			push(&stack, new_elem);
			printf("\n");
			print_list(stack.head);
			break;
		case 2: //pop the elmement from the head of the list
			cheack=pop(&stack, &del_elem);
			if (!cheack)
				printf("the stack is empty");
			printf("\n");
			print_list(stack.head);
			break;
		case 3:
			printf("the stack:\n");
			printf("\n");
			print_list(stack.head);
			break;
		case 4 :
			free_list(&(stack.head));
			exit(1);
		}
	}

}
void push(st* Q, int data)
{
	if (Q->size == NUM)
	{
		printf("the stack is full ");
		return;
	}
	
	node* temp;
	temp = (node*)malloc(sizeof(node));
	if (!temp) {
		printf("alloction faild");
		free_list(&Q->head);
		exit(1);
	}
		
	temp->data = data;
	temp->next = NULL;
	//in stack the insert will be to the head;
	temp->next = Q->head;
	Q->head = temp;
	Q->size++;
}

int pop(st* Q, int* del_elem) {
	
	if (Q->size == 0) return 0;
	node* temp;
	temp = Q->head;
	Q->head = Q->head->next;
	*del_elem = temp->data;
	free(temp);
	Q->size--;
	return 1;
}

void print_list(node* head) {
	while (head) {
		printf("%d->", head->data);
		head = head->next;
	}
}
void free_list(node** head) {
	if (!head) return;
	free_list(&(*head)->next);
	free(*head);
}