#include "mydefs.h"
#include <stdio.h>

void print_std(Student* ps)
{
    printf("%d %s %lf", ps->id, ps->name, (*ps).gpa);
}