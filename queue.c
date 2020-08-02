#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*in this program we will see how queue wroks- under the condition FIFO - first in first out
the queue will be executed in a linked list*/

#define MAX 5 //the maximum number in the queue will be 5

typedef struct node {
	int data;
	struct node* next;
}node;

/*manager struct */
typedef struct queue {
	 node* head; //head to the linked list for delete
	 node* tail;//tail to the linked list for insert
	int size;//size for cheaking if the queue is full under the codition that the queue have a max MAX nodes.
}queue,*Pqueue;

void Enqueue(Pqueue Q, int new_elem);   //add a new member to list of the queue 
int Dequeue(Pqueue Q, int* value);     //delete member from the queue and  return the deleted value using int *del_value
node* create_node(Pqueue Q, int data);
void free_list(node** head);
void print_list(node* head);
node* get_pointer(node* head, int data);

void change_priority(node** head, node* change);

void main()
{
	int new_elem, flag=1,option,temp;
	queue Q;
	Q.head = Q.tail = NULL;
	Q.size = 0;
	int value;
	node* temp2;
	while (flag)
	{
		printf("\n\nfor insert elemnt press 1\nfor delete element press 2 \nprint the"
	    "list press _3\n for change priority press 4\nfor exit the program press 5\n->");
		scanf("%d", &option);
		switch (option)
		{
		case 1: //insert element to the queue
			printf("insert a data for the element ");
			scanf("%d", &new_elem);
			Enqueue(&Q, new_elem); //insert element to the queue
			print_list(Q.head);
			break;
		case 2: //delete element in the queue
			temp=Dequeue(&Q,&value); //the node to be delete will be in del value;
			if (temp)
			{
				printf("the node you have been delete is : %d \n the list after changes: ", value);
				print_list(Q.head);
			}
			else
				printf("the queue is empty there is nothing to delete");
			break;
		case 3: // print the queue
			print_list(Q.head);
			break;
		case 4 :  //guess we are in israeli queue and the manager of the queue meet someone in the queue and promote 
			//one of the members to the head of the queue
			
			printf("which node do you want to change the priority ? ");
			scanf("%d", &value);
			temp2 = get_pointer(Q.head, value);
			if (!temp2)
				printf("the member u enterd not in the queue");
			else
			{
				change_priority(&(Q.head), temp2);
				printf("the list after changes :");
				print_list(Q.head);
			}
			break;
			
		case 5:
			printf("bye bye");
			free_list(&(Q.head)); //send the adress to the pointer that point on head (double pointer)
			flag = 0;
			break;
		}
		
	}
}


void Enqueue(Pqueue Q, int new_elem) {
	if (Q->size == MAX)
	{
		printf("the queue is full");
		return;
	}
	node* temp= create_node(Q, new_elem);
	if (!temp) // if allocation faild 
	{
		free_list(Q->head);
		exit(1);
	}
	if (Q->size == 0) 
		Q->head = Q->tail = temp;
	else //insert node to the tail
	{
		Q->tail->next= temp;
		Q->tail = temp;
	}
	Q->size++;
}



node* create_node(Pqueue Q, int data)
{
	node* temp;
	temp = (node*)malloc(sizeof(node));
	if (!temp)
	{
	printf("allocation faild"); 
	return NULL;
	}
	temp->data = data;
	temp->next = NULL;
	return temp;
}

void free_list(node ** head) //free list in recursion . get a double pointer for changes in real time
{
	if (*head == NULL)
		return;
	free_list(&(*head)->next);
	free(*head);
	
}
int Dequeue(Pqueue Q, int* del_value)
{
	// we will disconnect the first node in the list and return the member in  del value;
	if (Q->size == 0)
		return 0; //there is nothing in the list
	else
	{
		*del_value = Q->head->data; 
		Q->head = Q->head->next;//disconntct
		Q->size--;
		return 1;//the delting succeed
	}
}

void print_list(node* head)
{
	while (head)
	{
		printf("%d->",head->data);
		head = head->next;
	}
}
node* get_pointer(node* head,int data)
{
	while (head)
	{
		if (head->data == data)
			return head;
		head = head->next;
	}
	return NULL;
}
void change_priority(node** head, node* change) //take the node temp and put him in the head 1 2 3
{
	node* temp=*head;
	while (temp->next!=change) //put pointer befor change to new linked
	{
		temp = temp->next;
	}
	temp->next = change->next;
	change->next = *head;
	*head = change;
}