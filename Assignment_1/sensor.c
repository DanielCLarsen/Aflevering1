#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int getNextData(FILE *file_p){

	int value;

	fscanf(file_p,"%i",&value);

	return value;
}
