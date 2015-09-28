#include <stdio.h>
#include <stdlib.h>
#include "dataManagement.h"


int p_search(datastruct *dataset){
	dataset->p_xleft 	= dataset->mw_data[(dataset->ix + DZ - 3)%DZ];
	dataset->p_xmid 	= dataset->mw_data[(dataset->ix + DZ - 2)%DZ];
	dataset->p_xright 	= dataset->mw_data[(dataset->ix + DZ - 1)%DZ];


	if (dataset->p_xmid == dataset->p_xright && dataset->p_xmid != 0){
		dataset->p_xright = dataset->mw_data[(dataset->ix+DZ)%DZ];
	}
	if (dataset->p_xmid == dataset->p_xright){
		return 0;
	}
	else if (dataset->p_xleft < dataset->p_xmid && dataset->p_xmid > dataset->p_xright){
		return 1;
	} else{
		return 0;
	}

}
