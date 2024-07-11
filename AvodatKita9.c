#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

int countLines(char* filename);
void letterFrequency(char* filename, int counts[26]);
void moveto(char* infile, char* outfile);
int main30()
{
	char* c ="C:\\Users\\afik3\\Desktop\\stam.txt";
 	return 0;

}

int countLines(char* filename)
{  
    int count = 0, lastCharWasNewline = 1;
    char ch;
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "Could not open file %s for reading\n", filename);
        return -1;
    }

    while ((ch = fgetc(f)) != EOF) {
       if(ch=='\n') 
           count++;
       lastCharWasNewline = (ch == '\n');
    }
    if (!lastCharWasNewline) {
        count++;
    }

    fclose(f);
    return count;
}

void letterFrequency(char* filename, int counts[26])
{
    char ch;
    FILE* f = fopen(filename, "r");
    if (f==NULL)
    {
        printf("couldn't open file %s\n",filename);
        return;
    }
    while ((ch=fgetc(f)) !=EOF)
    {
        if (isupper(ch))
        {
            counts[ch - 'A']++;
        }
        else if (islower(ch))
        {
            counts[ch - 'a']++;
        }
    }
    fclose(f);

}

void moveto(char* infile, char* outfile)
{
    FILE* in, *out;
    fopen_s(&in, infile, "r");
    fopen_s(&out, outfile, "a");
    char* arr=NULL, ch;
    int count = 0,i;
    if (in == NULL)
        return;
    if (out == NULL)
        return;
    while ((ch = fgetc(in)) != EOF)
    {
        if (ch != " ")
            count++;
    }
    arr = (char*)calloc(count ,sizeof(char));
    i = 0;
    rewind(in);
    while ((ch = fgetc(in)) != EOF)
    {
        if (ch != " " )
            arr[i++] = ch;
    }
    arr[count] = '\0';
    for ( i = 0; i < count; i++)
    {
        fputc(arr[i], out);
    }
    
    rewind(in);
    rewind(out);
    fclose(in);
    fclose(out);
    free(arr);
}
