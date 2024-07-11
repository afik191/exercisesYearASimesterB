#include <stdio.h>
#include<stdlib.h>
#include <assert.h>
#include<string.h>

void printArrInt(int* arr, int size);
void printArrChar(char* arr, int size);
void* realloc1(void* memblock, unsigned size_old, unsigned size_new);
int* arrcat(int* arr1, unsigned size1, int* arr2, unsigned size2);
int hisor_kvozot(int* A, int n, int* B, int m, int* size);


void main2()
{
	
}



//מעבדת כיתה 2
//שאלה 1
void* realloc1(void* memblock, unsigned size_old, unsigned size_new)
{ 
	
	char* pc_old = (char*)memblock, * pc_new = (char*)malloc(size_new);
	int min_size = (size_old) < size_new ? size_old : size_new, i;
	if (pc_old && pc_new)
	{
		for (i = 0;i < min_size;i++)
			pc_new[i] = pc_old[i];
		free(memblock);
		if (size_new == 0)
			return NULL;
	}
	return pc_new;

}


//שאלה 2
int* arrcat(int* arr1, unsigned size1, int* arr2, unsigned size2)
{
	arr1 = (int*)realloc1(arr1, size1 * sizeof(int), (size1 + size2) * sizeof(int));
	if (arr1)
	{
		int i;
		for (i = 0; i < size2 + size1; i++)
		{
			arr1[size1++] = arr2[i];
		}
	}
	return arr1;
}

//שאלה 3
int hisor_kvozot(int* A, int n, int* B, int m, int* size)
{
	int i, j, k = 0, * C;
	C = (int*)realloc1(NULL, 0, n * sizeof(int));
	for (i = 0; i < n; i++)
	{
		for (j = 0;j < m;j++)
			if (B[j] == A[i])
				break;
		if (j == m)
			C[k++] = A[i];
	}
	*size = k;
	C = (int*)realloc1(C, n * sizeof(int), (*size) * sizeof(int));
	return C;
}