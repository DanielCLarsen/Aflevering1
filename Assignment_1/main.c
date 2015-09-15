#include <stdio.h>
#include "sensor.h"

// declaring global variable, filename for data load simulation.
static const char filename[] = "ECG.txt";

int main(int argc, char *argv[])
{
	datastruct dataset = {0}; //generates the struct object and initialises values at 0
	int test = 1; //test variable, not to be implemented in final version
	int iterations = 0; //test variable, not to be implemented in final version
	dataset.ix = 0; //index tracker for reading/writing data-array elements
	dataset.dz = 33; //tracker of the array lengths.

	//opens the file:
	dataset.file_p = fopen(filename,"r");

	//filter loop:
	while(test == 1){
		dataset.raw_data[dataset.ix] = getNextData(dataset.file_p); //retrieves the next line of data from the sensor
		dataset.lp_data[dataset.ix]=lp_filter(&dataset); //filters the data through low-pass
		dataset.hp_data[dataset.ix]=hp_filter(&dataset); //filters through high-pass
		dataset.de_data[dataset.ix]=de_filter(&dataset); //filters through derivative
		dataset.sq_data[dataset.ix]=sq_filter(&dataset); //filters through squared
		dataset.mw_data[dataset.ix]=mw_filter(&dataset);

		printf("\n %i ",dataset.ix);
		//printf("Raw: %i ",dataset.raw_data[dataset.ix]);
		//printf("Low: %i ",dataset.lp_data[dataset.ix]);
		//printf("High: %i ",dataset.hp_data[dataset.ix]);
		//printf("Derivative: %i ",dataset.de_data[dataset.ix]);
		//printf("Squared: %i ",dataset.sq_data[dataset.ix]);
		printf("Moving: %i ",dataset.mw_data[dataset.ix]);

		dataset.ix = (dataset.ix+1)%dataset.dz; // increments the index for the data-arrays

		//used to control the amount of iterations:
		iterations++;
		if (iterations == dataset.dz*2){
			test = 0;
		}
	}
	return 0;
}
