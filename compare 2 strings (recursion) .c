#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// compare two strings without useing strcmp in c

typedef enum {NO,YES} bool ;//the first answer in enum will be 0 value

void Error(char*);
bool compare(char*, char*);
void main()
{
	char* str1, * str2, temp1[10], temp2[10]; // we can assume that the user will not type above 10 char
	//the dinamic allocation will be for practice
	printf("plz enter 2 strings   ");
	scanf("%s %s", temp1, temp2);
	str1 = ((char*)malloc(((strlen(temp1)) + 1) * sizeof(char)));
	if (!str1)
		Error("allocation faild");
	strcpy(str1, temp1);
	str2 = ((char*)malloc(((strlen(temp2)+1) * sizeof(char))));
	if (!str2)
		Error("allocation faild");
	strcpy(str2, temp2);
	if (compare(str1, str2)) printf("the strings are the same");
	else printf("the strings are not the same");
}

void Error(char* string)
{
	puts(string);
	exit(1);
}
 
bool compare(char* str1, char* str2) 
{
	if (*str1 == '\0' && *str2 == '\0') return YES; //if we got to the end all the chars are the same
	if (*str1 != *str2) return NO; // Enough that a pair of letters is not equal return no
	compare(str1 + 1, str2 + 1);// move with the pointers
}
