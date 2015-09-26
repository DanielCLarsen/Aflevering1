typedef struct{

	int sensor_input;
	FILE *file_p;
	int dz;
	int dpeaks;
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
	int peak_index;
	int PEAKS[2][300];
	int R_PEAKS[2][33];
	int NPKF;
	int SPKF;
	int THRESHOLD1;
	int THRESHOLD2;
	int time;
	int RRintervals[8];
	int RRaverage1;
	int RRaverage2;
	int RRlow;
	int RRhigh;
	int RRmiss;
	int r_peak_index;
	int RRintervals_index;
	int pulse_counter;

} peakstruct;


int getNextData(FILE *file_p);

int lp_filter(datastruct *dataset);

int hp_filter(datastruct *dataset);

int de_filter(datastruct *dataset);

int sq_filter(datastruct *dataset);

int mw_filter(datastruct *dataset);

int p_search(datastruct *dataset);

int r_detecter(peakstruct *peakdata, int current_peak);

int avg_check(peakstruct *peakdata,int current_r_interval);

int searchback(peakstruct *peakdata, datastruct *dataset,int iterations);
