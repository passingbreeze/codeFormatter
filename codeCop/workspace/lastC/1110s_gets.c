//Listing 11.10   The  s_gets()  Function 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * s_gets(char * st, int n)
{
	printf("%s\n", st);
	char * ret_val;
//	printf("in func : %s\n", fgets(st, n, stdin));
	int i = 0;
	// i.e., ret_val != NULL
	ret_val = fgets(st, n, stdin);
	if (ret_val){
		while (st[i] != '\n' && st[i] != '\0'){
//			printf("%c ", st[i]);
			i++;
		}
		printf("\n");

		if (st[i] == '\n')
			st[i] = '\0';
		else // must have words[i] == '\0'
			while (getchar() != '\n')
				continue;
	}
	printf("length = %d\n", strlen(ret_val));
	return ret_val;
}

int main()
{
	int n;
	printf("enter the number -> ");
	scanf("%d", &n);
	char inp[BUFSIZ];
	printf("input string -> ");
	scanf("%s", inp);
	printf("%s\n", inp);
	printf("Result = %s\n", s_gets(inp, n));
	return EXIT_SUCCESS;
}