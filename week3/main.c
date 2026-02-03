#include<stdio.h>
#include<stdlib.h>

void print_jaggedarray(char** buf, int size)
{
    for(int i=0; i<size; i++)
        printf("%s\n", buf[i]);
}
void print_jagged_array_int(int ** nums, int* nums_sizes, int size)
{
    for(int i=0; i<size; i++)
    {
        for (int j=0; j<nums_sizes[i];  j++)
            printf("%d\t", nums[i][j]);
        printf("\n");
    }
}
int main()
{
    int nums1[5] = {0x11, 0x00, 0x13, 0x14, 0x015};
    int nums2[2] = {0x21, 0x22};
    int nums3[1] = {0x31};
    int nums_size[3] = {5, 2, 1};
    int* nums[3] = {nums1, nums2, nums3};    
    print_jagged_array_int(nums, nums_size, 3);
}
int main_demo_jagged_array_string(int argc, char** argv)
{
    print_jaggedarray(argv, argc);
    return 0;

    // jagged array
    char buf1[20] = "00000000000000";
    char buf2[20] = "11111111111111";
    char buf3[20] = "22222222222222";
    char buf4[20] = "33333333333333";
    char buf5[20] = "44444444444444";

    char* buf[5] = {buf1, buf2, buf3, buf4, buf5  };
    print_jaggedarray(buf, 5);
        // "000000000000",
        // "ZZZZZZZZZZZZ",
        // "AAAAAAAAAAAA",
        // "BBBBBBBBBBBB",
        // "CCCCCCCCCCCC"

}

int main_2darray()
{
    // 2d array
    int nums2d[3][2] = {
        {0x11, 0x12},
        {0x21, 0x22},
        {0x31, 0x32}
    };
//    int * pnums2d = (int*) (&nums2d);
    printf("%p %d\n", nums2d, sizeof(nums2d));
    printf("%p %d\n", nums2d+1, sizeof(nums2d[0]));
    printf("%p %d\n", nums2d[0]+1, sizeof(nums2d[0][1]));

    printf("");
}


int main_demo_heap_vs_stack()
{
    int x = 5;
    int* pn = malloc(sizeof(int) * 4);
    pn[0] = 0xffaaee11;
    pn[1] = 0xffaaee12;
    pn[2] = 0xffaaee13;
    pn[3] = 0xffaaee14;
    printf("%p", pn);
}