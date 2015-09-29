#include <stdio.h>
#include <stdlib.h>
#include "dataManagement.h"


int r_detecter(datastruct *dataset, int current_peak){
int xn = dataset->PEAKS[1][current_peak];


if (dataset->THRESHOLD1 < xn && dataset->PEAKS[0][current_peak]-dataset->PEAKS[0][current_peak-1] > 25){
	//extra demand: r-peak must be at least 1/10s away from previous r-peak
	return 1;
}
//Updates values due to this peak.
	dataset->NPKF = 0.125*xn+0.875*dataset->NPKF;

	dataset->THRESHOLD1 = dataset->NPKF + 0.25*(dataset->SPKF - dataset->NPKF);

	dataset->THRESHOLD2 = dataset->THRESHOLD1*0.5;

return 0;
}
