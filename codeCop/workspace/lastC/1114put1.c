
//Listing 11.14   The  put1()  Function
/* put1.c -- prints a string  without adding \n */
#include <stdio.h>
void put1(const char * string)
/* string not altered */
{
	while (*string != '\0')
		putchar(*string++);
}
