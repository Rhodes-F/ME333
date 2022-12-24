#include <stdio.h>
#include "io.h"

int getUserInput(Investment *invp) {
	int valid;
	
	char msg[100] = {};
	
	//changed here
	sprintf(msg, "Enter investment, growth rate, number of yrs (up to %d): ",MAX_YEARS);
	NU32_WriteUART3(msg);
	NU32_ReadUART3(msg, 100);
	sscanf(msg, "%lf %lf %d", &(invp->inv0), &(invp->growth), &(invp->years));
	
	valid = (invp->inv0 > 0) && (invp->growth > 0) &&
	(invp->years > 0) && (invp->years <= MAX_YEARS);
	
	//changed here
	sprintf(msg, "Valid input? %d\r\n", valid);
	NU32_WriteUART3(msg);
	
	if (!valid) {
		//changed here
		sprintf(msg, "Invalid input; exiting.\r\n");
		NU32_WriteUART3(msg);
	}
	return(valid);
}

void sendOutput(double *arr, int yrs) {
	int i;
	char outstring[100];
	
	//changed here
	sprintf(outstring, "\nRESULTS:\r\n\n");
	NU32_WriteUART3(outstring);
	
	for (i=0; i<=yrs; i++) {
		//changed here
		sprintf(outstring, "Year %3d: %10.2f\r\n", i, arr[i]);
		NU32_WriteUART3(outstring);
	}
	NU32_WriteUART3("\r\n"); 
}