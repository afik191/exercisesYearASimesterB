#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
	char last_name[30], first_name[30];
	unsigned id;
} person;

typedef struct unit {
	int value;
	int col;
	struct unit* next;
} unit;


void mix_sorted(char* infile_1, char* infile_2, char* oufile);
int person_sorted_up(person* per, int size);
unit* createNode(int value, int col);
int** make_it_matrix(unit** lists, int rows, int cols);
void printMatrix(int** matrix, int rows, int cols);


void main5()
{
	
}

unit* createNode(int value, int col) {
	unit* newNode = (unit*)malloc(sizeof(unit));
	newNode->value = value;
	newNode->col = col;
	newNode->next = NULL;
	return newNode;
}

void next_number(FILE* in, FILE* out, int* num, char* ch)
{
	fprintf(out, "%d ", *num);
	if ((*ch = fgetc(in)) != '\n')
		fscanf_s(in, num,"%d");
}


void copy_file(FILE* in, FILE* out)
{
	char ch;
	while ((ch = fgetc(in)) != EOF)
		fputc(ch, out);
}


//לחזור לזה
void mix_sorted(char* infile_1, char* infile_2, char* oufile)
{
	//FILE* fin1 = fopen(infile_1, "r"), * fin2 = fopen(infile_2, "r"), * fout = fopen(oufile, "w");
	//char ch1, ch2;
	//int n1, n2;
	//fscanf_s(fin1, &n1,"%d");
	//fscanf_s(fin2, &n2,"%d");
	//while (ch1 != '\n' && ch2 != '\n')
	//	if (n1 < n2)
	//		next_number(fin1, fout, &n1, &ch1);
	//	else
	//		next_number(fin2, fout, &n2, &ch2);

	///* Copying remainder of a longer row */
	//while (ch1 != '\n')
	//	next_number(fin1, fout, &n1, &ch1);
	//while (ch2 != '\n')
	//	next_number(fin2, fout, &n2, &ch2);

	//fputc('\n', fout);
	//fclose(fin1);
	//fclose(fin2);
	//fclose(fout);


	
}

int person_sorted_up(person* per,int size)
{
	int i;
	for ( i = 1; i < size; i++)
	{
		if (strcmp(per[i - 1].last_name, per[i].last_name) == 1)
			return 0;
		else if (strcmp(per[i - 1].first_name, per[i].first_name) == 0
			&& strcmp(per[i - 1].first_name, per[i].first_name) == 1)
			return 0;
		else if (strcmp(per[i - 1].first_name, per[i].first_name) == 0
			&& strcmp(per[i - 1].first_name, per[i].first_name) == 0
			&& per[i - 1].id >= per[i].id)
			return 0;
	}
	return 1;

	/*main
	person people[] = {
	 {"Asher", "Mike", 231567809},
	 {"Bern", "David", 216578900},
	 {"Borgman", "Joseph", 354678903},
	 {"Cohen", "Abraham", 224567821},
	 {"Cohen", "Den", 206666431},
	 {"Levi", "Ilan", 290876441},
	 {"Levi", "Omri", 245689432},
	 {"Levi", "Omri", 245689436},
	 {"Smith", "Jack", 345389010},
	 {"Smith", "John", 311232111}
	};
	printf("%d", person_sorted_up(people, 10));
	*/
}
 
void printMatrix(int** matrix, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}

int** make_it_matrix(unit** lists,int rows, int cols)
{
	int** matrix = (int**)malloc(rows* sizeof(int*)),i;
	unit* cur;
	if (!matrix)
		return;	
	for ( i = 0; i < rows; i++)
	{
		matrix[i] = (int*)calloc(cols, sizeof(int));
		if (!matrix[i])
			return;
	}
	for (size_t i = 0; i < rows; i++)
	{
		if (lists[i]!=NULL)
		{
			cur = lists[i];
			while (cur != NULL)
			{
				matrix[i][cur->col] = cur->value;
				cur = cur->next;
			}
		}
	}
	return matrix;


	/*main
	 unit* lists[4];
	lists[0] = createNode(4, 2);
	lists[0]->next = createNode(7, 4);
	lists[1] = createNode(3, 0);
	lists[2] = createNode(9, 0);
	lists[2]->next = createNode(1, 1);
	lists[2]->next->next = createNode(6, 3);
	lists[3] = NULL;
	int** mat = make_it_matrix(lists, 4, 5);
	printMatrix(mat, 4, 5);
	*/
}
