#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int reverse_string(char* string);
void erase_spaces(char* str);

int main22()
{
	char s[] = "a  di";
	erase_spaces(s);
	puts(s);
	return 0;
}
void swap(char* x, char* y)
{
	char temp = *x;
	*x = *y;
	*y = temp;
}

int reverse_string(char* string)
{	
	char* end;
	int pal = 1;
	for (end = string+strlen(string); string < end; string++,end--)
	{
		if (*string != *end)
		{
			swap(string, end);
			pal = 0;
		}
	}
	return pal;
}
void identify(char* str, int* lower, int* upper, int* nums, int* other)
{
	*lower = *upper = *nums = *other = 0;
	for (;  *str != '\0'; str++)
	{
		if (islower(*str))
			(*lower)++;
	    
	}
}

void erase_spaces(char* str) {
	int i, j = 0;
	int len = strlen(str);

	for (i = 0; i < len; i++) {
		if (str[i] != ' ' || (i > 0 && str[i - 1] != ' ')) {
			str[j++] = str[i];
		}
	}
	str[j] = '\0'; // Null terminate the string
}