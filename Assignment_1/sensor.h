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
	int p_xleft;
	int p_xmid;
	int p_xright;


} datastruct;

typedef struct{
	int PEAKS[2][33];
	int R_PEAKS[2][33];
 int NPKF;
int SPKF;
int THRESHOLD1;
int THRESHOLD2;

} peakstruct;


int getNextData(FILE *file_p);

int lp_filter(datastruct *dataset);

int hp_filter(datastruct *dataset);

int de_filter(datastruct *dataset);

int sq_filter(datastruct *dataset);

int mw_filter(datastruct *dataset);

int p_search(datastruct *dataset);

void r_detecter(peakstruct *peakdata, int current_peak);
