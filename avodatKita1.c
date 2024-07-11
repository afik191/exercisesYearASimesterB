#include <stdio.h>
#include<stdlib.h>
#include <assert.h>
#include<string.h>


int* zogiandizogi(int* A, int size, int** arrizogi, int* sizezogi, int* sizeizogi);
void charssplit(char* arr, int size, char** big, int* sizebig, char** small, int* sizesmall);
void strsplit(char* str, char** big, char** small);
void removeDup(int* arr, int size, int** newarr, int* newsize);
void printArrInt(int* arr, int size);
void printArrChar(char* arr, int size);
int* removeDupPointer(int* arr, int size, int* newsize);
int removeDupSize(int* arr, int size, int** newarr);
int* zogiandizogiRealloc(int* arr, int size, int** arrodd, int* sizezogi, int* sizeizogi);
void charssplitRealloc(char* arr, int size, char** big, int* sizebig, char** small, int* sizesmall);
void strsplitRealloc(char* str, char** big, char** small);

void main1()
{
	
	
}

void printArrInt(int* arr, int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("[%d]", arr[i]);
	printf("\n");
}
void printArrChar(char* arr, int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("[%c]", arr[i]);
	printf("\n");
}

//מעבדת כיתה 1
//שאלה 1
int* zogiandizogi(int* A,int size, int** arrizogi, int* sizezogi, int* sizeizogi)
{
	*sizezogi = 0, * sizeizogi = 0;
	int i;
	for ( i = 0; i < size; i++)
	{
		if (A[i] % 2 == 0)
			(*sizezogi)++;
	}
	*sizeizogi = size - *sizezogi;
	int* arr1zogi = (int*)calloc((*sizezogi),sizeof(int));
	*arrizogi = (int*)calloc((*sizeizogi),sizeof(int));
	assert(arr1zogi);assert(arrizogi);
	for ( i = 0,*sizezogi=0,*sizeizogi=0; i < size; i++)
	{
		if (A[i] % 2 == 0)
			arr1zogi[(*sizezogi)++] = A[i];
		else
			(*arrizogi)[(*sizeizogi)++] = A[i];
	}
	return arr1zogi;

	//במיין
	/*int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int* zogi;int* izogi;
	int sizezogi1;int sizeizogi1;
	zogi = zogiandizogi(arr, 10, &izogi, &sizezogi1, &sizeizogi1);
	printArr(zogi, sizezogi1);
	printArr(izogi, sizeizogi1);
	free(zogi);free(izogi);*/
}

//מעבדת כיתה 1
//שאלה 2
void charssplit(char* arr, int size, char** big, int* sizebig, char** small, int* sizesmall)
{
	int i;*sizebig = 0, * sizesmall = 0;
	for ( i = 0; i < size; i++)
	{
		if (arr[i] >= 'A' && arr[i] <= 'Z')
			(*sizebig)++;
		else
			if (arr[i] >= 'a' && arr[i] <= 'z')
				(*sizesmall)++;
	}
	*big = (char*)calloc(*sizebig,1);
	*small = (char*)calloc(*sizesmall,1);
	assert(big);assert(small);
	for (i = 0,*sizebig=0,*sizesmall=0; i < size; i++)
	{
		if (arr[i] >= 'A' && arr[i] <= 'Z')
			(*big)[(*sizebig)++] = arr[i];
		else
			if(arr[i] >='a' && arr[i] <= 'z')
		     	(*small)[(*sizesmall)++] = arr[i];
	}
	
	//במיין
	/*char a[5] = { 'a','B','c','D','e' };
	char* big1;char* small1;
	int bigsize, smallsize;
	charssplit(a, 5, &big1, &bigsize, &small1, &smallsize);
	printArrChar(big1, bigsize);
	printArrChar(small1, smallsize);
	free(big1);free(small1);*/
}

//מעבדת כיתה 1
//שאלה 3
void strsplit(char* str, char** big, char** small)
{
	int i;int i_big = 0, i_small = 0;
	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			i_big++;
		else
			if (str[i] >= 'a' && str[i] <= 'z')
				i_small++;
	}

	(*big) = (char*)calloc((i_big+1),sizeof(char));
	(*small) = (char*)calloc((i_small+1),sizeof(char));
	assert(big);assert(small);
	for (i = 0, i_big=0, i_small=0; i < strlen(str); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			(*big)[i_big++] = str[i];
		else
			if (str[i] >= 'a' && str[i] <= 'z')
				(*small)[i_small++] = str[i];
	}
	(*big)[i_big] = '\0';
	(*small)[i_small] = '\0';

	//במיין
	/*char str[5] = "heLlo";
	char* big;
	char* small;
	strsplit(str, &big, &small);
	printf("%s \n", big);
	printf("%s", small);*/
}

//מעבדת כיתה 1
//שאלה 4, א
int* removeDupPointer(int* arr, int size, int* newsize)
{
	int i;int* newarr;*newsize=1;int index = 1;
	for (i = 1; i < size; i++)
	{
		if (arr[i] != arr[i - 1])
			(*newsize)++;
	}

	newarr = (int*)calloc((*newsize), sizeof(int));
	assert(newarr);
	newarr[0] = arr[0];
	for ( i = 1; i < size; i++)
	{
		if (arr[i] != arr[i - 1])
			newarr[index++] = arr[i];
	}
	return newarr;
}

//מעבדת כיתה 1
//שאלה 4, ב
int removeDupSize(int* arr, int size, int** newarr)
{
	int i,newsize=1,index=1;
	
	for (i = 1; i < size; i++)
	{
		if (arr[i] != arr[i - 1])
			newsize++;
	}
	(*newarr) = (int*)malloc(newsize * sizeof(int));
	(*newarr)[0] = arr[0];
	for ( i = 1; i < size; i++)
	{
		if (arr[i] != arr[i - 1])
			(*newarr)[index++] = arr[i];
	}
	/*free(arr);*/
	return newsize;
}

//מעבדת כיתה 1
//שאלה 4,ג
void removeDup(int* arr, int size,int** newarr,int* newsize)
{
	*newsize = 1;int index = 1;
	int i;
	for ( i = 1; i < size; i++)
	{
		if (arr[i] != arr[i - 1])
			(*newsize)++;
	}
	*newarr = (int*)malloc((*newsize) * sizeof(int));
	(*newarr)[0] = arr[0];
	for ( i = 1; i < size; i++)
	{
		if (arr[i] != arr[i - 1])
			*newarr[index++] = arr[i];
	}



}

//מעבדת כיתה 1
//שאלה 1 ראילוק
int* zogiandizogiRealloc(int* arr, int size, int** arrodd, int* sizezogi, int* sizeizogi)
{
	*sizezogi = 0, * sizeizogi = 0;
	int i;
	int* arreven = NULL;
	for (i = 0; i < size; i++)
	{
		if (arr[i] % 2 == 0)
		{
			(*sizezogi)++;
			arreven = (int*)realloc(arreven, (*sizezogi) * sizeof(int));
			arreven[(*sizezogi) - 1] = arr[i];
		}
		else if (arr[i] % 2 != 0)
		{
			(*sizeizogi)++;
			*arrodd = (int*)realloc(*arrodd, (*sizeizogi) * sizeof(int));
			(*arrodd)[(*sizeizogi) - 1] = arr[i];
		}

	}
	return arreven;

	//במיין
	/*int a[6] = { 1,2,3,4,5,6 };
	int* arrodd = NULL;
	int seven, sodd;
	int* arreven = zogiandizogiRealloc(&a, 6, &arrodd, &seven, &sodd);
	printArrInt(arreven, seven);
	printArrInt(arrodd, sodd);*/

}

//שאלה 2 ריאלוק
void charssplitRealloc(char* arr, int size, char** big, int* sizebig, char** small, int* sizesmall)
{
	int i;*big = NULL;*small = NULL;
	*sizebig = 0;*sizesmall = 0;
	for ( i = 0; i < size; i++)
	{
		if (arr[i] >= 'A' && arr[i] <= 'Z')
		{
			(*sizebig)++;
			*big = (char*)realloc(*big, (*sizebig));
			(*big)[(*sizebig) - 1] = arr[i];
		}
		else if (arr[i] >= 'a' && arr[i] <= 'z')
		{
			(*sizesmall)++;
			*small = (char*)realloc(*small, (*sizesmall));
			(*small)[(*sizesmall) - 1] = arr[i];
		}
	}

	//במיין
	/*char a[6] = { 'a','A','B','c','g','r' };
	char* arrbig;
	int sbig, ssmall;
	char* arrsmall;
	charssplitRealloc(&a, 6, &arrbig, &sbig, &arrsmall, &ssmall);
	printArrChar(arrbig, sbig);
	printArrChar(arrsmall, ssmall);*/
}

//שאלה 3 ריאלוק
void strsplitRealloc(char* str, char** big, char** small)
{
	*big = NULL;*small = NULL;
	int i=0,index_big=0,index_small=0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			index_big++;
			*big = (char*)realloc(*big, index_big);
			(*big)[index_big - 1] = str[i];
		}
		else if (str[i] >= 'a' && str[i] <= 'z')
		{
			index_small++;
			*small = (char*)realloc(*small, index_small);
			(*small)[index_small - 1] = str[i];
		}
		i++;
	}
	*big = (char*)realloc(*big, index_big + 1);
	*small = (char*)realloc(*small, index_small + 1);
	(*big)[index_big] = '\0';
	(*small)[index_small] = '\0';

	//במיין
	//char str[] = "abcDAC";
	//char* strbig;char* strsmall;
	//strsplitRealloc(&str, &strbig, &strsmall);
	//printf("big: %s\nsmall: %s", strbig, strsmall);

}

