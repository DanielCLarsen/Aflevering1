#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int searchback(peakstruct *peakdata, datastruct *dataset,int iterations){

	//runs through the stored peaks, if one is above threshold 2 it is stored into R-peaks:
	for(int i=1; i<=dataset->dz; i++){
		if(peakdata->PEAKS[1][(peakdata->peak_index-i)%dataset->dpeaks]>peakdata->THRESHOLD2){
			//if(peakdata->PEAKS[1][(peakdata->peak_index-i)%dataset->dpeaks] >= peakdata->THRESHOLD1){
			//break;
			//}

			//moves the last R-peak forward, to make space for the newly found R-peak
			peakdata->R_PEAKS[0][(peakdata->r_peak_index+1) % dataset->dz]=peakdata->R_PEAKS[0][(peakdata->r_peak_index)% dataset->dz];
			peakdata->R_PEAKS[1][(peakdata->r_peak_index+1) % dataset->dz] =peakdata->R_PEAKS[1][(peakdata->r_peak_index)% dataset->dz];

			//stores the found peak as an r-peak:
			peakdata->R_PEAKS[0][peakdata->r_peak_index % dataset->dz] = iterations-i; //iteration count is stored
			peakdata->R_PEAKS[1][peakdata->r_peak_index % dataset->dz] = peakdata->PEAKS[1][(peakdata->peak_index-i) % dataset->dpeaks]; //stores the peak value
			printf("R_peak at: time = %i s, value of r_peak = %i (searchback) \n",peakdata->R_PEAKS[0][(peakdata->r_peak_index)%dataset->dz]/250,peakdata->R_PEAKS[1][(peakdata->r_peak_index)%dataset->dz]);

			//updates values:
			int pn = peakdata->R_PEAKS[1][peakdata->r_peak_index % dataset->dz];

			peakdata->SPKF = 0.25*pn+0.75*peakdata->SPKF;

			peakdata->THRESHOLD1 = peakdata->NPKF + 0.25*(peakdata->SPKF - peakdata->NPKF);

			peakdata->THRESHOLD2 = peakdata->THRESHOLD1*0.5;

			//recalculates the RR average:
			peakdata->RRintervals[peakdata->RRintervals_index]= (iterations-peakdata->R_PEAKS[0][(peakdata->r_peak_index-1)%dataset->dz]);

			peakdata->RRintervals_index = (peakdata->RRintervals_index+1)%8;
			for(int i=0; i < 8 ;i++){
				int Average2sum=0;
				Average2sum+=peakdata->RRintervals[i];
				peakdata->RRaverage1 = Average2sum/8;
			}
			peakdata->RRlow = (peakdata->RRaverage1 * 0.92);
			peakdata->RRhigh = (peakdata->RRaverage1 * 1.16);
			peakdata->RRmiss = (peakdata->RRaverage1 * 1.66);

			if (peakdata->R_PEAKS[1][peakdata->r_peak_index % dataset->dz]<peakdata->THRESHOLD2){
				printf("Warning: heartbeat too weak!\n");
			}

			//peakdata->RRaverage2 = peakdata->RRaverage1;
			peakdata->pulse_counter++;
			peakdata->r_peak_index++;
			if (i == 31){

				printf("Searchback out of bounds\n");

			}




			break;

		}


	}
	return 0;
}
