#include <stdio.h> 
#include <string.h> 
#include<ctype.h>
#include<stdlib.h>
#include<math.h>

#define _CRT_SECURE_NO_WARNINGS

typedef struct nums
{
    int num;
    struct nums* next;
}list_nums;

typedef struct {
    char address[30];
    int rooms;
    int price;
} apartment;

char* duplicateString(char* base, int times, char* middle);
void List_num_add(list_nums** ls, int n);

void main4()
{
    
   
}

//Q1
char* duplicateString(char* base, int times, char* middle)
{
    int size_base = strlen(base);
    int size_middle = strlen(middle);
    int size_all = (times * size_base) + ((times - 1) * size_middle) + 1; // +1 for null terminator
    char* new_str = (char*)calloc(size_all, sizeof(char));
    errno_t err;

    if (new_str == NULL) {
        // Allocation failed
        return NULL;
    }

    for (int i = 0; i < times; i++) {
        err = strcat_s(new_str, size_all, base);
        if (err != 0) {
            free(new_str);
            return NULL;
        }
        if (i < times - 1) {
            err = strcat_s(new_str, size_all, middle);
            if (err != 0) {
                free(new_str);
                return NULL;
            }
        }
    }
    new_str[size_all] = '\0';
    return new_str;

    /*main
     char* destination = "hello";
     char* source = "-";
     int times = 3;
     char* a = duplicateString(destination, times, source);
    */
}
int count_digit(int n)
{
    int count = 0;
    while (n!=0)
    {
        ++count;
        n /= 10;
    }
    return count;
}

//Q2
void List_num_add(list_nums** ls,int n)
{
    list_nums* cur = *ls,*new_ls=(list_nums*)malloc(sizeof(list_nums));//dummy
    int number_add = 0,i;
    while (cur!=NULL)
    {
        number_add = (number_add*10) +cur->num ;
        cur = cur->next;
    }
    number_add += n;
    i = count_digit(number_add)-1;
    
    cur = new_ls;
    while (i>=0)
    {
        cur->next = (list_nums*)malloc(sizeof(list_nums));
        cur = cur->next;
        cur->num = number_add / pow(10, i);
        number_add = number_add % (int)pow(10,i);
        i--;
    }
    cur->next = NULL;
    cur = new_ls;
    new_ls = new_ls->next;
    free(cur); //delete dummy
    *ls = new_ls;

    /* main
      list_nums one,two,three,four;
    one.num = 9;
    two.num = 9;
    three.num = 9;
    four.num = 4;
    one.next=&two;
    two.next = &three;
    three.next = &four;
    four.next = NULL;
    list_nums* h = &one;
    List_num_add(&h, 18);
    */
}

//Q3
apartment* appropritateAppartment(char* filename, int room_number, int max_price,int* size)
{
    *size = 0;
    FILE* f = fopen(filename, "rb");
    if (!f)
        return NULL;
    apartment* app = NULL,unit;
    fread(&unit, sizeof(apartment), 1, f);
    while (!feof(f))
    {
        if (unit.price<=max_price && unit.rooms == room_number)
        {
            (*size)++;
            app = (apartment*)realloc(app, sizeof(apartment) * (*size));
            app[(*size) - 1] = unit;
        }
        fread(&unit, sizeof(apartment), 1, f);
    }
    fclose(f);
    if (*size == 0)
        return NULL;
    return app;
}