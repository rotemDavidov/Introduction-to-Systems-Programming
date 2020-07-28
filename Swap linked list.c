//פתרון של רותם דוידוב:

//המטרה לבנות פונקציה שמבצעת החלפה :מצביע לראש הרשימה יצביע כעת לסוף הרשימה
//ואילו האיבר שבראש הרשימה יכיל באיבר הבא שלו נאל.
//קיימים שני פתרונות שחשבתי עליהם לבעיה הזאת:
// פתרון ראשון והאידאלי ביותר הינו ליצור רשימה חדשה
//כלומר להגדיר משתנה לראש זמני ונעבור על הרישמה פעם אחת בלבד
//בכל מעבר נבצע הכנסה לראש, ההכנסה לראש יוצרת באופן אוטומטי רשימה מסודרת בסדר הפוך
//בגלל שרוצים שהמצביע לאיבר הראשון כעת יצביע על האיבר האחרון נעדכן את המשתנה הזמני לראש שלנו
//כעת להיות המצביע שקיבלנו בהתחלה.- זמן ריצה אן  במקרה הגרוע

//פתרון נוסף זה לשנות את הרשימה מבלי ליצור רשימה חדשה אלא עם מצביעים על אותה רשימה קיימת
//כלומר נניח כי יצירה של רשימה חדשה עולה לנו הרבה כסף או שנגיד כי נגמר לנו משאבי המקום בזיכרון של המחשב ואנחנו לא יכולים 
//ליצור רשימה חדשה, הפתרון שלי בפונקציה הזאת יהיה מהמחשבה הזאת, כלומר אני אשנה את הרשימה "בזמן אמת"
//מבלי להשתמש בהקצאות של רשימות חדשות
//זמן ריצה במקרה הגרוע יהיה אן בריבוע, נשים לב שבכל פעם הלולאה המקוננת רצה פחות ריצות ולכן אפשר לחשב
//סיבוכיות זאת על פי טור ולכן זה יכול להיות פחות מאן בריבוע

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct node {
	int num;
	struct node* next;
}node;

void create_list(node**, node**,int);
void swap(node**);

void main() {
	int num, i;
	node *head, *tail;
	tail = head = NULL;
	printf("plz enter 4 numbers");
	for (i = 0; i < 4; i++)
	{
		scanf("%d", &num);
		create_list(&head, &tail, num);
	}
	swap(&head);
	while (head != NULL)
	{
		printf("%d->", head->num);
		head = head->next;
	}
}
void create_list(node** head,node**tail, int num)
{
	node* temp;
	temp = (node*)malloc(sizeof(node));
	if (!temp) { printf("allocation faild"); free(*head); exit(1); }
	temp->num = num;
	temp->next = NULL;
	if (*head == NULL)
	{
     *head=*tail= temp;
	}
	else
	{
		(*tail)->next = temp;
		*tail = temp;
	}
}

void swap(node** head) { //double pointer for changes 
	 
	node* temp, *prev;
	temp = prev = *head;
	while ((*head)->next != NULL)
	{
		prev = *head; //prev will be the previous node to the last
		*head = (*head)->next; //now head will point on the last node
	}
	(*head)->next = prev; //we started to link the list in the opsite way
	prev->next = NULL;
	while (temp->next != NULL)//we want that in the last itrasion the "first" node will point on null
	{
		prev = temp; //always send the pointer to serach the new previous node to the last
		while (prev->next->next != NULL)//we dont want to get to the final node
			prev = prev->next;
		prev->next->next = prev;//link the list in the opsite way
		prev->next = NULL;
	}
	


		




}




