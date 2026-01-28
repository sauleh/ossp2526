#include<stdio.h>

void print_buf(char* buf)
{
    while(*buf)
    {
        printf("%p, %c\n", buf, *buf);
        buf++;
    }
}

int mystrlen(char* str)
{

}

void strcpy(char* src, char* tgt)
{

}

void strcat(char* str1, char* str2, char* tgt)
{
    
}


int main()
{
    // char buf[20] = {'b', 'o', 'u', 'd'};
    char buf[20] = "12345678901234567890";
    // char buf[20] = "asdfghjklasdfghjkl";
    print_buf(buf);
    printf("%s\n", buf);
    buf[9] = 0;
    print_buf(buf);
    printf("%s\n", buf);
    return 0;

    printf("%s", buf);
    int nums[5] = {0x11, 0x22, 0x33, 0x44, 0x55};    
    int i = 0;
    int* pn = nums;
    while (i < 5)
    {
        printf("%p: %x \n",pn, *pn);
        pn = pn + 1;
        i++;
    }

    // for (int i=0; i<5; i++)
    // {
    //     int * ptr = nums + i; // * sizeof(int);
    //     printf("%x , %x\n", nums[i], *ptr);
    // }
    int x = 6;
    // int x = 0x55;
    // int a = 0x55000000;
    // int b = 0x11ffff22;
    // int e = 0xaabbccdd;
    // char c = 0;
    // while (5 == 5)
    // {
    //     printf("%d ", c);
    //     c++;
    // }
    // return 0;
}