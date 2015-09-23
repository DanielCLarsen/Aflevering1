#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int searchback(peakstruct *peakdata, datastruct *dataset,int index){

	for(int i=1; i<=dataset->dz; i++){
		if(peakdata->PEAKS[index-i]>peakdata->THRESHOLD2){
			peakdata->PEAKS[index-i]

		}


	}
	return 0;
}
