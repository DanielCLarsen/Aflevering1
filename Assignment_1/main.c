#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

// declaring global variable, filename for data load simulation.
static const char filename[] = "ECG.txt";

int main(int argc, char *argv[]) {
	datastruct dataset = { 0 }; //generates the struct object and initialises values at 0
	peakstruct peakdata = { 0 }; // peak object
	int iterations = 0; //test variable, not to be implemented in final version
	int p_search_offset = 3;
	int peak_index = 0;
	int r_peak_index = 0;
	int RecentRPeaks_index = 0;
	int RecentPeaks_index = 0;
	dataset.ix = 0; //index tracker for reading/writing data-array elements
	dataset.dz = 33; //tracker of the array lengths.
	peakdata.NPKF 		= 800;
	peakdata.SPKF 		= 5000;
	peakdata.THRESHOLD1 = 4000;
	peakdata.THRESHOLD2 = 2000;
	peakdata.NPKF = 800;
	peakdata.SPKF = 5000;
	peakdata.THRESHOLD1 = 4000;
	peakdata.THRESHOLD2 = 2000;
	peakdata.time = 5;
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


		//peak detection:

		dataset.p_xleft = dataset.mw_data[(dataset.ix + dataset.dz
				- p_search_offset) % dataset.dz];
		dataset.p_xmid = dataset.mw_data[(dataset.ix + dataset.dz
				- p_search_offset + 1) % dataset.dz];
		dataset.p_xright = dataset.mw_data[(dataset.ix + dataset.dz
				- p_search_offset + 2) % dataset.dz];

		if (p_search(&dataset)) { //if peak at datapoint
			peakdata.PEAKS[0][peak_index % dataset.dz] = (iterations - 1); // iteration count is stored
			peakdata.PEAKS[1][peak_index % dataset.dz] =
					dataset.mw_data[((dataset.ix + dataset.dz - p_search_offset
							+ 1) % dataset.dz)]; //stores the peak value


			//Checks if peak is an R-peak and calculates
			if (r_detecter(&peakdata, peak_index)) { // returns 1 if the peak is an rpeak (function cll also updates peak struct)
				peakdata.R_PEAKS[0][r_peak_index % dataset.dz] =
						(iterations - 1); // iteration count is stored
				peakdata.R_PEAKS[1][r_peak_index % dataset.dz] =
						peakdata.PEAKS[1][peak_index % dataset.dz];
				printf("R_peak at: ix = %i, value of r_peak = %i \n",
						peakdata.R_PEAKS[0][r_peak_index],
						peakdata.R_PEAKS[1][r_peak_index]);

				if(peakdata.R_PEAKS[1][(r_peak_index-1)%dataset.dz] != 0){ //if the previous point in the r_peaks[] is not 0

					peakdata.RRintervals2[RecentRPeaks_index]= (iterations-peakdata.R_PEAKS[0][(r_peak_index-1)%dataset.dz]);

				RecentRPeaks_index = (RecentRPeaks_index+1)%8;
					if(peakdata.RRintervals2[7]!=0){
						for(int i=0; i < 8 ;i++){
							int Average2sum=0;
							Average2sum+=peakdata.RRintervals2[i];
							peakdata.RRaverage2 = Average2sum/8;

						}
						if(avg_check(&peakdata,peakdata.RRintervals2[RecentRPeaks_index])){


						}

						printf("Average2 = %i \n",peakdata.RRaverage2);
					}


				}



				r_peak_index++;
			}

			peak_index = (peak_index + 1);
		}

		//peakdata.peaks[(dataset.ix+dataset.dz-p_search_offset+1)%dataset.dz] = p_search(&dataset);

		dataset.ix = (dataset.ix + 1) % dataset.dz; // increments the index for the data-arrays

		//used to control the amount of iterations:
		iterations++;
		if (iterations % 10 == 0) { //increments time every 10 iterations ie. every 1/25 sec.
			peakdata.time++;
		}

	}
	return 0;
}
