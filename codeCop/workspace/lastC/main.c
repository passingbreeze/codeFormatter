#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define nullptr ((void*)0)

enum {ROW=6, COL=6, HIGH=6};

void set3d(int ***);
void print3d(int ***);
void clear(int ***);

int main() {
    srand((unsigned)time(nullptr));
    // try : int a[5][6][10]
    int ***a = nullptr;
    a = (int***)calloc(HIGH,sizeof(int**));
    *a = (int**)calloc(COL*HIGH,sizeof(int*));
    **a = (int*)calloc(ROW*COL*HIGH, sizeof(int));

    for(int i=1; i<HIGH; ++i) {
        a[i] = a[i-1]+COL*ROW;
        for(int j=1; j<ROW; ++j) {
            a[i][j] = a[i][j-1]+COL;
        }
    }

//    set3d(a);
    printf("set here.\n");
    print3d(a);
    clear(a);

    return EXIT_SUCCESS;
}

void set3d(int ***arr) {
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j)
            for (int k = 0; k < HIGH; ++k)
                arr[i][j][k] = rand() % 10 + 1;
}

void print3d(int*** arr) {
    for(int i=0; i < ROW; ++i) {
        for(int j=0; j < COL; ++j) {
            for(int k=0; k < HIGH; ++k) {
                printf(" %d ", arr[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("\n");
}

void clear(int ***arr) {
    if(arr!=nullptr) {
        free(**arr);
        free(*arr);
        free(arr);
    }
}