#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int getNextData(void){
	int value;
	fscanf(file,"%i",&value);

	return value;
}
