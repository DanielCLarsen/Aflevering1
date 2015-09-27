#include <stdio.h>
#include <stdlib.h>
#include "dataManagement.h"
#include "sensor.h"
#include "filters.h"

// declaring global variable, filename for data load simulation.
static const char filename[] = "ECG.txt";



int main(int argc, char *argv[]) {
	datastruct dataset = { 0 }; //generates the struct object and initialises values at 0
	int iterations = 0; //test variable, not to be implemented in final version
	int timeelapsed = 0;	// elapsed time time since last r-peak
	int CA = 0; //flag for cardic arrest
	int RecentRPeaks_index = 0;
	dataset.dpeaks = 300;
	dataset.ix = 0; //index tracker for reading/writing data-array elements
	dataset.dz = 33; //tracker of the array lengths.
	dataset.NPKF = 800;
	dataset.SPKF = 5000;
	dataset.THRESHOLD1 = 4000;
	dataset.THRESHOLD2 = 2000;
	dataset.NPKF = 800;
	dataset.SPKF = 5000;
	dataset.THRESHOLD1 = 4000;
	dataset.THRESHOLD2 = 2000;
	dataset.time = 5;
	//offset 0.1875s

	//opens the file:
	dataset.file_p = fopen(filename, "r");

	//filter loop:
	while (iterations <= 5000) {
		dataset.raw_data[dataset.ix] = getNextData(dataset.file_p); //retrieves the next line of data from the sensor
		dataset.lp_data[dataset.ix] = lp_filter(&dataset); //filters the data through low-pass
		dataset.hp_data[dataset.ix] = hp_filter(&dataset); //filters through high-pass
		dataset.de_data[dataset.ix] = de_filter(&dataset); //filters through derivative
		dataset.sq_data[dataset.ix] = sq_filter(&dataset); //filters through squared
		dataset.mw_data[dataset.ix] = mw_filter(&dataset);

		if (p_search(&dataset)) { //if peak at datapoint
			addPeak(&dataset,iterations);

			//Checks if peak is an R-peak and calculates
			if (r_detecter(&dataset, dataset.peak_index)) { // returns 1 if the peak is an rpeak (function cll also updates peak struct)
				addRPeak(&dataset,iterations);

				if (dataset.R_PEAKS[1][(dataset.r_peak_index - 1) % dataset.dz] != 0) { //if the previous point in the r_peaks[] is not 0

					calcRRInterval(&dataset,RecentRPeaks_index,iterations);

					RecentRPeaks_index = (RecentRPeaks_index + 1) % 8;

					if (dataset.RRintervals[7] != 0) {
						for (int i = 0; i < 8; i++) {
							int Average2sum = 0;
							Average2sum += dataset.RRintervals[i];
							dataset.RRaverage2 = Average2sum / 8;
						}
						if(avg_check(&dataset,dataset.RRintervals[dataset.RRintervals_index])&&CA == 0){
							searchback(&dataset,&dataset,iterations);

						}
					}
				}
				dataset.pulse_counter++;
				dataset.r_peak_index++;
			}
				dataset.r_peak_index++;

			CA = 0; //resets the CA flag
			//checks for heartstop:
			if (dataset.RRaverage2){
			 timeelapsed = iterations-dataset.R_PEAKS[0][dataset.r_peak_index-1];
			if (dataset.RRaverage2*5<timeelapsed)
				printf("Warning: cardiac arrest!, %i \n", timeelapsed);
				//CA = 1;

			}
			dataset.peak_index++;
		}
		dataset.ix = (dataset.ix + 1) % dataset.dz; // increments the index for the data-arrays

		//used to control the amount of iterations:
		iterations++;
		if (iterations % 10 == 0) { //increments time every 10 iterations ie. every 1/25 sec.
			dataset.time++;

		if (iterations%1250 == 0) { //prints the patients pulse every 1250 iterations (ie every 5 seconds)
			printf("Pulse: %i \n",dataset.pulse_counter*12);
			dataset.pulse_counter = 0;
		}

	}
}
	return 0;
}
