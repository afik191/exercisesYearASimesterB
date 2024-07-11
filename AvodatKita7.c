#include<stdio.h>
#include<stdlib.h>

#define ROWS 3;
#define COLS 3;

int** alloc_matrix(int rows, int cols);
int** top_triangle_matrix(int** mat, int rows, int cols);
void print_matrix(int** a, int rows, int cols);
int return_that_value(int** mat, int row, int col);
int** bottom_triangle_matrix(int** mat, int rows, int cols);

int main24()
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
	print_matrix(matrix,rows,cols);
	matrix = bottom_triangle_matrix(matrix, rows, cols);
	print_matrix(matrix,rows,cols);
	return 0;
}

int** top_triangle_matrix(int** mat, int rows, int cols)
{
	int** new_mat = alloc_matrix(rows, cols);
	int i,j;
	for (i = 0; i < rows; i++)
	{
		for ( j = 0; j < cols; j++)
		{
			if (j < i)
			{
				 new_mat[i][j] = mat[i][j];
			}
		}
	}
	return new_mat;
}

int return_that_value(int** mat, int row, int col)
{
	return mat[row][col];
}

int** bottom_triangle_matrix(int** mat, int rows, int cols)
{
	int** new_mat = alloc_matrix(rows, cols);
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (j > i)
			{
				new_mat[i][j] = mat[i][j];
			}
		}
	}
	return new_mat;
}