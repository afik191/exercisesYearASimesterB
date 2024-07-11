#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct monom {
	double coeffiecient;
	int power;
}Monom;
typedef struct item {
	Monom mon;
	struct item* next;
}Item;

Item* createPolynom(Item* L);
void printPolynom(Item* L);
void freePolynom(Item* L);
void sortedRowsCols(int** ar, int m, int n, int** ar_s_rows, int* num_s_rows, int** ar_s_cols, int* num_s_cols);
void ReallocSortedRowsCols(int** ar, int m, int n, int** ar_s_rows, int* num_s_rows, int** ar_s_cols, int*
	num_s_cols);
int arrSorted(int* a, int n);//return 1 if sorted upwards,else 0
int columnSorted(int** ar, int m, int col);//return 1 if sorted downwards,else 0
char* nextWord(char* sentence, char* seperators, char* word);
int exA();
int exB();
int breakSentence(char* sentence, char* separators, char* file_name);
int countWordOccur(char* sentence, char* separators, char* query);


void main2() {
	


}
Item* createPolynom(Item* L) {
	Item* curr = L, * new_list = (Item*)malloc(sizeof(Item));//creating first in the list
	if (new_list == NULL) {
		return NULL;
	}
	int max = curr->mon.power, i;
	curr = curr->next;
	while (curr != NULL) {
		if (curr->mon.power >= max)
			max = curr->mon.power;
		curr = curr->next;
	}
	int* count = (int*)calloc(max + 1, sizeof(int));//counter array
	if (count == NULL)
		return NULL;
	curr = L;
	while (curr != NULL) {//adding values to counter array
		count[curr->mon.power] += curr->mon.coeffiecient;
		curr = curr->next;
	}
	curr = new_list;
	for (i = max; i >= 0; i--) {//adding values to the new list
		if (count[i] != 0)
		{
			curr->next = (Item*)malloc(sizeof(Item));//creating the next node in the list
			if (curr->next == NULL) {
				return NULL;
			}
			curr = curr->next;

			curr->mon.coeffiecient = count[i];
			curr->mon.power = i;
		}
	}
	curr->next = NULL;
	curr = new_list; //free storage
	new_list = new_list->next;
	free(curr);
	free(count);
	return new_list;

	//main
	// Create a sample polynomial linked list: 3x^2 + 4x^5 + x^2 + 2x^5
	//Item* poly = (Item*)malloc(sizeof(Item));
	//poly->mon.coeffiecient = 3;
	//poly->mon.power = 2;
	//poly->next = (Item*)malloc(sizeof(Item));
	//poly->next->mon.coeffiecient = 4;
	//poly->next->mon.power = 5;
	//poly->next->next = (Item*)malloc(sizeof(Item));
	//poly->next->next->mon.coeffiecient = 1;
	//poly->next->next->mon.power = 2;
	//poly->next->next->next = (Item*)malloc(sizeof(Item));
	//poly->next->next->next->mon.coeffiecient = 2;
	//poly->next->next->next->mon.power = 5;
	//poly->next->next->next->next = NULL;

	//printf("Original polynomial: ");
	//printPolynom(poly);

	//Item* combinedPoly = createPolynom(poly);

	//printf("Combined polynomial: ");
	//printPolynom(combinedPoly);

	//// Free memory
	//freePolynom(poly);
	//freePolynom(combinedPoly);
}
void printPolynom(Item* L) {
	Item* curr = L;
	while (curr != NULL) {
		printf("%+.2fx^%d ", curr->mon.coeffiecient, curr->mon.power);
		curr = curr->next;
	}
	printf("\n");
}

void freePolynom(Item* L) {
	Item* temp;
	while (L != NULL) {
		temp = L;
		L = L->next;
		free(temp);
	}
}



void sortedRowsCols(int** ar, int m, int n, int** ar_s_rows, int* num_s_rows, int** ar_s_cols, int* num_s_cols) {
	// i wanted realloc but those kiddos told me not to
	//they told me i was outnumbered so i caved
	int i, j;
	*num_s_cols = 0;
	*num_s_rows = 0;
	for (i = 0; i < m; i++) {//rows
		if (arrSorted(num_s_rows[i], m))
			(*num_s_rows)++;
	}
	*ar_s_rows = (int*)calloc(*num_s_rows, sizeof(int));
	if (ar_s_rows == NULL)
		return NULL;
	(*num_s_rows) = 0;
	for (i = 0; i < m; i++) {
		if (arrSorted(num_s_rows[i], m))
		{
			*ar_s_rows[(*num_s_rows)++] = i;
		}
	}
	for (i = 0; i < n; i++) {//cols
		if (columnSorted(ar, n, i))
			(*num_s_cols)++;
	}
	*ar_s_cols = (int*)calloc(*num_s_cols, sizeof(int));
	if (ar_s_cols == NULL)
		return NULL;
	*num_s_cols = 0;
	for (i = 0; i < n; i++) {
		if (columnSorted(ar, n, i))
			ar_s_cols[(*num_s_cols)++];
	}
}
void ReallocSortedRowsCols(int** ar, int m, int n, int** ar_s_rows, int* num_s_rows, int** ar_s_cols, int*
	num_s_cols)
{
	int i, j;
	*num_s_rows = *num_s_cols = 0;
	*ar_s_rows = (int*)calloc(m, sizeof(int)); // max size - number of rows
	*ar_s_cols = (int*)calloc(n, sizeof(int)); // max size - number of columns
	for (i = 0; i < m; i++)
		if (arrSorted(ar[i], n))
			(*ar_s_rows)[(*num_s_rows)++] = i;
	for (j = 0; j < n; j++)
		if (columnSorted(ar, m, j))
			(*ar_s_cols)[(*num_s_cols)++] = j;
	*ar_s_rows = (int*)realloc(*ar_s_rows, *num_s_rows * sizeof(int));
	*ar_s_cols = (int*)realloc(*ar_s_cols, *num_s_cols * sizeof(int));
}
int arrSorted(int* a, int n) {
	for (int i = 1; i < n; i++) {
		if (a[i] < a[i - 1]) {
			return 0; // Not sorted in ascending order
		}
	}
	return 1; // Sorted in ascending order
}

int columnSorted(int** ar, int m, int col) {
	for (int i = 1; i < m; i++) {
		if (ar[i][col] > ar[i - 1][col]) {
			return 0; // Not sorted in descending order
		}
	}
	return 1; // Sorted in descending order
}


int countWordOccur(char* sentence, char* separators, char* query) {
	char* word = (char*)malloc(strlen(sentence) + 1); //create space for each word
	if (word == NULL)
		return -1; //if allocation failed
	int count = 0;
	while (sentence = nextWord(sentence, separators, word) != NULL) {//find the word
		if (strcmp(word, query) == 0)//return 0 if same
			count++;
	}
	if (strcmp(word, query) == 0)//if something is left
		count++;
	free(word); //clear storage
	return count;
}
int exB() {
	char sentence[] = "But why?! That’s why.";
	char separators[] = "? !.";
	char file_name[] = "output.txt";

	int word_count = breakSentence(sentence, separators, file_name);
	if (word_count == -1) {
		printf("An error occurred.\n");
	}
	else {
		printf("The sentence was split into %d words.\n", word_count);
		printf("The words have been written to the file '%s'.\n", file_name);
	}

	return 0;
}
int breakSentence(char* sentence, char* separators, char* file_name) {
	FILE* f = fopen(file_name, "w");
	if (!f)
		return -1; //if open failed
	char* word = (char*)malloc(strlen(sentence) + 1);
	if (word == NULL)
		return -1; //if allocation failed
	int count = 0;
	while (sentence = nextWord(sentence, separators, word) != NULL) {
		fprintf(f, "%s\n", word);
		count++;
	}
	if (*word) {//if something was left
		fprintf(f, "%s\n", word);
		count++;
	}
	free(word);
	fclose(f);
	return count;
}
char* nextWord(char* sentence, char* seperators, char* word) {
	//recieves an array of seperators and return the first word until the first seperator
	int i = 0;
	while (sentence[i] && !strchr(seperators, sentence[i])) {
		word[i] = sentence[i]; //updates the word to the first one
		i++;
	}
	while (sentence[i] && strchr(seperators, sentence[i])) {
		i++;
	}
	if (sentence[i])
		return sentence + i; //returns the location of the next word
	else
		return NULL;
}
int exA() {
	char sentence[] = "Why?! That's why.";
	char separators[] = "?!.";
	char word[12];
	char* next = sentence;

	printf("Sentence: %s\n", sentence);
	printf("Words:\n");

	while (next != NULL) {
		next = nextWord(next, separators, word);
		if (strlen(word) > 0) { // Check if a word was found
			printf("%s\n", word);
		}
	}

	return 0;
}