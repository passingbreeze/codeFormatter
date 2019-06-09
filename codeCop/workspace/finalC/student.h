#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum {MAX = 100};
typedef struct student {
    int snum;
    char *name;
    char *addr;
    char *dept;
    double grade;
} student;

extern int count;

int enterStudent(student*);
void sortStudent(student*, int);
void showStudent(student*, int);
void findBestStudent(student*, student*, int);

#endif
