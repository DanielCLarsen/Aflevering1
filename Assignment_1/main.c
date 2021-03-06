#include <stdio.h>
#include <stdlib.h>
#include "dataManagement.h"
#include "sensor.h"
#include "filters.h"
#include <time.h> //used in the analysis part of the program

// declaring global variable, filename for data load simulation.
static const char filename[] = "ECG.txt";

int main(int argc, char *argv[]) {
	datastruct dataset = { 0 }; //generates the struct object and initialises values at 0
	int iterations = 0; //test variable, not to be implemented in final version
	int RR; //temporary R-peak interval
	int pulse = 0;	//used to calculate the current pulse, (beats per minute) based on the last 5 seconds.
	int ix = 0;		//is set = dataset.ix every loop, shortens our code.
	clock_t start, end;
	//double cpu_time_used;//used in the analysis part of the program
	//double cputime[10000];//used in the analysis part of the program
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
	//start = clock();//used in the analysis part of the program
	while (iterations <= 10000) {

		ix = dataset.ix;
		//Sends the datapoint the the filters.
		dataset.raw_data[ix] = getNextData(dataset.file_p); //retrieves the next line of data from the sensor
		dataset.lp_data[ix] = lp_filter(&dataset); //filters the data through low-pass
		dataset.hp_data[ix] = hp_filter(&dataset); //filters through high-pass
		dataset.de_data[ix] = de_filter(&dataset); //filters through derivative
		dataset.sq_data[ix] = sq_filter(&dataset); //filters through squared
		dataset.mw_data[ix] = mw_filter(&dataset);



		if (p_search(&dataset)) { //if peak at datapoint

			addPeak(&dataset,iterations);

			//Checks if peak is an R-peak and calculates
			if (r_detecter(&dataset, (dataset.peak_index)%330)) {

				//adds the first 9 data points and calculates intervals for RRaverage1 and RRaverage2's arrays.
				if(dataset.R_PEAKS[1][8]==0){
					addRPeak(&dataset,iterations);
					if(dataset.R_PEAKS[1][(dataset.r_peak_index -1) % DZ] != 0){
					dataset.RRintervals[dataset.RRintervals_index] = calcRRInterval(&dataset,iterations);
					dataset.RecentRR[dataset.RecentRR_index] = dataset.RRintervals[dataset.RRintervals_index];
					dataset.RRintervals_index++;
					dataset.RecentRR_index++;
					}
					dataset.r_peak_index++;
					dataset.pulse_counter++;
				}
				else { //When the first 9 points are calculated it will always reach the else branch.

					RR = calcRRInterval(&dataset,iterations);

					//checks if the calculated peak goes through the criterias of being an R-peak
					//if not, avg_check will return 1, and the searchback will be called.
					if(avg_check(&dataset,RR,iterations)){
						searchback(&dataset,iterations);
					}
				}
			}
			dataset.peak_index++;
		}

		//checks for cardiac arrest:
		if (dataset.RRmiss_count == 5){
			printf("Warning: cardiac arrest! \n");
			dataset.RRmiss_count = 0;
		}

		dataset.ix = (ix + 1)%DZ; // increments the index for the data-arrays

		//used to control the amount of iterations:
		iterations++;
		dataset.pulse_time++;


		//prints the patients pulse every 1250 iterations (ie every 5 seconds)
		if (iterations%1250 == 0) {

			pulse = dataset.pulse_counter*12; //determines the pulse if the 5 seconds are extended to 60.

			printf("Pulse: %i \n",pulse);
			dataset.pulse[dataset.pulse_index%100] = pulse; //stores the pulse
			dataset.pulse_counter = 0;
			dataset.pulse_time = 0;
			dataset.pulse_index++;

			if (pulse == 0){
				dataset.RRmiss_count = 5; //if no pulse, cardiac arrest
			}
		}
	}	//end of while loop
	//end = clock();  //used in the analysis part of the program

	// cpu_time_used = ((double) (end-start))/CLOCKS_PER_SEC; //used in the analysis part of the program

	//printf("\n");
	//printf("CPU time: %f\n",cpu_time_used); //used in the analysis part of the program
	//printf("\n");

	return 0;
}
