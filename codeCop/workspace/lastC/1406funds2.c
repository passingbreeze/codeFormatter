
// Listing 14.6 The funds2.c Program
/* funds2.c -- passing a pointer to a structure */
#include <stdio.h>
#include <stdlib.h>

#define FUNDLEN 50
struct funds {
    char bank[FUNDLEN];
    double bankfund;
    char save[FUNDLEN];
    double savefund;
};
//double sum(const struct funds); /* argument is structure */
double sum(struct funds *f); /* argument is a pointer */

int main(void) {
    struct funds stan = {
        "Garlic-Melon Bank",
        4032.27,
        "Lucky's Savings and Loan",
        8543.94
    };
    //printf("Stan has a total of $%.2f.\n", sum(stan));
    printf("Stan has a total of $%.2f.\n", sum(&stan));
    system("pause");

    return 0;
}
//double sum(const struct funds money)
double sum(struct funds *money) {
    /*
    printf("sum::ban = %f\n", money.bankfund);
    return(money.bankfund + money.savefund);
    */
    money->bankfund += 1000.00;
    printf("sum::ban = %f\n", money->bankfund);
    return(money->bankfund + money->savefund);
}
