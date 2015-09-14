<<<<<<< HEAD
typedef struct{
	int sensor_input;
	FILE *file_p;
	int dz;
	int raw_data[33]; //stores 13 measuring points
	int lp_data[33];
	int hp_data[33];
	int ix;
=======
int getNextData(file_p); // Please implement me in Sensor.c
>>>>>>> d826ee211b864796c0427df1e4ce7702b945599b

} datastruct;



int getNextData(FILE *file_p); // Please implement me in Sensor.c

int lp_filter(datastruct *dataset);
//
