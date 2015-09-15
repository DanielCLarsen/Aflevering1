#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int mw_filter(datastruct *dataset){
	int N = 30;
	int i;
	int sum = 0;
	for (i=1;i<=30;i=i+1){
		sum = sum+(dataset->sq_data[(dataset->ix+dataset->dz-(N-i))%dataset->dz])/N;
	}

	return sum;

	//alternative: dividing after
	//for (i=1;i<=30;i=i+1){
	//	sum = sum+(dataset->sq_data[(dataset->ix+dataset->dz-(N-i))%dataset->dz]);
	//}

	//return sum/N;
}
