#include <stdio.h>
#include "sensor.h"

struct data{
	int sensor_input;
};

/* main : The primary unction. */
int main(int argc, char *argv[])
{
	struct data test = {0};
	static const char filename[] = "ECG.txt";
	FILE *file = fopen(filename,"r");
	test.sensor_input = getNextData();
	printf("%i",test.sensor_input);
	return 0;
}
