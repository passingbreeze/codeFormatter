// implement the showStudent function here
#include "student.h"

void showStudent(student* list, int n) {
    printf("\nThis is students list\n");
    for(int i=0; i<n; ++i)
        printf("%d\t%s\t%s\t%s\t%lf\n", list[i].snum, list[i].name, list[i].addr, list[i].dept, list[i].grade);
}
