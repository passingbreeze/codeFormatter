// implement the enterStudent function here
#include "student.h"

int enterStudent(student* list)
{
	int stdnum = 0;
	int i, breakpoint;

	for(i=0; i<MAX; ++i){
        printf("input student's information -> ");
        scanf("%d%s%s%s%lf", &list[i].snum, list[i].name, list[i].addr, list[i].dept, &list[i].grade);
        printf("input more students? plz input 1 >> ");
        scanf("%d", &breakpoint);
        if(breakpoint != 1)
            return i+1;
	}
    if(i>MAX)
        printf("You've entered enough students!\n");
    return MAX;
}
