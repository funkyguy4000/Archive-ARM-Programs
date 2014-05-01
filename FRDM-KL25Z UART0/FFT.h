//Header file for FFT functions
#include <math.h>
#include "ADC.h"
#include "kiss_fft.h"

#define SAMPLE_SIZE	32

typedef struct{				//Pile
	uint16_t list[16];
} Pile;

static double xAxis = 0;
static int sampleCount = 0;
static double pieSteps;
static double fullSinWave = 3.14159265 * 2;
static double sampleRate = 44100;

Pile MyPile;


kiss_fft_cpx *fin;
kiss_fft_cpx *fout;



kiss_fft_cfg mycfg;



	



Pile Build_Pile(void){
	for(int i = 0; i<1024; i++){
		pieSteps = fullSinWave/(sampleRate);
		xAxis += pieSteps;
	}
	return MyPile;
}


void FFT_Init(void){
	mycfg = kiss_fft_alloc(1024,0,NULL,NULL);
}

void set_SampleRate(double rate){
	sampleRate = rate;
}

double get_SampleRate(void){
	return sampleRate;
}

kiss_fft_cpx run_FFT(void){
	Pile DataStream = Build_Pile();
	for (int i = 0; i< SAMPLE_SIZE; i++){
		fin[i].r = DataStream.list[i];
		fin[i].i = DataStream.list[i];
	}
	kiss_fft(mycfg, fin, fout);
	
	return *fout;
}

