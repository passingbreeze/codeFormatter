#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int i;
	int value;
	unsigned seed;

	seed = (unsigned)time(NULL);
	srand(seed);

	for (i = 0; i < 5; ++i) {
		value = (rand() % 13) + 3;
		printf("%d ", value);
	}
	printf("\n");
	return 0;
}