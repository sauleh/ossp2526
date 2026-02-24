#include "mydefs.h"
#include <stdio.h>
#define STDID int
//#define DEBUG 1

// void print_std(Student* ps)
// {
//     printf("%d %s %lf", ps->id, ps->name, (*ps).gpa);
// }

extern void print_std(Student* ps);


int main()
{
    Student x = {
        .id = 1234,
        .gpa = 99.99,
        .name = "dfgjkl"
    };

    STDID myid;
    myid = 1234;

    #ifdef DEBUG
    printf("%d %s %lf", x.id, x.name, x.gpa);
    #endif

    print_std(&x);

    return 0;
}