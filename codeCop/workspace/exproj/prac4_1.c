#include <stdio.h>

int main(void) {
    int a[] = {11, 22, 33};
    int i;

    for (i = 2; i >= 0; --i)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}