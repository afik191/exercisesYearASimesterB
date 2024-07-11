#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

typedef struct Item
{
	int data;
	struct item* next;
} item;


int sorted_string(char* str);
item* starters_list(item** A, int rows, item* L);
item* createItem(int data);
void appendItem(item** head, int data);

void main7()
{

}

//Q1
int sorted_string(char* str)
{
	int sorts[3] = { 0 };//[bigger][lower][numbers]
	int i=1;
     	if (isupper(str[0]))
			sorts[0] = str[0];
		if (islower(str[0]))
			sorts[1] = str[0];
		if (isdigit(str[0]))
			sorts[2] = str[0];
	while (str[i]!='\0')
	{
		if (isupper(str[i]) && str[i] < sorts[0])
			return 0;
		if (islower(str[i]) && str[i] < sorts[1])
			return 0;
		if (isdigit(str[i]) && str[i] < sorts[2])
			return 0;
		if (isupper(str[i]))
			sorts[0] = str[i];
		if (islower(str[i]))
			sorts[1] = str[i];
		if (isdigit(str[i]))
			sorts[2] = str[i];
		i++;
	}
	return 1;

	/*main
	  char* s = "B4$Ca#%ds5P8P&9zY";
	  int m = sorted_string(s);
	*/
}


int isprefix(item* L, item* A)
{
	while (L && A)
	{
		if (L->data != A->data)
			return 0;
		L = L->next;
		A = A->next;
	}
	if (L)
		return 0;
	return 1;

}
//Q2
item* starters_list(item** A, int rows, item* L)
{
	int i,index=0;
	item* cur_L=L, * CUR_A,*indexes=malloc(sizeof(item))/*dummy*/,*cur_indexes=indexes;
	for ( i = 0; i < rows; i++)
	{
		CUR_A = A[i];
		if (isprefix(L, CUR_A) == 1)
		{
			cur_indexes->next = (item*)malloc(sizeof(item));
			cur_indexes = cur_indexes->next;
			cur_indexes->data = i;
		}
		
	}
	cur_indexes->next = NULL;
	cur_indexes = indexes;
	indexes = indexes->next;
	free(cur_indexes);
	return indexes;
}

item* createItem(int data) {
	item* newItem = (item*)malloc(sizeof(item));
	newItem->data = data;
	newItem->next = NULL;
	return newItem;
}

// פונקציה להוספת פריט בסוף הרשימה
void appendItem(item** head, int data) {
	item* newItem = createItem(data);
	if (*head == NULL) {
		*head = newItem;
	}
	else {
		item* temp = *head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newItem;
	}
}

//Q3
#define COLS 5
void file_to_sparse_matrix(char* filename, int A[][COLS], int rows, int cols)
{
	FILE* f = fopen(filename, "r");
	if (!f)
		return;
	char ch;
	int cur_row,i,val,j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			A[i][j] = 0;
	for ( i = 0; i < rows; i++)
	{
		fscanf_s(f, "%d", &cur_row);
		while ((ch=fgetc(f)) !='\n')
		{
			fscanf_s(f, "%d%d", &val, &j);
			A[i][j] = val;
		}
	}
	fclose(f);

	
	
}