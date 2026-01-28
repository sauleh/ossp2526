#include<stdio.h>

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

int mystrlen(char* str)
{   
    int i=0; 
    for(; str[i] != 0; i++)
        ;
    
}

int main()
{
    // int x;
    char buf[255];
    scanf("%s", buf);
    // x++;
    // scanf("%d", &x);
    printf("\n%s %s\n", buf, buf);
    return 0;
}