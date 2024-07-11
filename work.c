

#define _CRT_SECURE_NO_WARNINGS

/* Libraries */
#include<stdio.h>
#include<stdlib.h>

/* Constant definitions */
#define N 3
#define ROWS 4
#define COLS 5

/* Type definitions */
typedef struct Number
{
    unsigned long long num;
    int sum;
} Number;

typedef struct triad
{
    int i, j, value;
} Triad;

typedef struct item
{
    Triad data;
    struct item* next;
} Item;

/* Function declarations */
void Ex1();
void Ex2();
void Ex3();

Number* primeSums(unsigned long long n1, unsigned long long n2, int* p_size);
int** matrixMaxNeighbor(int A[][COLS], int rows, int cols);
void createThreeLists(int** A, int rows, int cols, Item** pL1, Item** pL2);

/* Declarations of auxiliary functions */
int isPrime(int n);
int digitSum(unsigned long long num);

int neighborMax(int A[][COLS], int rows, int cols, int i, int j);
int** alloc_matrix(int rows, int cols);

Triad createThree(int i, int j, int value);

/* rest of the auxiliary functions*/
void printArray(Number* nums, int size);
void free_matrix(void** c, int n);
void print_dyn_matrix(int** a, int rows, int cols);
void printMatrix(int A[][COLS], int rows, int cols);
void inputMatrix(int A[][COLS], int rows, int cols);
void printList(Item* head);
Item* Insert(Triad* t);
void inputDynamicMatrix(int** A, int rows, int cols);
void freeList(Item* lst);

/* ------------------------------- */

int main20() {
    int select = 0, i, all_Ex_in_loop = 0;
    printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
    if (scanf("%d", &all_Ex_in_loop) == 1)
        do
        {
            for (i = 1; i <= N; i++)
                printf("Ex%d--->%d\n", i, i);
            printf("EXIT-->0\n");
            do {
                select = 0;
                printf("please select 0-%d : ", N);
                scanf("%d", &select);
            } while ((select < 0) || (select > N));
            switch (select)
            {
            case 1: Ex1(); break;
            case 2: Ex2(); break;
            case 3: Ex3(); break;
            }
        } while (all_Ex_in_loop && select);
        return 0;
}

/* Function definitions */

void Ex1()
{
    /* Called functions: primeSums, printArray, free */

    //input numbers and creates array of prime sums of numbers in domain ,and prints
    unsigned long long n1, n2;
    int ArraySize = 0;
    printf("enter 2 numbers n1, and n2. make sure n2>n1\n");
    printf("Enter n1: ");
    scanf_s("%llu", &n1);
    printf("Enter n2: ");
    scanf_s("%llu", &n2);
    Number* Sum_Array = primeSums(n1, n2, &ArraySize);
    printArray(Sum_Array, ArraySize);
    printf("the size of the array is:%d\n", ArraySize);
    free(Sum_Array); //free memory
}

void Ex2()
{
    /* Called functions: inputMatrix, printMatrix, matrixMaxNeighbor, printDynamicMatrix, freeMatrix */

    //Matrix input, output, neighbor max, and free memory.
    int matrix[ROWS][COLS];
    inputMatrix(matrix, ROWS, COLS);
    printMatrix(matrix, ROWS, COLS);
    int** m = matrixMaxNeighbor(matrix, ROWS, COLS);
    print_dyn_matrix(m, ROWS, COLS);
    free_matrix(m, ROWS);//freeing the space
}

void Ex3()
{
    /* Called functions: allocMatrix, inputDynamicMatrix, printDynamicMatrix,
    createThreeLists, printList, freeMatrix, freeList */

    //Allocates, processes, prints, and frees matrix and lists
    int** m;
    Item* p1, * p2;
    m = alloc_matrix(ROWS, COLS);
    inputDynamicMatrix(m, ROWS, COLS);
    print_dyn_matrix(m, ROWS, COLS);
    createThreeLists(m, ROWS, COLS, &p1, &p2);
    printList(p1);//displaying the created lists
    printList(p2);
    free_matrix(m, ROWS); //freeing the space
    freeList(p1);
    freeList(p2);
}

Number* primeSums(unsigned long long n1, unsigned long long n2, int* p_size)
{
    /* Called functions: isPrime, digitSum */

    *p_size = 0;
    if (n2 < n1) //stop condition, no need to check negativity because it's unsigned
        return NULL;

    int i, index = 0, temp_sum = 0;
    Number* nums = (Number*)calloc(1, sizeof(Number));// Allocate memory for the array of Numbers
    if (!nums)
        return NULL;
    *p_size = 1;
    for (i = n1; i <= n2; i++)
    {
        temp_sum = digitSum(i);//calculate sum of digits for current number
        if (isPrime(temp_sum) == 1)//checks if the sum of digits is prime(1=prime,0 not prime)
        {// Check if index is within the allocated size
            if (index < *p_size)
            {// Store the number and its sum of digits in the array
                nums[index].num = i;
                nums[index].sum = temp_sum;
                index++;
            }
            else
            {// If index exceeds allocated size, resize the array
                (*p_size) *= 2;
                nums = (Number*)realloc(nums, (*p_size) * sizeof(Number));
                if (!nums)
                {
                    *p_size = 0;
                    return NULL;
                }
                // Store the number and its sum of digits in the resized array
                nums[index].num = i;
                nums[index].sum = temp_sum;
                index++;

            }
        }
    }
    *p_size = index;// Update p_size with the actual size of the array
    // Resize the array to the actual size
    nums = (Number*)realloc(nums, (*p_size) * sizeof(Number));
    if (!nums)
    {
        *p_size = 0;
        return NULL;
    }
    return nums;
}

int** matrixMaxNeighbor(int A[][COLS], int rows, int cols)
{
    /* Called functions: neighborMax, allocMatrix */

    //allocate a new matrix and inserts values into it according to the max neighbor
    int** B = alloc_matrix(rows, cols);
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {// Compute the max neighbor value for each element
            B[i][j] = neighborMax(A, rows, cols, i, j);
        }
    }
    return B;
}

void createThreeLists(int** A, int rows, int cols, Item** pL1, Item** pL2)
{
    /* Called functions: createThree, insert */

    *pL1 = *pL2 = NULL;
    int i, j;
    Triad temp;
    Item* cur1 = *pL1, * cur2 = *pL2, * new_item; //so we wont destroy the original lists

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (A[i][j] == i + j)//list 1=row number+column number=value
            {//if fits into category of list 1 insert into it
                temp = createThree(i, j, A[i][j]);
                new_item = Insert(&temp);
                if (*pL1 == NULL) {
                    *pL1 = new_item; // Initialize head of list 1
                    cur1 = new_item;
                }
                else {
                    cur1->next = new_item; // Link new item to list 1
                    cur1 = cur1->next;
                }
            }
            if (abs(i - j) == abs(A[i][j] - j))//list 2=row number,column number and value create a Invoice series
            {//if fits into category of list 2 insert into it
                temp = createThree(i, j, A[i][j]);
                new_item = Insert(&temp);
                if (*pL2 == NULL) {
                    *pL2 = new_item;  // Initialize head of list 2
                    cur2 = new_item;
                }
                else {
                    cur2->next = new_item;  // Link new item to list 2
                    cur2 = cur2->next;
                }
            }
        }
    }

}

/* Definitions of auxiliary functions */

void inputDynamicMatrix(int** A, int rows, int cols)
{  // Input values into the a dynamic matrix
    printf("Enter the values for the matrix (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Enter value for matrix[%d][%d]: ", i, j);
            scanf_s("%d", &A[i][j]);
        }
    }
}

void inputMatrix(int A[][COLS], int rows, int cols)
{// Input values into the matrix
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("Enter value for matrix[%d][%d]: ", i, j);
            scanf_s("%d", &A[i][j]);
        }
        printf("\n");
    }

}

void printMatrix(int A[][COLS], int rows, int cols)
{//print values of the matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void print_dyn_matrix(int** a, int rows, int cols)
{//print values of the dynamic matrix
    int i, j;
    printf("the dynamic matrix:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
            printf("%5d", a[i][j]);
        printf("\n");
    }
}

int isPrime(int n)
{//checks if the number is prime. if so returns 1, if not 0.
    if (n <= 1)
        return 0;
    if (n <= 3)
        return 1;
    if (n % 2 == 0 || n % 3 == 0)
        return 0;
    //Check for factors from 5 to sqrt(n)
    //Only check factors of the form 6k +/- 1
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)//i=6k-1, i+2=6k+1
            return 0;
    }
    return 1;
}

int digitSum(unsigned long long num)
{//Returns the sum of the digits of a number.
    int sum = 0;
    while (num != 0)
    {
        sum += num % 10;
        num = num / 10;
    }
    return sum;
}

void printArray(Number* nums, int size)
{// Print the array of Number structs
    if (size <= 0)
        return;
    printf("Array of Numbers:\n");
    for (int i = 0; i < size; i++) {
        printf("Number: %llu, Digit Sum: %d\n", nums[i].num, nums[i].sum);
    }
}

int** alloc_matrix(int rows, int cols)
{//creating dynamically a matrix 
    int** c, i;
    c = (int**)calloc(rows, sizeof(int*));
    if (!c)
        return NULL;
    for (i = 0; i < rows; i++)
    {
        c[i] = (int*)calloc(cols, sizeof(int));
        if (!c[i])//if the process failed clear the memory
        {
            free_matrix(c, i);
            return NULL;
        }
    }
    return c;
}

int neighborMax(int A[][COLS], int rows, int cols, int i, int j)
{//return the max value among the neighbor values in a matrix
 //each if checks if the row/column exists before proceeding
    int max = 0;
    if (i + 1 < rows && A[i + 1][j] > max) //bottom neighbor
        max = A[i + 1][j];
    if (j + 1 < cols && A[i][j + 1] > max) //right neighbor
        max = A[i][j + 1];
    if (i - 1 >= 0 && A[i - 1][j] > max) //top neighbor
        max = A[i - 1][j];
    if (j - 1 >= 0 && A[i][j - 1] > max) //left neighbor
        max = A[i][j - 1];
    return max;
}

void free_matrix(void** c, int n)
{//free a matrix from memory
    int i;
    for (i = 0; i < n; i++)
        free(c[i]);
    free(c);
}

Triad createThree(int i, int j, int value)
{ //Initializes and returns a Triad with given values.
    Triad t;
    t.i = i;
    t.j = j;
    t.value = value;
    return t;
}

Item* Insert(Triad* t)
{//inserts a triad as data into linked list
    Item* new_item = (Item*)malloc(sizeof(Item));
    if (!new_item)
        return NULL;
    new_item->data = createThree(t->i, t->j, t->value);
    new_item->next = NULL;
    return new_item;
}

void printList(Item* head)
{//Prints the elements of a linked list of Items in Triad format.
    Item* cur = head;
    while (cur != NULL)
    {
        printf("(%d,%d,%d)->", cur->data.i, cur->data.j, cur->data.value);
        if (cur->next != NULL)
            cur = cur->next;
        else//at the end of the list
        {
            printf("NULL\n");
            break;
        }
    }
}

void freeList(Item* lst)
{// free a linked list from memory
    Item* temp;
    while (lst != NULL) {
        temp = lst;
        lst = lst->next;
        free(temp);
    }
}

/* ------------------- */