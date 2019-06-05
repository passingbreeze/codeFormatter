//Listing 12.7
/* rand0.c –– produces random numbers            */
/*               uses ANSI C portable algorithm  */
#include <stdio.h>
static unsigned long int next = 1;  /* the seed  */

unsigned int rand0(void)
{
	/* magic formula to generate pseudorandom number */
	printf("rand0():: next = %ld\n", next);
	next = next * 1103515245 + 12345;
	return (unsigned int)(next / 65536) % 32768;
}
