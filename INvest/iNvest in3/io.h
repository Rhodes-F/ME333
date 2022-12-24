#ifndef IO__H
#define IO__H

#define MAX_YEARS 100

typedef struct {
	double inv0;
	double growth;
	int years;
	double invarray[MAX_YEARS+1];
} Investment;

int getUserInput(Investment *invp);
void sendOutput(double *arr, int yrs);

#endif