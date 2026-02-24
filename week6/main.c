#include<stdio.h>

int g;
int* pg;

int* sum(int** nums, int* sizes, int size)
{
    int* nums_sums = malloc(size*sizeof(int));
    int sum=0;
    int i = 0;
    while (i < size)
    {
        int * subnums = *(nums+i); //nums[i];
        int subnums_size = *(sizes+i); // sizes[i]

        int j = 0;
        nums_sums[i] = 0;
        while (j < subnums_size)
        {
            int value = *(subnums + j); // subnums[j]
            nums_sums[i] += value;
        }
    }
    return nums_sums;
}

int sum(int* nums, int size)
{
    int sum = 0;
    int i = 0;
    while (i < size)
    {
        int v = *(nums + i);
        sum += v;
    }
}

int sum(int* nums, int size)
{
    int sum = 0;
    for(int i=0; i<size; i++)
        sum += nums[i];
    return sum;
}

int main(int argc, char** argv)
{
    char* pch = "ertuiodfgj";
    int a;
    int* pa;
    char buf[10];
    char* pbuf = malloc(10);
}