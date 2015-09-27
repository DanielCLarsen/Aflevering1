#include <stdio.h>
#include <stdlib.h>
#include "dataManagement.h"

int avg_check(datastruct *peakdata, int current_r_interval){

	if (peakdata->RRhigh == 0){

		peakdata->RRlow = (peakdata->RRaverage2 * 0.92);
		peakdata->RRhigh = (peakdata->RRaverage2 * 1.16);
		peakdata->RRmiss = (peakdata->RRaverage2 * 1.66);
		return 0;
	} else{

		if(current_r_interval > peakdata->RRlow && current_r_interval < peakdata->RRhigh){
			peakdata->RRlow = (peakdata->RRaverage2 * 0.92);
			peakdata->RRhigh = (peakdata->RRaverage2 * 1.16);
			peakdata->RRmiss = (peakdata->RRaverage2 * 1.66);
			return 0;
		} else if (current_r_interval > peakdata->RRmiss) {
			return 1;
		}

	}


	return 0;;

}
