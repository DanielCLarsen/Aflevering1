#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int r_detecter(peakstruct *peakdata, int current_peak){
int xn = peakdata->PEAKS[1][current_peak];


if (peakdata->THRESHOLD1 < xn){

	peakdata->SPKF = 0.125*xn+0.875*peakdata->SPKF;

	peakdata->NPKF = 0.125*xn+0.875*peakdata->NPKF;

	peakdata->THRESHOLD1 = peakdata->NPKF + 0.25*(peakdata->SPKF - peakdata->NPKF);

	peakdata->THRESHOLD2 = peakdata->THRESHOLD1*0.5;

	return 1;

}
return 0;

}
