#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    char id[10];
	char name[31];
	double total;
}item;

void main25()
{
    
}




void add_item(char* filename)
{
	FILE* f = fopen(filename, "r+");
	if (!f)
		return;
	item m;
	fread(&m, sizeof(m), 1, f);
	while (!feof(f))
	{
		if(strcmp()
	}



}