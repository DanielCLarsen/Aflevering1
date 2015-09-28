#include <stdio.h>
#include <stdlib.h>
#include "dataManagement.h"

void addPeak(datastruct *dataset, int iterations) {
	dataset->PEAKS[0][dataset->peak_index%(DZ*10)] = (iterations - 1); // iteration count is stored
	dataset->PEAKS[1][dataset->peak_index%(DZ*10)] = dataset->mw_data[((dataset->ix + DZ - 2) % DZ)]; //stores the peak value
}

void addRPeak(datastruct *dataset, int iterations){
	dataset->R_PEAKS[0][dataset->r_peak_index%DZ] = (iterations - 1); // iteration count is stored

	dataset->R_PEAKS[1][dataset->r_peak_index%DZ] = dataset->PEAKS[1][dataset->peak_index%(DZ*10)];

	printf("R_peak at: iteration = %i, value of r_peak = %i \n",
			//(dataset->R_PEAKS[0][(dataset->r_peak_index)%DZ])/250,
//					dataset->R_PEAKS[1][(dataset->r_peak_index)%DZ]
					dataset->R_PEAKS[0][dataset->r_peak_index%DZ],dataset->R_PEAKS[1][dataset->r_peak_index%DZ]);

}

int calcRRInterval (datastruct *dataset, int iterations){
	return (iterations - dataset->R_PEAKS[0][(dataset->r_peak_index - 1)% DZ]);
}




