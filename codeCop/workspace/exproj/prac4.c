#include <stdio.h>

void set_n(int a[], int sz, int n) {
    int i, cnt = 0;

    for (i = 0; i < sz; ++i) {
        a[i] = ((cnt++) < n) ? 1 : 0;
    }
}

void print(int a[], int sz) {
    int i;

    for (i = 0; i < sz; ++i)
        printf("%d ", a[i]);
    printf("\n");
}

int main(void) {
    int a[10];
    int sz = sizeof(a) / sizeof(*a);
    int n;

    scanf("%d", &n);
    set_n(a, sz, n);
    print(a, sz);
    return 0;
}