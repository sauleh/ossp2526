#include<stdio.h>
#include<string.h>

void inc(int x)
{
    x = x + 1;
}

void inca(int* arr, int elem)
{
    arr[elem] = arr[elem] + 1;
}

int main5()
{
    int nums[3] = {1, 2, 3};
    inca(nums, 1);
    for(int i=0; i<3; i++)
        printf("%d ", nums[i]);
    printf("\n");
    return 0;
}

int main3()
{
    int x = 0;
    inc(5);
    printf("%d\n", x);
}

int mystrlen_while(char* str)
{   
    int len=0;
    while(*str) len++;
    return len;
}

void str_append(char* str, char* str2)
{
    while(*str) str++;

    while(*str2)
    {
        *str = *str2;
        str++;
        str2++;
    }
    *str = 0;
}

int main()
{
    char str[20] = "John";
    char str2[10] = "Amy";
    str_append(str, str2);
    printf("%s\n", str);
}

int mystrlen(char* str)
{   
    int i=0; 
    for(; str[i] != 0; i++)
        ;
    return i;
}

int main_demolen()
{
    // int x;
    while(1)
    {
        char buf[255];
        scanf("%s", buf);
        printf("\n%s %d\n", buf, mystrlen(buf));
    }    
    // x++;
    // scanf("%d", &x);
    return 0;
}