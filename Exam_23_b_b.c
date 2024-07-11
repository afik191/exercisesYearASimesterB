#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
	int value;
	struct node* next;
} node;

typedef struct {
	char film_code[10];
	int copies;
	int year;
} film;

node* JosephusPermutation(node* lst, int m);
void print_circ_list(node* head);
node* create_node(int value);
void print_list(node* head);
void insert_films_to_file(film films[], int num_films, const char* filename);
film* appropriateAppartment(char* fileName, int copies_limit, int last_year, int* size);
void print_films_arr(film* arr, int size);
char* my_strtok(char* sentence, char* separators);

void main3() {
	
}

void print_films_arr(film* arr,int size)
{
	int i;
	for ( i = 0; i < size; i++)
	{
		printf("[%s,%d,%d]\n", arr[i].film_code, arr[i].copies, arr[i].year);
	}

}
void print_list(node* head) {
	node* current = head;
	while (current != NULL) {
		printf("%d->", current->value);
		current = current->next;
	}
	printf("NULL\n");
	
}
node* create_node(int value) {
	node* new_node = (node*)malloc(sizeof(node));
	new_node->value = value;
	new_node->next = NULL;
	return new_node;
}
void print_circ_list(node* head) {
	if (head == NULL) return;
	node* current = head;
	do {
		printf("%d->", current->value);
		current = current->next;
	} while (current != head);
	printf("\n");
}
//Q1
node* JosephusPermutation(node* lst, int m)
{
	if (!lst)
		return NULL;
	node* new_lst = (node*)malloc(sizeof(node));//dummy
	node* cur=lst, * prev=lst,*cur_new=new_lst;
	int count = 0;
	while (lst!=NULL)
	{
		count++;
		if (count % m==0 )
		{
			cur_new->next = cur;
			cur_new = cur_new->next;
			prev->next = cur->next;
		}
		prev = cur;
		cur = cur->next;
		if (prev == cur)
		{
			cur_new->next = cur;
			cur_new = cur->next;
			cur_new->next = NULL;
			break;
		}
			
	}
	/*cur_new->next = NULL;*/
	cur_new = new_lst;
	new_lst = new_lst->next;
	free(cur_new); //free dummy
	return new_lst;

	/* main
	
	node* head = create_node(1);
	node* current = head;
	for (int i = 2; i <= 8; i++) {
		current->next = create_node(i);
		current = current->next;
	}
	current->next = head;
	print_circ_list(head);
	node* n = JosephusPermutation(head, 3);
	print_list(n);
	*/
}
//Q2
film* appropriateAppartment(char* fileName, int copies_limit,
	int last_year, int* size)
{
	*size = 0;
	FILE* f = fopen(fileName, "rb");
	if (!f)
		return NULL;
	film* films=NULL, movie;
	fread(&movie, sizeof(film), 1, f);
	while (!feof(f))
	{
		if (movie.copies <= copies_limit && movie.year <= last_year)
		{
			(*size)++;
			films = (film*)realloc(films, (*size) * sizeof(film));
			films[(*size) - 1] = movie;
		}
		fread(&movie, sizeof(film), 1, f);
	}
	fclose(f);
	return films;

	/* main
	film films[] = {
		{"A346-f", 2, 1967},
		{"D8120-fx", 4, 1960},
		{"S516-t", 1, 1970},
		{"R11-v", 2, 1972},
		{"G555-xx", 3, 201}
	};
	char* name = "films.bin";
	int num_films = sizeof(films) / sizeof(films[0]),size;
	film* f = appropriateAppartment(name, 2, 1970, &size);
	print_films_arr(f, size);
	*/
}

void insert_films_to_file(film films[], int num_films, const char* filename) {
	FILE* file = fopen(filename, "wb");
	if (file == NULL) {
		perror("Error opening file");
		return;
	}

	// Write each film struct to the file
	for (int i = 0; i < num_films; i++) {
		fwrite(&films[i], sizeof(film), 1, file);
	}

	fclose(file);
}
int is_sep(char* sep,char c)
{
	int i = 0;
	while (sep[i] !='\0')
	{
		if (c == sep[i])
			return 1;
	}
	return 0;
}
//Q3
char* my_strtok(char* sentence, char* separators)
{
	int i = 0;
	char* word;
	static char* start;
	if (sentence != NULL)
		start = sentence;
	word = (char*)malloc(strlen(start) + 1);
	while (*start && strchr(separators, *start)) // scan separators
		start++;
	while (*start && !strchr(separators, *start)) // scan word
	{
		word[i++] = *start;
		start++;
	}
	if (i > 0) // word was found
	{
		word[i] = '\0';
		word = (char*)realloc(word, i + 1);
		return word;
	}
	free(word);
	return NULL;

	/*main
	char* sent = "Why?! That’s why.";
	char* sep = "?!. :,",*get;
	get=my_strtok(sent, sep);
	get = my_strtok(NULL, sep);
	get = my_strtok(NULL, sep);
	get = my_strtok(NULL, sep);
	*/
}