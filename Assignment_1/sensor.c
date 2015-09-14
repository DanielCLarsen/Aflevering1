#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

<<<<<<< HEAD
int getNextData(FILE *file_p){

	int value;

	fscanf(file_p,"%i",&value);
=======
int getNextData(FILE *file){
	int value;
		fscanf(file,"%i",&value);
>>>>>>> d826ee211b864796c0427df1e4ce7702b945599b

	return value;
}
