#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

typedef struct _Student
{
    int student_id;
    char name[20];
    int national_id;
    double GPA;
} Student;

Student* make_student(int id, char* buf, int natid, double gpa)
{
    Student* ps = malloc(sizeof(Student));
    ps->student_id = id;
    ps->national_id = natid;
    ps->GPA = gpa;

    int i=0;
    while(buf[i])
    {
        ps->name[i] = buf[i];
        i++;
    }
    ps->name[i] = 0;
    return ps;
}

int main()
{
    

    Student Mary = {
        .student_id = 0x11223344,
        .name = "Mary AAAAAAA",
        .national_id = 0xaaaaaaaa,
        .GPA = 99.99
    };
    printf("%x, %s, %x, %lf", Mary.student_id, Mary.name, Mary.national_id, Mary.GPA);
}

int main_pointer_cast()
{
    unsigned long long int n = 0x11223344AABBCCDD;
    unsigned char * pch = (char*) &n;
    for(int i=0; i<8; i++)
        printf("%x\n", pch[i]);
}


int main_do()
{
    unsigned long long int n = 0x11223344AABBCCDD;
    for(int i = 0; i<8; i++)
    {
        unsigned char b = n & 0x00000000ff;
        printf("%x\n", b);
        n = n >> 8;
    }
}

int main_memory_leak()
{
    long long sum = 0;
    for(int i=0; i<1000*1000; i++)    
    {
        int* nums = malloc(100*1000);
        sum += nums[1000];
        Sleep(100);
        printf("\r%d", i);
    }
    printf("%d\n", sum);
}









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
int main_jaagged_array_int()
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