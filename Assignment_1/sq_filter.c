#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int sq_filter(datastruct *dataset){
	int xn = dataset->de_data[(dataset->ix)%dataset->dz];

	//printf("xn = %i ",xn);


	return xn*xn;
}
