#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int x = 5;

void fn()
{
    static int sx = 1;
    sx++;
    printf("%d", sx);
}

char* mystrdup(char* str)
{
    int len = strlen(str);
    char* pch = malloc(len + 1);
    while(*str)
    {
        *pch = *str;
        str++;
        pch++;
    }
    *pch = 0;
    return pch-len;
}

int main()
{
    char* buf = "234567890o";
    char* dup = mystrdup(buf);
    printf("%s\n", dup);
    free(dup);
}

int main33()
{
    const char* pch = "sdfghjkldfghjk";
    char a = 'A';
    static int sy = 77;
    // fn();
    // fn();
    // fn();
    int y = 7;
    printf("global %p,\n local %p,\n fn %p,\n sl %p,\nstatic %p\n", &x, &y, fn, pch, &sy);

}