#include <stdio.h>

int main(void)
{
	int a1 = 347;
	int a2 = 012;
	int a3 = 0x01B3;

	printf("%d %d %d\n", a1, a2, a3);
	printf("%o %o %o\n", a1, a2, a3);
	printf("%x %x %x\n", a1, a2, a3);
	printf("%X %X %X\n", a1, a2, a3);

	return 0;
}