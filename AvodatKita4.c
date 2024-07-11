#include<stdio.h>
#include<stdlib.h>

typedef struct List
{
	unsigned num;
	struct List* next;
}node;

int evenOrOdd(node** headeven, node** headodd);
void printNode(node** head);
void deleteNode(node** head);
int sumNums(node* head, int* min, int* max);

void main7()
{
	node* he;
	node* ho;
	int a = evenOrOdd(&he, &ho);
	printNode(&he);
	printNode(&ho);
	int min, max;
	printf("\nsum:%d", sumNums(he, &min, &max));
	
}

void deleteNode(node** head)
{
	node* current = *head;
    node* next;

	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}

	*head = NULL; 
}
void printNode(node** head)
{
	node* cur = *head;
	while (cur!=NULL)
	{
		printf("%d->", cur->num);
		if (cur->next != NULL)
			cur = cur->next;
		else
		{
			printf("NULL\n");
			break;
		}
	}
}

int evenOrOdd(node** headeven,node** headodd)
{
	int amount = 0;
	*headeven=NULL;
	node* prevEven=NULL;
	node* curEven = *headeven;
	*headodd=NULL;
	node* curOdd = *headodd;
	node* preOdd=NULL;
	int get;
	printf("write positive num\n");
	scanf_s("%d", &get);
	while (get!=-1)
	{
		amount++;
		if (get%2==0)
		{
			if (*headeven==NULL)
			{
				*headeven = (node*)malloc(sizeof(node));
				(*headeven)->num = get;
				(*headeven)->next = NULL;
				curEven = *headeven;
				prevEven = *headeven;
			}
			else
			{
				curEven->next = (node*)malloc(sizeof(node));
				curEven = curEven->next;
				curEven->num = get;
				prevEven->next = curEven;
				prevEven = curEven;
				curEven->next = NULL;
			}
		}
		else
		{
			if (*headodd == NULL)
			{
				(*headodd) = (node*)malloc(sizeof(node));
				(*headodd)->num = get;
				(*headodd)->next = NULL;
				curOdd = preOdd = *headodd;
			}
			else
			{
				curOdd->next = (node*)malloc(sizeof(node));
				curOdd = curOdd->next;
				curOdd->num = get;
				preOdd->next = curOdd;
				preOdd = curOdd;
				curOdd->next = NULL;
			}
		}
		printf("write positive num\n");
		scanf_s("%d", &get);
	}
	return amount;
}

int sumNums(node* head, int* min, int* max)
{
	node* cur = head;
	int sum = 0;
	*max = 0, *min = 1000;
	while (cur!=NULL)
	{
		if (cur->num > *max)
			*max = cur->num;
		if (cur->num < *min)
			*min = cur->num;
		sum += cur->num;
		cur = cur->next;
		
	}
	printf("\nmax:%d, min:%d", *max, *min);
	return sum;
}