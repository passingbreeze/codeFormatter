// implement the sortStudent function here
#include "student.h"
void sortStudent(student* list, int n) {
    student temp;
    for(int i=0; i<n; ++i) {
        for(int j=i+1; j<n; ++j) {
            if(list[i].snum > list[j].snum) {
                temp = list[i];
                list[i] = list[j];
                list[j]=temp;
            }
        }
    }

}
