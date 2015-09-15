#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int de_filter(datastruct *dataset){
	int xn = dataset->hp_data[(dataset->ix)%dataset->dz];
	int xn1 = dataset->hp_data[(dataset->ix+dataset->dz-1)%dataset->dz];
	int xn3 = dataset->hp_data[(dataset->ix+dataset->dz-3)%dataset->dz];
	int xn4 = dataset->hp_data[(dataset->ix+dataset->dz-4)%dataset->dz];

	//printf("xn = %i ",xn);
	//printf("xn1 = %i ",xn1);
	//printf("xn3 = %i ",xn3);
	//printf("xn4 = %i \n",xn4);

	return (2*xn+xn1-xn3-2*xn4)/8;
}
