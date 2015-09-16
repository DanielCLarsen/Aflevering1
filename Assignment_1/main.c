#include <stdio.h>
#include "sensor.h"

// declaring global variable, filename for data load simulation.
static const char filename[] = "ECG.txt";

int main(int argc, char *argv[])
{
	datastruct dataset = {0}; //generates the struct object and initialises values at 0
	peakstruct peakdata = {0}; // peak object
	int iterations = 0; //test variable, not to be implemented in final version
	int p_search_offset = 3;
	int peak_index = 0;
	dataset.ix = 0; //index tracker for reading/writing data-array elements
	dataset.dz = 33; //tracker of the array lengths.
	peakdata.NPKF = 800;
	peakdata.SPKF = 5000;
	peakdata.THRESHOLD1 = 4000;
	peakdata.THRESHOLD2 = 2000;

	//opens the file:
	dataset.file_p = fopen(filename,"r");

	//filter loop:
	while(iterations <= 500){
		dataset.raw_data[dataset.ix] = getNextData(dataset.file_p); //retrieves the next line of data from the sensor
		dataset.lp_data[dataset.ix]=lp_filter(&dataset); //filters the data through low-pass
		dataset.hp_data[dataset.ix]=hp_filter(&dataset); //filters through high-pass
		dataset.de_data[dataset.ix]=de_filter(&dataset); //filters through derivative
		dataset.sq_data[dataset.ix]=sq_filter(&dataset); //filters through squared
		dataset.mw_data[dataset.ix]=mw_filter(&dataset);

		//printf("\n %i ",dataset.ix);
		//printf("Raw: %i ",dataset.raw_data[dataset.ix]);
		//printf("Low: %i ",dataset.lp_data[dataset.ix]);
		//printf("High: %i ",dataset.hp_data[dataset.ix]);
		//printf("Derivative: %i ",dataset.de_data[dataset.ix]);
		//printf("Squared: %i ",dataset.sq_data[dataset.ix]);
		//printf("Moving: %i ",dataset.mw_data[dataset.ix]);

		//peak detection:

		dataset.p_xleft = dataset.mw_data[(dataset.ix+dataset.dz-p_search_offset)%dataset.dz];
		dataset.p_xmid = dataset.mw_data[(dataset.ix+dataset.dz-p_search_offset+1)%dataset.dz];
		dataset.p_xright = dataset.mw_data[(dataset.ix+dataset.dz-p_search_offset+2)%dataset.dz];

		if (p_search(&dataset)){
			peakdata.PEAKS[0][peak_index%dataset.dz]=(iterations-1);
			peakdata.PEAKS[1][peak_index%dataset.dz]=dataset.mw_data[((dataset.ix+dataset.dz-p_search_offset+1)%dataset.dz)];
			r_detect(&peakdata,peak_index);
			printf("peak at: ix = %i, value of peak = %i \n",peakdata.PEAKS[0][peak_index],peakdata.PEAKS[1][peak_index]);
			peak_index = (peak_index+1);
		}

		//dataset.peaks[(dataset.ix+dataset.dz-p_search_offset+1)%dataset.dz] = p_search(&dataset);

		dataset.ix = (dataset.ix+1)%dataset.dz; // increments the index for the data-arrays

		//used to control the amount of iterations:
		iterations++;

	}
	return 0;
}
