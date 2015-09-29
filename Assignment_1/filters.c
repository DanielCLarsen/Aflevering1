#include <stdio.h>
#include <stdlib.h>
#include "dataManagement.h"
#include "filters.h"

//All filters fetch data from the datastruct using pointers. Storing them in temporary variables for
//making it easier to work it.
int lp_filter(datastruct *dataset){
	int yn1 = dataset->lp_data[(dataset->ix+DZ-1)%DZ];
	int yn2 = dataset->lp_data[(dataset->ix+DZ-2)%DZ];
	int xn = dataset->raw_data[(dataset->ix)%DZ];
	int xn6 = dataset->raw_data[(dataset->ix+DZ-6)%DZ];
	int xn12 = dataset->raw_data[(dataset->ix+DZ-12)%DZ];
	return 2*yn1-yn2+(xn-2*xn6+xn12)/32;
}

int hp_filter(datastruct *dataset){
	int yn1 = dataset->hp_data[(dataset->ix+DZ-1)%DZ];
	int xn = dataset->lp_data[(dataset->ix)%DZ];
	int xn16 = dataset->lp_data[(dataset->ix+DZ-16)%DZ];
	int xn17 = dataset->lp_data[(dataset->ix+DZ-17)%DZ];
	int xn32 = dataset->lp_data[(dataset->ix+DZ-32)%DZ];
	return yn1-xn/32+xn16-xn17+xn32/32;
}

int de_filter(datastruct *dataset){
	int xn = dataset->hp_data[(dataset->ix)%DZ];
	int xn1 = dataset->hp_data[(dataset->ix+DZ-1)%DZ];
	int xn3 = dataset->hp_data[(dataset->ix+DZ-3)%DZ];
	int xn4 = dataset->hp_data[(dataset->ix+DZ-4)%DZ];
	return (2*xn+xn1-xn3-2*xn4)/8;
}

int sq_filter(datastruct *dataset){
	int xn = dataset->de_data[(dataset->ix)%DZ];
	return xn*xn;
}

int mw_filter(datastruct *dataset){
	int N = 30;
	int i;
	int sum = 0;
	for (i=1;i<=30;i=i+1){
		sum = sum+(dataset->sq_data[(dataset->ix+DZ-(N-i))%DZ])/N;
	}
	return sum;
}





