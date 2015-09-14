#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int hp_filter(datastruct *dataset){
	int yn1 = dataset->hp_data[(dataset->ix+dataset->dz-1)%dataset->dz];
	int xn = dataset->lp_data[(dataset->ix)%dataset->dz];
	int xn16 = dataset->lp_data[(dataset->ix+dataset->dz-16)%dataset->dz];
	int xn17 = dataset->lp_data[(dataset->ix+dataset->dz-17)%dataset->dz];
	int xn32 = dataset->lp_data[(dataset->ix+dataset->dz-32)%dataset->dz];

	//printf("yn1 = %i ",yn1);
	//printf("xn = %i ",xn);
	//printf("xn16 = %i ",xn16);
	//printf("xn17 = %i ",xn17);
	//printf("xn32 = %i \n",xn32);

	return yn1-xn/32+xn16-xn17+xn32/32;
}
