#include <stdio.h>
#include<stdlib.h>
#include <assert.h>
#include<string.h>



typedef struct Complex
{
	double real;
	double img;
} complex;

typedef struct
{
	char address[30];
	int rooms;
	double price;
} apartment;

void inputComplex(complex* c);
void printComplex(complex c);
complex sumComplex(complex c1, complex c2);
complex minusComplex(complex c1, complex c2);
complex timesComplex(complex c1, complex c2);
apartment* chosenAparts(apartment* apart_units, int size, int wanted_rooms, double max_price);

void main3()
{
	apartment ap[3] = { {"a",3,100},{"b",4,200},{"c",5,600} };
	apartment* aa = chosenAparts(ap, 3, 4, 201);
	for (int i = 0; i < 1; i++)
	{
		printf("%s,%d,%.2f", aa[i].address, aa[i].rooms, aa[i].price);
	}

}


void inputComplex(complex* c)
{
	printf("write real form\n");
	scanf_s("%lf", &(c->real));
	printf("write img form\n");
	scanf_s("%lf", &(c->img));
	printf("\n");
}

void printComplex(complex c)
{
    if(c.img>0)
         printf("%.2f+%.2fi\n",c.real,c.img);
    else
        printf("%.2f%.2fi\n", c.real, c.img);
	
}

complex sumComplex(complex c1, complex c2)
{
	complex c3;
	c3.real = c1.real + c2.real;
	c3.img = c1.img + c2.img;
	return c3;
}

complex minusComplex(complex c1, complex c2)
{
	complex c3;
	c3.real = c1.real - c2.real;
	c3.img = c1.img - c2.img;
	return c3;
}

complex timesComplex(complex c1, complex c2)
{
	complex c3;
	c3.real = c1.real * c2.real - (c1.img * c2.img);
	c3.img = c1.real * c2.img + c1.img * c2.real;
	return c3;
}

apartment* chosenAparts(apartment* apart_units, int size, int wanted_rooms, double max_price)
{
	int i,new_size=0;
	apartment* new_aparts;
	for ( i = 0; i < size; i++)
	{
		if (apart_units[i].rooms == wanted_rooms && apart_units[i].price <= max_price)
			new_size++;
	}
	new_aparts = (apartment*)malloc(new_size * sizeof(apartment));
	if (new_aparts == NULL)
	{
		return new_aparts;
	}
	new_size = 0;
	for (i = 0; i < size; i++)
	{
		if (apart_units[i].rooms == wanted_rooms && apart_units[i].price <= max_price)
		{
			new_aparts[new_size++] = apart_units[i];
		}
	}
	
	return new_aparts;
}