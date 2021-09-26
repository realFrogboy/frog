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



int main ()
{
    FILE *input = NULL, *output = NULL;
    
    if ((open_f (&input, &output)) == FAIL)   
        return FAIL;
    
    int len = len_f (input);
    printf ("%d\n", len);

    char* str_in = NULL;
    str_in = (char*) calloc (len, sizeof (char));

    if ((read_f (str_in, len, input)) == FAIL)
        return FAIL;
    
    const int numN = countN (len, str_in);
    printf ("%d", numN);

    struct line string[numN];

    scanFile (len, string, str_in);

    qsort (string, numN, sizeof (struct line), compare_f);
    put_res (string, numN, output);

    beauty_divide1 (output);

    qsort (string, numN, sizeof (struct line), compare_l);
    put_res (string, numN, output);

    beauty_divide2 (output);

    fwrite (str_in, sizeof (char), len, output);

    free (str_in);

    return SUCCESS;
}



int open_f (FILE** input, FILE** output)
{
    if ((*input = fopen ("Gamlet.txt", "a+b")) == NULL)
    {
        printf ("Error openning file Gamlet.txt");
        return FAIL;
    }

    if ((*output = fopen ("oGamlet.txt", "a+b")) == NULL)
    {
        printf ("Error openning file oGamlet.txt");
        return FAIL;
    }
}


int len_f (FILE* file)
{
    assert (file);

    fseek (file, 0L, SEEK_END);
    int len = ftell (file); 
    rewind (file);

    return len;    
}


int read_f (char* str, int len, FILE* input)
{
    assert (isfinite (len));
    assert (input);
    assert (str);
    
    int ret_code = fread (str, sizeof (char), len, input);
    str [len + 1] = '\0';
    if (ret_code != len)
    {
       printf ("Error reading Gamlet.txt\n");
       return FAIL;
    }
    else
    {
        int n;
        for (n = 0; n < len; n++)
        {
            printf ("%c", str[n]);
        }
        return SUCCESS; 
    }    
}


int compare_f (const void* p1, const void* p2)
{
    assert (p1);
    assert (p2);
    assert (p1 != p2);
    
    const struct line* ps1 = (const struct line*) p1;
    const struct line* ps2 = (const struct line*) p2;

    int res;
    res = strcmp (ps1->index, ps2->index);
    return res;
}

int compare_l (const void* p1, const void* p2)
{
    assert (p1);
    assert (p2);
    assert (p1 != p2);
    
    const struct line* ps1 = (const struct line*) p1;
    const struct line* ps2 = (const struct line*) p2;

    int min;
    if (ps1->lenStr > ps2->lenStr)
        min = ps2->lenStr;
    else
        min = ps1->lenStr;
    
    int num;
    for (num = 0; num < min; num++)
    {
        if (*(ps1->index + ps1->lenStr - num) > *(ps2->index + ps2->lenStr - num))
            return 1;
        else if (*(ps1->index + ps1->lenStr - num) < *(ps2->index + ps2->lenStr - num))
            return -1;
    }
}


int scanFile (int len, struct line* string, char* str_in)
{
    assert (isfinite (len));
    assert (string);
    assert (str_in);
    
    int num, numBeg = 0, k = 0, fl = 0;
    
    for (num = 0; num < len+1; num++)
    {

        if ((isalpha (str_in[num])) && (fl == 0))
        {
            string[k].index = &str_in[num];
            numBeg = num;
            fl = 1;
        }

        if (str_in[num] == '\0')
        {
            int num1 = num;

            string[k].lenStr = num - numBeg;
            fl = 0;

            printf ("%d ", string[k].lenStr);

            while (!isalpha (str_in[num--]))
            {
                string[k].lenStr--;
            }

            printf ("--- %d\n", string[k].lenStr);

            k++;
            num = num1;
       }
    }
}


const int countN (int len, char* str_in)
{
    assert (isfinite (len));
    assert (str_in);
    
    int num, kol = 0;   

    for (num = 0; num < len; num++)
        if (str_in[num] == '\n')
        {
            str_in[num] = '\0';
            kol++;
        }
        
    str_in[len] = '\0';
    
    return kol+1;

}


int put_res (struct line* string, const int numN, FILE* output)
{
    assert (isfinite (numN));
    assert (string);
    assert (output);
    
    int num;
    for (num = 0; num < numN; num++)
    {
        fputs (string[num].index, output);
    }    
}

void beauty_divide1 (FILE* output)
{
    assert (output);
    
    fputs ("\n", output);
    fputs ("\n", output);
    fputs ("By the last letters", output);
    fputs ("\n", output);
    fputs ("\n", output);
}

void beauty_divide2 (FILE* output)
{
    assert (output);
    
    fputs ("\n", output);
    fputs ("\n", output);
    fputs ("Untouched text", output);
    fputs ("\n", output);
    fputs ("\n", output);    
}
