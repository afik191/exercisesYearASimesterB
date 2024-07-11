#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
    char first_name[30], last_name[30];
} name;

typedef struct Item {
	int data;
	struct Item* next;
} item;


int is_sorted_by_value(name* names, int size);
item* cyclic_lists_combining(item* L1, item* L2);

void main6()
{
	
}

//Q1
int is_sorted_by_value(name* names, int size)
{
	int i, count[2] = { 0 };
	for ( i = 1; i < size; i++)
	{
		if (strcmp(names[i - 1].first_name, names[i].first_name) == -1)
			count[0]++;
	    if (strcmp(names[i - 1].last_name, names[i].last_name) == -1)
			count[1]++;
	}
	if (count[0] != size - 1 && count[1] != size - 1)
		return 0;
	else if (count[0] == size - 1)
		return 1;
	else if (count[1] == size - 1)
		return 2;

	/* main
	  name names[] = {
	   {"Mike", "Asher"},
	   {"David", "Bern"},
	   {"Joseph", "Borgman"},
	   {"Alon", "Kapulski"},
	   {"Ilan", "Mizrachi"},
	   {"Oren", "Nodel"},
	   {"Abraham", "Rosen"}
	};
	int a = is_sorted_by_value(names, 7);
	*/
}

//Q2
/* Auxiliary function. Search of common items.
   The function gives addresses of items preceding common ones */
void addresses_of_items_preceding_common(item* L1, item* L2, item** p1, item** p2) {
	item* prev1 = L1, * prev2, * curr1 = prev1->next, * curr2;
	while (1) //external loop: scan first list
	{
		prev2 = L2;
		curr2 = prev2->next;
		do //internal loop: scan second list
		{
			if (curr2->data != curr1->data)
			{
				prev2 = curr2;
				curr2 = curr2->next;
			}
			else //common items are found
			{
				*p1 = prev1;
				*p2 = prev2;
				return;
			}
		} while (curr2 != L2->next);
		prev1 = curr1;
		curr1 = curr1->next;
	} //while (1)
}

/* Special case: list L1 has one item */
item* one_item_list(item* L1, item* L2) {
	int common = L1->data;
	free(L1);
	while (L2->data != common) //search of common item in L2
		L2 = L2->next;
	return L2;
}

item* cyclic_lists_combining(item* L1, item* L2) {
	item* p1, * p2, * common;
	if (L1->next == L1) //L1 has one item
		return one_item_list(L1, L2);
	if (L2->next == L2) //L2 has one item
		return one_item_list(L2, L1);

	//p1 and p2 are addresses of items preceding common ones
	addresses_of_items_preceding_common(L1, L2, &p1, &p2);

	/* Combining of L1 and L2*/
	common = p1->next;
	p1->next = p2->next->next;
	free(p2->next);
	p2->next = common;
	return common;
}




//Q3
int** expand_file_to_mat(char* filename,int** S,int* rows)
{
	char ch;
	int** A, num, size, start_row, i, j, k;
	FILE* fptr = fopen(filename, "r");
	if (!fptr)
		exit(1);

	/* Estimation of the number of rows */
	*rows = 0;
	while ((ch = fgetc(fptr)) != EOF)
		if (ch == '\n')
			(*rows)++;

	A = (int**)calloc(*rows, sizeof(int*)); //pointer array allocation
	*S = (int*)calloc(*rows, sizeof(int)); //array of row sizes allocation

	rewind(fptr);
	for (i = 0; i < *rows; i++)
	{
		start_row = ftell(fptr);

		/* Estimation of row size */
		do
		{
			fscanf_s(fptr, "%d%d", &num, &size);
			(*S)[i] += size;
		} while ((ch = fgetc(fptr)) != '\n');

		A[i] = (int*)calloc((*S)[i], sizeof(int)); //row allocation

		/* File row -> array row */
		fseek(fptr, start_row, SEEK_SET);
		k = 0;
		do
		{
			fscanf_s(fptr, "%d%d", &num, &size);
			for (j = 1; j <= size; j++, k++)
				A[i][k] = num;
		} while ((ch = fgetc(fptr)) != '\n');
	} //for i

	fclose(fptr);
	return A;


}