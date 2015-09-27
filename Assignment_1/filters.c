#include <stdio.h>
#include <stdlib.h>
#include "dataManagement.h"
#include "filters.h"


int lp_filter(datastruct *dataset){
	int yn1 = dataset->lp_data[(dataset->ix+dataset->dz-1)%dataset->dz];
	int yn2 = dataset->lp_data[(dataset->ix+dataset->dz-2)%dataset->dz];
	int xn = dataset->raw_data[(dataset->ix)%dataset->dz];
	int xn6 = dataset->raw_data[(dataset->ix+dataset->dz-6)%dataset->dz];
	int xn12 = dataset->raw_data[(dataset->ix+dataset->dz-12)%dataset->dz];
	return 2*yn1-yn2+(xn-2*xn6+xn12)/32;
}

int hp_filter(datastruct *dataset){
	int yn1 = dataset->hp_data[(dataset->ix+dataset->dz-1)%dataset->dz];
	int xn = dataset->lp_data[(dataset->ix)%dataset->dz];
	int xn16 = dataset->lp_data[(dataset->ix+dataset->dz-16)%dataset->dz];
	int xn17 = dataset->lp_data[(dataset->ix+dataset->dz-17)%dataset->dz];
	int xn32 = dataset->lp_data[(dataset->ix+dataset->dz-32)%dataset->dz];
	return yn1-xn/32+xn16-xn17+xn32/32;
}

int de_filter(datastruct *dataset){
	int xn = dataset->hp_data[(dataset->ix)%dataset->dz];
	int xn1 = dataset->hp_data[(dataset->ix+dataset->dz-1)%dataset->dz];
	int xn3 = dataset->hp_data[(dataset->ix+dataset->dz-3)%dataset->dz];
	int xn4 = dataset->hp_data[(dataset->ix+dataset->dz-4)%dataset->dz];
	return (2*xn+xn1-xn3-2*xn4)/8;
}

int sq_filter(datastruct *dataset){
	int xn = dataset->de_data[(dataset->ix)%dataset->dz];
	return xn*xn;
}

int mw_filter(datastruct *dataset){
	int N = 30;
	int i;
	int sum = 0;
	for (i=1;i<=30;i=i+1){
		sum = sum+(dataset->sq_data[(dataset->ix+dataset->dz-(N-i))%dataset->dz])/N;
	}
	return sum;
}






