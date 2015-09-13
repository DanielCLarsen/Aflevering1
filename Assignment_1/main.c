#include <stdio.h>
#include "sensor.h"

struct data{
	int sensor_input;
};
struct low_pass_filter{

};


int main(int argc, char *argv[])
{
	static const char filename[] = "ECG.txt";
	FILE *file = fopen(filename,"r");
	struct data test = {0};
	test.sensor_input = getNextData(file);

	while(test.sensor_input != EOF){
		printf("%i \n",test.sensor_input);
		test.sensor_input = getNextData(file);
	}

	return 0;
}
