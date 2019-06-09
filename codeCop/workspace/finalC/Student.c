
#include "student.h"

int count = 0;

int main(void) {
    student *list = (student*)calloc(MAX, sizeof(student));
    student *s = (student*)malloc(sizeof(student));

    for(int i=0; i<MAX; ++i) {
        list[i].name = (char*)calloc(BUFSIZ, sizeof(char));
        list[i].addr = (char*)calloc(BUFSIZ, sizeof(char));
        list[i].dept = (char*)calloc(BUFSIZ, sizeof(char));
    }
    int select = 0;

    while (1) {
        printf("\nSelect command 1: 입력, 2: 테이블 출력,  3: 정렬(snum), 4: 최고학점학생검색, 5. Quit\n => ");
        scanf("%d", &select);
        switch (select) {
        case 1:
            if(count > MAX)
                printf("\nYou cannot input more students.\n");
            else
                count += enterStudent(list);
            break;

        case 2:
            showStudent(list, count);
            break;

        case 3:
            sortStudent(list, count);
            break;
        case 4:
            findBestStudent(s, list, count);
            printf("\nHere is best!\n => %d %s %s %s %f\n", s->snum, s->name, s->addr, s->dept, s->grade);
            break;
        case 5:
            if(s!=NULL)
                free(s);

            if(list!=NULL) {
                for(int i=0; i<MAX; ++i) {
                    free(list[i].addr);
                    free(list[i].name);
                    free(list[i].dept);
                }
                free(list);
            }
            exit(0);
        default:
            printf("wrong input");
            break;
        }
    }

    return EXIT_SUCCESS;
}




