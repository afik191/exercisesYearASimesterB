#include <stdio.h> 
#include <string.h> 
#include<ctype.h>
#include<stdlib.h>


typedef struct
{
	int i, j;
}pair;

typedef struct car {
	char model[20];
	int price;
	int year;
} car;

typedef struct ls
{
	car data;
	struct ls* next;
}item;


int classifyString(char* str, int* low, int* up);
item* appropriateCar(char* filename, char* desired_model, int max_price, int min_year);
pair* friends(int** mat, int size, int* new_size);

void main1()
{
	

	
}

//Q1
int classifyString(char* str, int* low, int* up)
{
	*low = *up = 0;
	int size = strlen(str),i;
	for ( i = 0; i < size/2; i++)
		if(islower(str[i]))
			(*low)++;
	for (i = (size + 1) / 2; i < str[i] != '\0'; i++)
		if (isupper(str[i]))
			(*up)++;
	if (size % 2 == 0)
		return 0;
	if (isdigit(str[size / 2]))
		return 1;
	return -1;
	//main
	/*
	int low, up;
	char* s = "t&u5Y%4as3k$R";
	int a = classifyString(s, &low, &up);
	*/
}

//Q2


pair* friends(int** mat, int size, int* new_size)
{
	int i,j,k,count=0;
	*new_size = (size * size - size) / 2;
	pair* arr = (pair*)calloc(*new_size,sizeof(pair));
	for ( i = 0; i < size; i++)
	    for ( j = 0; j < i; j++)
		    if (mat[i][j] == 0)
			   for ( k = 0; k < size; k++)
				    if (mat[i][k] == 1 && mat[j][k] == 1)
					{
						arr[count].i = i;
						arr[count++].j = j;
						break;
					}	
	*new_size = count;
	arr = (pair*)realloc(arr, (*new_size)*sizeof(pair));
	return arr;
}

//Q3


item* appropriateCar(char* filename, char* desired_model, int max_price, int min_year)
{
	FILE* f = fopen(filename, "rb");
	if (!f)
		return NULL;
	item* list, * cur;
	list = cur = (item*)malloc(sizeof(item)); // dummy
	car unit;
	fread(&unit, sizeof(car), 1, f);
	while (!feof(f))
	{
		if (strcmp(unit.model,desired_model) == 0 && unit.price<=max_price  
			&& unit.year>=min_year)
		{
			cur->next = (item*)malloc(sizeof(item));
			cur = cur->next;
			cur->data.price = unit.price;
			cur->data.year = unit.year;
		}
		fread(&unit, sizeof(car), 1, f);
	}
	cur->next = NULL;
	//delete dummy
	cur = list;
	list = list->next;
	free(cur);

	fclose(f);
	return list;

	//main
	/*car c1 = { "subaru",90000,2019 };
	car c2 = { "mazda",95000,2020 };
	car c3 = { "subaru",10000,2009 };
	car c4 = { "toyota",200000,2022 };
	car c5 = { "subaru",25000,2012 };
	FILE* cfPtr = fopen("credit.dat", "wb");
	if (cfPtr == NULL)
		printf("File could not be opened.\n");
	fwrite(&c1, sizeof(car), 1, cfPtr);
	fwrite(&c2, sizeof(car), 1, cfPtr);
	fwrite(&c3, sizeof(car), 1, cfPtr);
	fwrite(&c4, sizeof(car), 1, cfPtr);
	fwrite(&c5, sizeof(car), 1, cfPtr);
	fclose(cfPtr);
	item* t = appropriateCar("credit.dat", "subaru", 100000, 2010);
	*/
}