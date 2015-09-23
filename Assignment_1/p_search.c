#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"


int p_search(datastruct *dataset){
	if (dataset->p_xmid == dataset->p_xright && dataset->p_xmid != 0){
		dataset->p_xright = dataset->mw_data[(dataset->ix+dataset->dz)%dataset->dz];
	}
	if (dataset->p_xmid == dataset->p_xright){
		return 0;
	}
	else if (dataset->p_xleft < dataset->p_xmid && dataset->p_xmid > dataset->p_xright){
		return 1;
	} else
		return 0;




}
