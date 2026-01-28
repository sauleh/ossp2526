#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int mystrlen2(char* buf)
{
    int i = 0;
    while(buf[i] != 0)
    {
        i++;
    }
    return i;
}


int mystrlen(char* buf)
{
    int len=0;
    while(*buf)
    {
        buf++;
        len++;
    }
    return len;
}

// void strcpy(char* src, char* tgt)
// {}

// void append(char* str, char* str2)
// {    
// }


// int main()
// {
//     char f = 0;
//     printf("%c\n", f);
// }

char* strduplicate(char* str)
{
    int len = strlen(str);
    char* dup = malloc(len + 1);
    for(int i = 0; i<len; i++)
        dup[i] = str[i];
    dup[len] = 0;
    return dup;
}

int x = 5;

int main()
{
    const char* pch = "hjkl";
    int w = 7;
    static int x = 7;
    char buf[20] = "sdfghjfdfghj";
    char* buf1 = strduplicate(buf);
    printf("%s", buf1);
    free(buf1);

    return 0;
}