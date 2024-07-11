#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

typedef struct item
{
	int data;
	struct item* next;
} Item;

typedef struct pair
{
	int num_text_rows;
	int num_bin_records;
} Pair;


void switch_rows_by_sizes(void** A, int rows, int* size);
Item* cut_list(Item* list);


void main()
{
	
	
}


void switch_rows_mat(void** mat, int row1, int row2)
{
	void* temp = mat[row1];
	mat[row1] = mat[row2];
	mat[row2] = temp;
}

void switch_sizes(int* sizes, int loc1, int loc2)
{
	int temp = sizes[loc1];
	sizes[loc1] = sizes[loc2];
	sizes[loc2] = temp;
}

//Q1
void switch_rows_by_sizes(void** A, int rows, int* size)
{
	int row1=0,row2=rows-1;
	while (row2>row1)
	{
		switch_rows_mat(A, row1, row2);
		switch_sizes(size, row1, row2);
		row1++;
		row2--;
	}
}

//Q2
Item* cut_list(Item* list)
{
	if (list == list->next)
		return list;
	if (list == NULL)
		return NULL;
	Item* cur = list->next, * biggest = list;
	int margin = 0,dis;
	while (cur!=list)
	{
		dis = abs((cur->data) - (cur->next->data));
		if (dis > margin)
		{
			margin = dis;
			biggest = cur;
		}
		cur = cur->next;
	}
	list = biggest->next;
	biggest->next = NULL;
	return list;

	/* main
	  Item* h, l1, l2, l4, l7;
	l1.data = 1;
	l2.data = 2;
	l4.data = 4;
	l7.data = 7;
	l4.next = &l7;
	l7.next = &l1;
	l1.next = &l2;
	l2.next = &l4;
	h = cut_list(&l4);
	*/
}

//Q3
/* Counting number of rows in text file */
int NumOfRows(char* fname) {
	FILE* f = fopen(fname, "r");
	int count = 0;
	char c;
	if (!f) return 0;
	while ((c = fgetc(f)) != EOF)
		if (c == '\n') count++;
	fclose(f);
	return count;
}

/* Counting number of records in binary file */
int NumOfRecords(char* fname, int rec_size) {
	char c;
	FILE* f = fopen(fname, "rb");
	int count = 0;
	if (!f) return 0;
	while (fread(&c, 1, 1, f)) //byte by byte input
		count++; //number of bytes
	fclose(f);
	return count / rec_size; //number of records
}

/* Extract a record size from a binary file name */
int getNumber(char* str) {
	int i = 0, dec = 1, num = 0;
	while (str[i] != '.') i++;
	i--; /*Scan of digits and deriving the number to the left of the point*/
	while (isdigit(str[i])) {
		num += (str[i--] - '0') * dec;
		dec *= 10;
	}
	return num;
}

Pair* numRowsRecords(char** Infiles, int n) {
	Pair* Results = (Pair*)malloc(n * sizeof(Pair));
	int i;
	for (i = 0; i < n; i++) {
		if (Infiles[i][0] == 'b' || Infiles[i][0] == 'B') {
			/* Processing of binary file */
			int rec = getNumber(Infiles[i]);
			Results[i].num_bin_records = NumOfRecords(Infiles[i], rec);
			Results[i].num_text_rows = -1;
		}
		else {
			/* Processing of text file */
			Results[i].num_text_rows = NumOfRows(Infiles[i]);
			Results[i].num_bin_records = -1;
		}
	} //for 
	return Results;
}
