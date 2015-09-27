#include <stdio.h>
#include <stdlib.h>
#include "dataManagement.h"

void addPeak(datastruct *dataset, int iterations) {
	dataset->PEAKS[0][dataset->peak_index % dataset->dz] = (iterations - 1); // iteration count is stored
	dataset->PEAKS[1][dataset->peak_index % dataset->dz] =
			dataset->mw_data[((dataset->ix + dataset->dz - 2) % dataset->dz)]; //stores the peak value
}

void addRPeak(datastruct *dataset, int iterations){
	dataset->R_PEAKS[0][dataset->r_peak_index % dataset->dz] =
						(iterations - 1); // iteration count is stored
				dataset->R_PEAKS[1][dataset->r_peak_index % dataset->dz] =
						dataset->PEAKS[1][dataset->peak_index % dataset->dz];
}

void calcRRInterval (datastruct *dataset, int RecentRPeaks_index, int iterations){
	dataset->RRintervals[RecentRPeaks_index] = (iterations
			- dataset->R_PEAKS[0][(dataset->r_peak_index - 1)
					% dataset->dz]);
}





