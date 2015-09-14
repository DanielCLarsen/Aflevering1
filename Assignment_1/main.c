#include <stdio.h>
#include "sensor.h"

// declaring global variable, filename for data load simulation.
static const char filename[] = "ECG.txt";

int main(int argc, char *argv[])
{
	datastruct dataset = {0};
	int test = 1;
	int increment = 0;
	dataset.ix = 0;
	dataset.dz = 33;

	//opens the file
	dataset.file_p = fopen(filename,"r");

	//asks getNextData to retrieve the next line of data from file.

	while(test == 1){
		dataset.raw_data[dataset.ix] = getNextData(dataset.file_p);
		dataset.lp_data[dataset.ix]=lp_filter(&dataset);
		dataset.hp_data[dataset.ix]=hp_filter(&dataset);
		printf("high pass: %i, raw: %i , low pass: %i, ix: %i\n",dataset.hp_data[dataset.ix],dataset.raw_data[dataset.ix],dataset.lp_data[dataset.ix],dataset.ix);
		dataset.ix = (dataset.ix+1)%dataset.dz;
		increment = increment +1;
		if (increment == dataset.dz*2){
			test = 0;
		}
	}
	return 0;
}
