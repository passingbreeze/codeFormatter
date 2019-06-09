// implement the findBestStudent function here
#include "student.h"

void findBestStudent(student* s, student* list, int n) {
    *s = list[0];
    for(int i=0; i<n; ++i) {
        if(s->grade < list[i].grade) {
            *s = list[i];
        }
    }
}
