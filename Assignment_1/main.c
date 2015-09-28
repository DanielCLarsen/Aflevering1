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
	int timeelapsed = 0;	// elapsed time since last r-peak
	int RecentRPeaks_index = 0;
	int pulse = 0;
	int ix = 0;		//is set = dataset.ix every loop, shortens our code.
	int sum_RRintervals = 0;
	dataset.NPKF = 800;
	dataset.SPKF = 5000;
	dataset.THRESHOLD1 = 4000;
	dataset.THRESHOLD2 = 2000;
	dataset.NPKF = 800;
	dataset.SPKF = 5000;
	dataset.THRESHOLD1 = 4000;
	dataset.THRESHOLD2 = 2000;
	dataset.time = -5;
	//offset 0.1875s

	//opens the file:
	dataset.file_p = fopen(filename, "r");

	//filter loop:
	while (iterations <= 10000) {
		ix = dataset.ix;
		dataset.raw_data[ix] = getNextData(dataset.file_p); //retrieves the next line of data from the sensor
		dataset.lp_data[ix] = lp_filter(&dataset); //filters the data through low-pass
		dataset.hp_data[ix] = hp_filter(&dataset); //filters through high-pass
		dataset.de_data[ix] = de_filter(&dataset); //filters through derivative
		dataset.sq_data[ix] = sq_filter(&dataset); //filters through squared
		dataset.mw_data[ix] = mw_filter(&dataset);



		if (p_search(&dataset)) { //if peak at datapoint
			addPeak(&dataset,iterations);

			//Checks if peak is an R-peak and calculates
			if (r_detecter(&dataset, (dataset.peak_index)%330)) { // returns 1 if the peak is an rpeak (function cll also updates peak struct)

				if(dataset.R_PEAKS[1][8]==0){
					addRPeak(&dataset,iterations);
					if(dataset.R_PEAKS[1][(dataset.r_peak_index -1) % DZ] != 0){
						calcRRInterval(&dataset,RecentRPeaks_index,iterations);
						RecentRPeaks_index++;
					}
				}

				else { //if the previous point in the r_peaks[] is not 0

					calcRRInterval(&dataset,RecentRPeaks_index,iterations);


					for (int i = 0; i < 8; i++) {
						sum_RRintervals += dataset.RRintervals[i];

					}
					dataset.RRaverage2 = sum_RRintervals / 8;
					sum_RRintervals = 0;


					if(avg_check(&dataset,dataset.RRintervals[dataset.RRintervals_index])){
						searchback(&dataset,iterations);

					}


				}



				//addRPeak(&dataset,iterations);

				if (dataset.R_PEAKS[1][dataset.r_peak_index % DZ] < dataset.THRESHOLD2){
					printf("Warning: heart beat too weak!\n");
				}



					RecentRPeaks_index = (RecentRPeaks_index + 1) % 8;


				//}
				dataset.pulse_counter++;
				dataset.r_peak_index++;
			}


			dataset.peak_index++;
		}

		//checks for cardiac arrest:
		if (dataset.RRmiss_count == 5){
			printf("Warning: cardiac arrest! \n");
			dataset.RRmiss_count = 0;
		}

		dataset.ix = (ix + 1) % DZ; // increments the index for the data-arrays

		//used to control the amount of iterations:
		iterations++;
		dataset.pulse_time++;


		//prints the patients pulse every 1250 iterations (ie every 5 seconds)
		if (iterations%1250 == 0) {
			pulse = (dataset.pulse_counter/(dataset.pulse_time/250))*60;
			printf("Pulse: %i \n",pulse);
			dataset.pulse[dataset.pulse_index%100] = pulse;
			dataset.pulse_counter = 0;
			dataset.pulse_time = 0;
			dataset.pulse_index++;
			if (pulse == 0){
				dataset.RRmiss_count = 5;
			}
		}


}
	printf("test");
	return 0;
}
