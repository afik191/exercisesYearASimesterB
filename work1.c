

#define _CRT_SECURE_NO_WARNINGS

/* Libraries */

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

/* Constant definitions */

#define N 3

/* Function declarations */

void Ex1();
void Ex2();
void Ex3();

char** split(char letter, char* str, int* p_size);
void createFile(char* filename);
char commonestLetter(char* filename);
void decode(char* text);

/* Declarations of auxiliary functions */

void printStringsArray(char** str_arr, int size);
void freeMatrix(void** A, int rows);

/* ------------------------------- */

int main()
{
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
	/* Called functions:
		split, printStringsArray, freeMatrix */

	char str[100],letter;
	printf("write a sentence please O_o\n");
	rewind(stdin);
	gets_s(str, 100);
	printf("write a letter\n");
	scanf_s("%c", &letter);
	int size;
	char** mat= split(letter, str, &size);
	printf("-----------\n");
	printStringsArray(mat, size);
	printf("-----------\n");
	freeMatrix(mat, size);
}

void Ex2()
{
	/* Called functions:
		createFile, commonestLetter */
		
	char* path = "input.txt";
	createFile(path);
    char str = commonestLetter(path);
 	printf("the most common letter is: %c\n", str);
}

void Ex3()
{
	/* Called functions:
		decode */

	char str[] = "Btwlzx Dqqes Eq|pj2 Tjhvqujs Iqoqjy bpg Eqfxtx Xcwwtt";
	decode(str);
	printf("%s", str);
}

char** split(char letter, char* str, int* p_size) 
//checks how many words in the string starts with a given letter and creates matrix to present them
{                                                 
	if (isupper(letter)) //making sure the letter is in lower case
		tolower(letter);
	int i=1, j=0,len=strlen(str);
	*p_size = 0;
	char** mat_words; 

	//counting the number of rows
	if (str[0] == letter || str[0] == letter-('a'-'A')) //in case the first word starts with the given letter
			(*p_size)++;
	while (str[i] != '\0') 
	{
		if (str[i-1] == ' ' && (str[i] == letter || str[i] == letter - ('a'-'A')))
			(*p_size)++;
		i++;
	}
	mat_words = (char**)malloc((*p_size) * sizeof(char*));//allocate rows array
	if (mat_words == NULL)
		return NULL;
	*p_size = 0;
	i = 0;
	//creating the columns
	while (i < len) {
		if (i == 0 && tolower(str[i]) == letter || (i > 0 && str[i - 1] == ' ' && tolower(str[i]) == letter)) {
			j = i;
			while (j < len && str[j] != ' ') {
				j++;
			}
			int word_length = j - i;
			mat_words[*p_size] = (char*)malloc((word_length + 1) * sizeof(char)); //allocate column
			if (mat_words[*p_size] == NULL) {
				freeMatrix(mat_words, *p_size);//if allocation failed, free matrix
				return NULL;
			}
			strncpy(mat_words[*p_size], &str[i], word_length);//inserts the word into the current array
			mat_words[*p_size][word_length] = '\0';
			(*p_size)++;
			i = j;
		}
		i++;
	}
	return mat_words;
}

void createFile(char* filename)
{ //creates a new file and inserts input from user
	int i = 0;
	FILE* f = fopen(filename, "w");//opens a new file
	if (f == NULL)
		return NULL;
	char ch[150];
	rewind(stdin);
	printf("write a sentence,to stop: press enter ctrl-z and then enter\n");
	while (fgets(ch, 150,stdin) != NULL) //recives sentences from user until ctrl-z + enter
		fputs(ch, f);
	rewind(stdin);
	fclose(f);
}
char commonestLetter(char* filename)
{ // checks which letter is the most abundent and returns the upper case version of it

	FILE* f = fopen(filename, "r");//opens file
	if (f==NULL)
		return NULL;
	int i,biggest=0,index=0,abc[26] = { 0 };
	char ch;
	while ((ch=tolower(fgetc(f))) != EOF)//counts every letter in the abc
	{
		abc[ch - 'a']++;
	}
	fclose(f); //closing the file as we don't need to access it anymore
	for ( i = 0; i < 26; i++)// search for the most abundent letter
	{
		if (abc[i] >= biggest)
		{
			biggest = abc[i];
			index = i;
		}
	}
	return index + 'A';
}

void decode(char* text)
{   //decodes text by their ascii value per position in a word
	int i = 0, pos = 1;
	while (text[i] !='\0')
	{ 
		
		if (text[i] != ' ') // decode a word by it's position
		{ 
			text[i] = text[i] - pos; 
			i++;
			pos++;
		}
		else //initialize a new word
		{
			i++;
			pos = 1;
		}
	}
}

/* Definitions of auxiliary functions */

//prints string matrix
void printStringsArray(char** str_arr, int size) { 
	printf("Number of words: %d\n", size);
	for (int i = 0; i < size; i++) {
		printf("%s\n", str_arr[i]);
	}
}

//clear memory
void freeMatrix(void** A, int rows)
{
	for (int i = 0; i < rows; i++) {
		free(A[i]);
	}
	free(A);
}

/* Write Definitions Here! */


/* ------------------- */
