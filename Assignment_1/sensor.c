#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int getNextData(){
	int value;


	static const char filename[] = "ECG.txt";
	FILE *file = fopen(filename,"r");
	if (fscanf(file,"%i",&value) != EOF){
	} else{
		rewind(file);
		fscanf(file,"%i",&value);
	}
	return value;
}
