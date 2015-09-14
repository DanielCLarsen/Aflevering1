typedef struct{
	int sensor_input;
	FILE *file_p;
	int dz;
	int raw_data[33]; //stores 13 measuring points
	int lp_data[33];
	int hp_data[33];
	int sq_data[33];
	int ix;

} datastruct;



int getNextData(FILE *file_p); // Please implement me in Sensor.c

int lp_filter(datastruct *dataset);

int hp_filter(datastruct *dataset);
