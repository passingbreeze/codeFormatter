#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shuffle(double a[], int size)
{
	int i, rand_i;
	double temp;

	for (i = 0; i < size; ++i) {
		rand_i = (rand() + 1) % size;
		temp = a[i];
		a[i] = a[rand_i];
		a[rand_i] = temp;
	}
}

int main(void)
{
	double a[] = {1.1, 2.2, 3.3, 4.4, 5.5};
	int n = sizeof(a) / sizeof(*a);
	int i;

	srand((unsigned)time(NULL));
	shuffle(a, n);
	for (i = 0; i < n; ++i)
		printf("%g ", a[i]);
	printf("\n");
	return 0;
}
