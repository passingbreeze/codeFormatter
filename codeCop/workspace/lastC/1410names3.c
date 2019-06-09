
// Listing 14.10 The names3.c Program
// names3.c -- use pointers and malloc()
// malloc()을 사용하여 문제 해결하는 경우
#include <stdio.h>
#include <string.h> // for strcpy(), strlen()
#include <stdlib.h> // for malloc(), free()

#define SLEN 81
struct namect {
    char * fname; // using pointers
    char * lname;
    int letters;
};
void getinfo(struct namect *); // allocates memory
void makeinfo(struct namect *);
void showinfo(const struct namect *);
void cleanup(struct namect *); // free memory when done
char * s_gets(char * st, int n);
int main(void) {
    struct namect person;
    struct names {
        char first[10];
        char last[10];
    };
    struct pnames {
        char *first;
        char *last;
    };
    /*
    struct names veep = { "Hong", "Bonghee" };
    struct pnames treas = { "Boby", "Jones" };
    printf("main::veep = %s and %s\n", veep.first, treas.first);
    struct names accountant;
    strcpy(accountant.first, "kim");
    struct pnames attorney;
    attorney.first = "Lee";
    printf("main::accountant = %s and %s\n", accountant.first, attorney.first);
    puts("Enter the last name of your accountant:");
    scanf("%s", accountant.last);
    puts("Enter the last name of your attorney:");
    attorney = veep;
    attorney = treas;
    printf("main::accountant = %s and %s\n", accountant.first, attorney.first);
    scanf("%s", attorney.last);
    */

    getinfo(&person);
    makeinfo(&person);
    showinfo(&person);
    cleanup(&person);

    system("pause");

    return 0;
}
void getinfo(struct namect * pst) {
    char temp[SLEN];
    printf("Please enter your first name.\n");
    s_gets(temp, SLEN);
    // allocate memory to hold name
    pst->fname = (char *)malloc(strlen(temp) + 1);
    //pst->fname = "Hong";
    // copy name to allocated memory
    strcpy(pst->fname, temp);
    printf("Please enter your last name.\n");
    s_gets(temp, SLEN);
    pst->lname = (char *)malloc(strlen(temp) + 1);
    strcpy(pst->lname, temp);
}
void makeinfo(struct namect * pst) {
    pst->letters = strlen(pst->fname) +
                   strlen(pst->lname);
}
void showinfo(const struct namect * pst) {
    printf("%s %s, your name contains %d letters.\n",
           pst->fname, pst->lname, pst->letters);
}
void cleanup(struct namect * pst) {
    free(pst->fname);
    free(pst->lname);
}
char * s_gets(char * st, int n) {
    char * ret_val;
    char * find;
    ret_val = fgets(st, n, stdin);
    if (ret_val) {
        find = strchr(st, '\n'); // look for newline
        if (find) // if the address is not NULL,
            *find = '\0'; // place a null character there
        else
            while (getchar() != '\n')
                continue; // dispose of rest of line
    }
    return ret_val;
}
