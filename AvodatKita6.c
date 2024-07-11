#include<stdio.h>
#include<stdlib.h>

#define ROWS 3;
#define COLS 3;

void switch_rows(void*** matrix, int row1, int row2);
void print_matrix(int** a, int rows, int cols);
void switch_cols_values(int*** matrix, int rows, int col1, int col2);
void free_matrix(void** c, int n);

int main15()
{
    int rows = ROWS;
    int cols = COLS;

    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }

    // Initialize the matrix with values
    int value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = value++;
        }
    }
    print_matrix(matrix, rows, cols);
    switch_rows(&matrix, 0, 1);
    switch_cols_values(&matrix, rows, 0, 1);
    print_matrix(matrix, rows, cols);
    free_matrix(matrix, rows);
	return 0;
}


void switch_rows(void*** matrix, int row1, int row2)
{
	void* temp = (*matrix)[row1];
	(*matrix)[row1] = (*matrix)[row2];
	(*matrix)[row2] = temp;
}

void switch_cols_values(int*** matrix, int rows, int col1, int col2)
{
    int i,temp;
    for ( i = 0; i < rows; i++)
    {
        temp = (*matrix)[i][col1];
        (*matrix)[i][col1] = (*matrix)[i][col2];
        (*matrix)[i][col2] = temp;
    }
}
void print_matrix(int** a, int rows, int cols)
{
    int i, j;
    printf("The %dx%d dy`namic matrix is:\n",rows,cols);
   for (int i = 0; i < rows; i++) {
       for (int j = 0; j < cols; j++) {
           printf("%d ", a[i][j]);
       }
       printf("\n");
   }
}
