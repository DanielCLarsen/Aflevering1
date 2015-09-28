#define DZ 33 //defines the length of our data arrays

typedef struct{

	int sensor_input;
	FILE *file_p;
	int dz;
	int raw_data[DZ];
	int lp_data[DZ];
	int hp_data[DZ];
	int de_data[DZ];
	int sq_data[DZ];
	int mw_data[DZ];
	int ix;
	int time_delay;
	int p_xleft;
	int p_xmid;
	int p_xright;

	int PEAKS[2][330];
	int R_PEAKS[2][DZ];
	int NPKF;
	int SPKF;
	int THRESHOLD1;
	int THRESHOLD2;
	int time;
	int RRintervals[8];
	int RecentRR[8];
	int RRaverage1;
	int RRaverage2;
	int RRlow;
	int RRhigh;
	int RRmiss;
	int RecentRR_index;
	int r_peak_index;
	int peak_index;
	int RRintervals_index;
	int pulse_index;
	int pulse_counter;
	int pulse_time;
	int pulse[100]; //saves the latest 100 pulse values
	int RRmiss_count;
} datastruct;


void addPeak(datastruct *dataset, int iterations);

void addRPeak(datastruct *dataset, int iterations);

int calcRRInterval (datastruct *dataset, int iterations);

int p_search(datastruct *dataset);

int r_detecter(datastruct *dataset, int current_peak);

int avg_check(datastruct *dataset,int current_r_interval, int iterations);

int searchback(datastruct *dataset, int index);
