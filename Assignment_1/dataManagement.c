#include <stdio.h>
#include <stdlib.h>
#include "dataManagement.h"

void addPeak(datastruct *dataset, int iterations) {
	//adds a datapoint to the peak array, along with the iteration it was found at.
	dataset->PEAKS[0][dataset->peak_index%(DZ*10)] = (iterations - 1); // iteration count is stored
	dataset->PEAKS[1][dataset->peak_index%(DZ*10)] = dataset->mw_data[((dataset->ix + DZ - 2) % DZ)]; //stores the peak value (offset by two, to match p_search)
}

void addRPeak(datastruct *dataset, int iterations){
	//adds datapoint to the R-peak array
	dataset->R_PEAKS[0][dataset->r_peak_index%DZ] = (iterations - 1); // iteration count is stored
	dataset->R_PEAKS[1][dataset->r_peak_index%DZ] = dataset->PEAKS[1][dataset->peak_index%(DZ*10)];

	printf("R-peak at %i.%i s, value: %i \n",
			(dataset->R_PEAKS[0][(dataset->r_peak_index)%DZ])/250,
			(dataset->R_PEAKS[0][(dataset->r_peak_index)%DZ])%250*10/250,
			dataset->R_PEAKS[1][(dataset->r_peak_index)%DZ]);
}

int calcRRInterval (datastruct *dataset, int iterations){
	return (iterations - dataset->R_PEAKS[0][(dataset->r_peak_index - 1)% DZ]);
}



