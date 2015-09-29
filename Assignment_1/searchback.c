#include <stdio.h>
#include <stdlib.h>
#include "dataManagement.h"

int searchback(datastruct *dataset,int iterations){


	for(int i=1; i<=(DZ*10); i++){
		if(dataset->PEAKS[1][(dataset->peak_index-i)%330] > dataset->THRESHOLD2){

			//stores the found peak as an r-peak:
			dataset->R_PEAKS[0][dataset->r_peak_index % DZ] = dataset->PEAKS[0][(dataset->peak_index-i)%330]; //iteration count is stored
			dataset->R_PEAKS[1][dataset->r_peak_index % DZ] = dataset->PEAKS[1][(dataset->peak_index-i)%330]; //stores the peak value

//prints the R-peak value and the time it occurs.
			printf("R-peak at %i.%i s, value: %i \n",
						(dataset->R_PEAKS[0][(dataset->r_peak_index)%DZ])/250,
						(dataset->R_PEAKS[0][(dataset->r_peak_index)%DZ])%250*10/250,
						dataset->R_PEAKS[0][(dataset->r_peak_index)%DZ]);


			//updates values, due to the new R-peak:
			int pn = dataset->R_PEAKS[1][dataset->r_peak_index % DZ];

			dataset->SPKF = 0.25*pn+0.75*dataset->SPKF;

			//Store RR value in array for RRaverage1.
			dataset->RecentRR[dataset->RecentRR_index]= (dataset->R_PEAKS[0][dataset->r_peak_index % DZ]-dataset->R_PEAKS[0][(dataset->r_peak_index-1)%DZ]);

			dataset->RecentRR_index = (dataset->RecentRR_index+1)%8;
			//Calculate RRaverage1
			for(int i=0; i < 8 ;i++){
				int Average2sum=0;
				Average2sum+=dataset->RecentRR[i];
				dataset->RRaverage1 = Average2sum/8;
			}
			//Updates the values from the new RRaverage1
			dataset->RRlow = (dataset->RRaverage1 * 0.92);
			dataset->RRhigh = (dataset->RRaverage1 * 1.16);
			dataset->RRmiss = (dataset->RRaverage1 * 1.66);

			//Updates values from the new peak.
			dataset->THRESHOLD1 = dataset->NPKF + 0.25*(dataset->SPKF - dataset->NPKF);

			dataset->THRESHOLD2 = dataset->THRESHOLD1*0.5;

			//Increments the counters
			dataset->pulse_counter++;
			dataset->r_peak_index++;
			dataset->RRmiss_count = 0;
			break;

		}


	}
	return 0;
}
