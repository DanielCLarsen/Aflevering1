#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int lp_filter(datastruct *dataset){
	int segment1;
	int segment2;
	int yn1 = dataset->lp_data[(dataset->ix+dataset->dz-1)%dataset->dz];
	int yn2 = dataset->lp_data[(dataset->ix+dataset->dz-2)%dataset->dz];
	int xn = dataset->raw_data[(dataset->ix)%dataset->dz];
	int xn6 = dataset->raw_data[(dataset->ix+dataset->dz-6)%dataset->dz];
	int xn12 = dataset->raw_data[(dataset->ix+dataset->dz-12)%dataset->dz];

	segment1 = 2*yn1-yn2;

	segment2 = (xn-2*xn6+xn12)/32;
	//printf("yn1 = %i ",yn1);
	//printf("yn2 = %i ",yn2);
	//printf("xn = %i ",xn);
	//printf("xn6 = %i ",xn6);
	//printf("xn12 = %i \n",xn12);
	//printf("%i + %i = ",segment1,segment2);

	return segment1+segment2;
}
