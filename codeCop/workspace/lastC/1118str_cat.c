#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum {SIZE=80};

char* s_gets(char *st, int n)
{
    char *ret_val = fgets(st, n, stdin);
    int i=0;

    if(ret_val)
    {
        while(st[i]!='\n' && st[i]!='\0')
            ++i;
        if(st[i]=='\n')
            st[i] = '\0';
        else
            while(getchar()!='\n')
                continue;
    }
    return ret_val;
}
int main()
{
    char flower[SIZE];
    char addon[] = "s smell like old shoes.";

    puts("What is your favorite flower?");
    if(s_gets(flower, SIZE))
    {
        strcat(flower, addon);
        puts(flower);
        puts(addon);
    }
    else
        puts("End of file encountered.");
    puts("bye");

    return EXIT_SUCCESS;
}