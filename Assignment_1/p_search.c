#include <stdio.h>
#include <stdlib.h>
#include "dataManagement.h"


int p_search(datastruct *dataset){
	//we use an offset of 2, meaning we detect a peak 2 datapoints behind the current.
	int p_xleft 	= dataset->mw_data[(dataset->ix + DZ - 3)%DZ]; 	//the datapoint the the left of the off set
	int p_xmid 		= dataset->mw_data[(dataset->ix + DZ - 2)%DZ];	//the datapoint in question
	int p_xright 	= dataset->mw_data[(dataset->ix + DZ - 1)%DZ];	//the data point to the right of the one in question


	//Compare if the middle point is as high as the right, making sure that there actually is a point (!= 0):
	if (p_xmid == p_xright && p_xmid != 0){
		p_xright = dataset->mw_data[(dataset->ix+DZ)%DZ];	//in case mid == right, move the right point one step further.
	}
	if (p_xmid == p_xright){	//in case mid == right (still), mid is not a peak.
		return 0;
	}
	else if (p_xleft < p_xmid && p_xmid > p_xright){ //in case left < mid > right, mid is a peak
		return 1;
	} else{
		return 0;
	}

}
