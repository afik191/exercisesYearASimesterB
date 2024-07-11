#include<stdio.h>
#include<stdlib.h>

typedef struct linked_list
{
	char letter;
	struct linked_list* next;
}linked;

void print_list(linked* head);
void insert_letter(linked** head, char let);
linked* linked_input();
void revesre_link(linked** head);
void free_list(linked* head);

void main11()
{
	linked* head = linked_input();
	revesre_link(&head);
	print_list(head);
	free_list(head);
}

void free_list(linked* head)
{
	linked* cur = head, * prev = head;
	while (cur->next!=NULL)
	{
		cur = cur->next;
		free(prev);
		prev = cur;
	}
}

void print_list(linked* head)
{
	linked* cur = head;
	while (cur != NULL)
	{
		printf("%c->", cur->letter);
		if (cur->next != NULL)
			cur = cur->next;
		else
		{
			printf("NULL\n");
			break;
		}
	}
}

void insert_letter(linked** head, char let)
{
	linked* new_let = (linked*)malloc(sizeof(linked));
	if (!new_let) { 
		printf("Memory allocation failed\n");
		return;
	}
	new_let->letter = let;
	new_let->next = NULL;

	if (*head == NULL || (*head)->letter >= let) { 
		new_let->next = *head;
		*head = new_let;
		return;
	}

	linked* cur = *head;
	while (cur->next != NULL && cur->next->letter < let) { 
		cur = cur->next;
	}

	new_let->next = cur->next;
	cur->next = new_let;
}

linked* linked_input()
{
	linked* head = NULL;
	char temp;

	printf("write a letter\n");
	scanf_s(" %c", &temp);  

	while (temp >= 'A' && temp <= 'z') {
		insert_letter(&head, temp);
		printf("write a letter\n");
		scanf_s(" %c", &temp);  
	}
	print_list(head);
	return head;
}

void revesre_link(linked** head)
{
	if ((*head)->next == NULL)
		return;
	linked* one = *head, * two = *head, * three = *head;
	if(one->next->next ==NULL)
	{
		*head = one->next;
		(*head)->next = one;
		(*head)->next->next = NULL;
		return;
	}
	if (one->next->next->next == NULL)
	{
		(*head) = one->next->next;
		two = one->next;
		(*head)->next = two;
		two->next = one;
		one->next = NULL;
		return;
	}
	if (one->next->next!=NULL)
	{
		two = two->next;
		one = one->next->next;
		two->next = three;
	}

	while (one!=NULL)
	{
		if (one->next->next==NULL)
		{
			three = two;
			two = one;
			one = one->next;
			two->next = three;
			one->next = two;
			(*head)->next = NULL;
			*head = one;
			return;
		}
		else
		{
			three = two;
			two = one;
			one = one->next;
			two->next = three;
		}	
	}
}












