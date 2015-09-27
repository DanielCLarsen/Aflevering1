#include <stdio.h>
#include <stdlib.h>
#include "dataManagement.h"


int p_search(datastruct *dataset){
	int p_search_offset = 3;

	dataset->p_xleft = dataset->mw_data[(dataset->ix + dataset->dz
			- p_search_offset) % dataset->dz];
	dataset->p_xmid = dataset->mw_data[(dataset->ix + dataset->dz
			- p_search_offset + 1) % dataset->dz];
	dataset->p_xright = dataset->mw_data[(dataset->ix + dataset->dz
			- p_search_offset + 2) % dataset->dz];


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
