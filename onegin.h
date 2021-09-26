#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>

enum RESULTS
{
    FAIL = 0,
    SUCCESS = 1,    
};

struct line
{
    char* index;
    int lenStr;
};

int open_f (FILE** input, FILE** output);
int len_f (FILE* file);
int read_f (char* str, int len, FILE* input);
int compare_f (const void* p1, const void* p2);
int compare_l (const void* p1, const void* p2);
int scanFile (int len, struct line* string, char* str_in);
const int countN (int len, char* str_in);
int put_res (struct line* string, int numN, FILE* output);
void beauty_divide1 (FILE* output);
void beauty_divide2 (FILE* output);

