#include<stdio.h>
#include<stdlib.h>
#define SIZE 3

typedef struct student_init_data
{
	int id;
	double* grades;
	int tests_amount;
}student;

typedef struct student_processed_data 
{
	int id;
	double avg;
}student_avg;

typedef struct Statistics
{
	student_avg *avg1,*avg2;
	int size1,size2;
	double avg_satistic;


}satistics;

double* input_data(int size);
void print_arr(double* arr, int size);
double student_average(double* arr, int size);
double total_avg(student_avg* avgs, int size);
void Classification(student* stds, int size, satistics* st);
void print_tab(satistics s);
void free_memory(satistics* s, student* std, int size_std);
void input_students(student** stds, int size);
void print_students(student* s, int size);
void print_satistic(satistics s);

void main5()
{
	student* stds;
	input_students(&stds, SIZE);
	print_students(stds, SIZE);
	satistics s;
	Classification(stds, SIZE, &s);
	print_satistic(s);
	free_memory(&s, stds, SIZE);
}
void print_satistic(satistics s)
{
	printf("--------------------------------\nabove avg:");
	int i;
	for ( i = 0; i < s.size1; i++)
	{
		printf("[%.2f]", s.avg1[i].avg);
	}
	printf("\nunder avg:");
	for ( i = 0; i < s.size2; i++)
	{
		printf("[%.2f]", s.avg2[i].avg);
	}
	printf("\ntotal avg:%.2f\n", s.avg_satistic);
}
void print_students(student* s,int size)
{
	printf("-----------------");
	int i;
	for ( i = 0; i < size; i++)
	{
		printf("\nstudent num[%d]", i + 1);
		printf("\nid:%d", s[i].id);
		printf("\ngrades:");
		print_arr(s[i].grades, s[i].tests_amount);
	}
}
void input_students(student** stds,int size)
{
	*stds = (student*)malloc(size * sizeof(student));
	int i;
	for (i = 0; i < size; i++)
	{
		printf("student num[%d]\nwrite id ", i + 1);
		scanf_s("%d", &((*stds)[i].id));
		printf("\nwrite amount of tests ");
		scanf_s("%d", &((*stds)[i].tests_amount));
		(*stds)[i].grades = input_data((*stds)[i].tests_amount);
	}
}
void print_arr(double* arr, int size)
{
	int i;
	for ( i = 0; i < size; i++)
	{
		printf("[%.2f]", arr[i]);
	}
	printf("\n");
}

double* input_data(int test_amount)
{
	int i;
	double* tests = (double*)calloc(test_amount, sizeof(double));
	for ( i = 0; i < test_amount; i++)
	{
		printf("write grade [%d]\n",i+1);
		scanf_s("%lf",&(tests[i]));
	}
	return tests;
}
double student_average(double* arr, int size)
{
	int i;
	double avg=0;
	for ( i = 0; i < size; i++)
	{
		avg += arr[i];
	}
	return avg / size;
}

double total_avg(student_avg* avgs, int size)
{
	int i;
	double avg = 0;
	for (i = 0; i < size; i++)
	{
		avg += avgs[i].avg;
	}
	return avg / size;
}

void Classification(student* stds,int size,satistics* st)
{
	student_avg* avg1, * avg2;
	int i,size_avg1=0,size_avg2=0;
	student_avg* avg_all = (student_avg*)malloc(size * sizeof(student_avg));
	for ( i = 0; i < size; i++)
	{
		avg_all[i].avg = student_average(stds[i].grades, stds[i].tests_amount);
		avg_all[i].id = stds[i].id;
	}
	st->avg_satistic = total_avg(avg_all, size);
	for ( i = 0; i < size; i++)
	{
		if (avg_all[i].avg >= st->avg_satistic)
			size_avg1++;
		else
			size_avg2++;
	}
	avg1 = (student_avg*)malloc(size_avg1 * sizeof(student_avg));
	avg2 = (student_avg*)malloc(size_avg2 * sizeof(student_avg));
	size_avg1 = size_avg2 = 0;
	for ( i = 0; i < size; i++)
	{
		if (avg_all[i].avg >= st->avg_satistic)
		{
			avg1[size_avg1++] = avg_all[i];
		}
		else
		{
			avg2[size_avg2++] = avg_all[i];
		}
	}
	st->avg1 = avg1;
	st->avg2 = avg2;
	st->size1 = size_avg1;
	st->size2 = size_avg2;
	avg1 = avg2 = NULL;
}

void print_tab(satistics s)
{
	printf("first group:");
	print_arr(s.avg1, s.size1);
	printf("second group:");
	print_arr(s.avg2, s.size2);
	printf("average of all students:%.2f", s.avg_satistic);
}

void free_memory(satistics* s, student* std, int size_std)
{
	int i;
	free(s->avg1);
	free(s->avg2);
	for (i = 0; i < size_std; i++)
		free(std[i].grades);
	free(std);
	s->avg1 = s->avg2 = NULL;
}