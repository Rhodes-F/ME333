#ifndef HELPER__H
#define HELPER__H

#define MAX_YEARS 100
#endif

typedef struct {
	double inv0;
	double growth;
	int years;
	double invarray[MAX_YEARS+1];
} Investment;

void calculateGrowth(Investment *invp);
int getUserInput(Investment *invp);
void sendOutput(double *arr, int yrs);