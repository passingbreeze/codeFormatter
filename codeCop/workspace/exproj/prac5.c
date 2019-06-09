#include <stdio.h>
#include <stdlib.h>

int less(const void* v1, const void* v2) {
    return (((*(int*)v1) > (*(int*)v2)) - ((*(int*)v1) < (*(int*)v2)));
}

int main(void) {
    int a[] = {35, 27, 9, 0, 1, 2, 45, 1, 9, 13};
    unsigned i;
    unsigned num = sizeof(a) / sizeof(*a);

    qsort(a, num, sizeof(int), less);
    for (i = 0; i < num; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}