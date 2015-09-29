#include <stdio.h>
#include <stdlib.h>
#include "dataManagement.h"


int avg_check(datastruct *dataset, int current_r_interval, int iterations) {
	int sumAvg1 = 0;
	int sumAvg2 = 0;
	int xn = dataset->PEAKS[1][(dataset->peak_index) % 330];
//The whole if statement is used for hen we havn't calculated a RRhigh, RRlow, RRaverage etc.
	if (dataset->RRhigh == 0) {

		//calculates average for both RRaverage1 and RRaverage2
		for (int i = 0; i < 8; i++) {
			sumAvg2 += dataset->RRintervals[i];
		}
		dataset->RRaverage2 = sumAvg2 / 8;
		dataset->RRaverage1 = sumAvg2 / 8;

		//Updates the values from the new RRaverage2
		dataset->RRlow = (dataset->RRaverage2 * 0.92);
		dataset->RRhigh = (dataset->RRaverage2 * 1.16);
		dataset->RRmiss = (dataset->RRaverage2 * 1.66);

//Adds peak as an R-peak
		dataset->R_PEAKS[0][dataset->r_peak_index%DZ] = (iterations - 1); // iteration count is stored

		dataset->R_PEAKS[1][dataset->r_peak_index%DZ] = dataset->PEAKS[1][dataset->peak_index%(DZ*10)];

		printf("R-peak at %i.%i s, value: %i \n",
					(dataset->R_PEAKS[0][(dataset->r_peak_index)%DZ])/250,
					(dataset->R_PEAKS[0][(dataset->r_peak_index)%DZ])%250*10/250,
					dataset->R_PEAKS[1][(dataset->r_peak_index)%DZ]);

		dataset->r_peak_index++;
		dataset->pulse_counter++;

		return 0;
	}
	//when the value is updated it will always reach the else branch.
	else {
		//checks if the temporary RR value fullfills the criterias
		if (current_r_interval > dataset->RRlow
				&& current_r_interval < dataset->RRhigh) {

			//Store as an R-peak
			dataset->R_PEAKS[0][dataset->r_peak_index%DZ] = (iterations - 1); // iteration count is stored

			dataset->R_PEAKS[1][dataset->r_peak_index%DZ] = dataset->PEAKS[1][dataset->peak_index%(DZ*10)];

			printf("R-peak at %i.%i s, value: %i \n",
						(dataset->R_PEAKS[0][(dataset->r_peak_index)%DZ])/250,
						(dataset->R_PEAKS[0][(dataset->r_peak_index)%DZ])%250*10/250,
						dataset->R_PEAKS[1][(dataset->r_peak_index)%DZ]);

			dataset->r_peak_index++;
			dataset->pulse_counter++;

			//store the interval i both arrays for both of the RRaverages
			dataset->RecentRR[dataset->RecentRR_index] = current_r_interval;

			dataset->RRintervals[dataset->RRintervals_index] =
					current_r_interval;
			//Updates the RRaverages values
			for (int i = 0; i < 8; i++) {
				sumAvg1 += dataset->RecentRR[dataset->RecentRR_index - i];
				sumAvg2 += dataset->RRintervals[dataset->RRintervals_index - i];
			}
			dataset->RRaverage1 = sumAvg1 / 8;

			dataset->RRaverage2 = sumAvg2 / 8;

			dataset->RecentRR_index++;

			dataset->RRintervals_index++;

			//Recalculates values from new R-peak and RRaverage2
			dataset->SPKF = 0.125 * xn + 0.875 * dataset->NPKF;

			dataset->RRlow = (dataset->RRaverage2 * 0.92);
			dataset->RRhigh = (dataset->RRaverage2 * 1.16);
			dataset->RRmiss = (dataset->RRaverage2 * 1.66);

			dataset->THRESHOLD1 = dataset->NPKF
					+ 0.25 * (dataset->SPKF - dataset->NPKF);

			dataset->THRESHOLD2 = dataset->THRESHOLD1 * 0.5;

			//Shows that there has been a heartbeat and we reset the counter
			dataset->RRmiss_count = 0;

			return 0;
		} // If it doesn't fullfill the criteria it will instantiate the searchback.
		else if (current_r_interval > dataset->RRmiss) {
			return 1;
		}

	}

	dataset->RRmiss_count++;
	return 0;

}
