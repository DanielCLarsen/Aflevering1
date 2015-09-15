typedef struct{
	int sensor_input;
	FILE *file_p;
	int dz;
	int raw_data[33];
	int lp_data[33];
	int hp_data[33];
	int de_data[33];
	int sq_data[33];
	int mw_data[33];
	int ix;
	int time_delay;

} datastruct;


int getNextData(FILE *file_p);

int lp_filter(datastruct *dataset);

int hp_filter(datastruct *dataset);

int de_filter(datastruct *dataset);

int sq_filter(datastruct *dataset);

int mw_filter(datastruct *dataset);
