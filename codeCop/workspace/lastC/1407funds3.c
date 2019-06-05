// Listing 14.7 The funds3.c Program
/* funds3.c -- passing a structure */
#include <stdio.h>
#include <stdlib.h>

#define FUNDLEN 50
struct funds {
	char bank[FUNDLEN];
	double bankfund;
	char save[FUNDLEN];
	double savefund;
};
double sum(struct funds moolah); /* argument is a structure */

int main(void)
{
	struct funds stan = {
		"Garlic-Melon Bank",
		4032.27,
		"Lucky's Savings and Loan",
		8543.94
	};
	printf("Stan has a total of $%.2f.\n", sum(stan));

	printf("main()::stan.bankfund = %f\n", stan.bankfund);
	system("pause");

	return 0;
}
double sum(struct funds moolah)
{
	moolah.bankfund += 1000.00;
	return(moolah.bankfund + moolah.savefund);
}
