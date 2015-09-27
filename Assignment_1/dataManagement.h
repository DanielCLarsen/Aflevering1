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

//peakdata
	int dpeaks;
	int PEAKS[2][33];
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
	int peak_index;
	int RRintervals_index;
	int pulse_counter;
} datastruct;


void addPeak(datastruct *peakdata, int iterations);

void addRPeak(datastruct *peakdata, int iterations);

void calcRRInterval (datastruct *peakdata, int RecentRPeaks_index, int iterations);

int p_search(datastruct *dataset);

int r_detecter(datastruct *peakdata, int current_peak);

int avg_check(datastruct *peakdata,int current_r_interval);

int searchback(datastruct *peakdata, datastruct *dataset, int index);
