#include <stdio.h>
#include <stdlib.h>
#include "dataManagement.h"

int avg_check(datastruct *dataset, int current_r_interval){

	if (dataset->RRhigh == 0){
		dataset->RRlow = (dataset->RRaverage2 * 0.92);
		dataset->RRhigh = (dataset->RRaverage2 * 1.16);
		dataset->RRmiss = (dataset->RRaverage2 * 1.66);
		return 0;
	} else{

		if(current_r_interval > dataset->RRlow && current_r_interval < dataset->RRhigh){

			addRPeak(&dataset,iterations);

			dataset->RRlow = (dataset->RRaverage2 * 0.92);
			dataset->RRhigh = (dataset->RRaverage2 * 1.16);
			dataset->RRmiss = (dataset->RRaverage2 * 1.66);
			dataset->RRmiss_count = 0;
			return 0;
		} else if (current_r_interval > dataset->RRmiss) {
			return 1;
		}

	}

	dataset->RRmiss_count++;
	return 0;

}
