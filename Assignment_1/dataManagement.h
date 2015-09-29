//Header file for the entire program (except for sensor.c)

#define DZ 33 //defines the length of our standard data arrays

typedef struct{

	int sensor_input;
	FILE *file_p;
	int raw_data[DZ]; 	//data array for data comming from the sensor
	int lp_data[DZ]; 	//data array, low pass filter (output)
	int hp_data[DZ]; 	//data array, high pass filter (output)
	int de_data[DZ];	//data array, derivative filter (output)
	int sq_data[DZ];	//data array, squaring filter (output)
	int mw_data[DZ];	//data array, moving window integration filter (output), used for peak detection.
	int ix;				//index counter, tracking the element to write to/from in the above data arrays.

	int PEAKS[2][DZ*10];  //stores the DZ*10 latest detected peaks
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
