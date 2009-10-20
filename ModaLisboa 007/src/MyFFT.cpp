

#include "MyFFT.h"
#include "testApp.h"

MyFFT::MyFFT(){
	numBands = 0;
	numWindows = 0;
	bufferSize = 0;
	bufferCounter = 0;
	bNormalizeValues = true;
}


MyFFT::~MyFFT(){
	magnitude.clear();
	phase.clear();
	power.clear();
	for(int i=0; i<numWindows; i++){
		freq[i].clear();
		freq_phase[i].clear();
	}
	freq.clear();
	freq_phase.clear();
}

void MyFFT::setup(testApp*appPtr, int _numBands, bool _bNormalizeValues){
	numBands = _numBands;
	bNormalizeValues = _bNormalizeValues;
	bufferSize = numBands*2;
	numWindows = 80;
	magnitude.resize(bufferSize);
	phase.resize(bufferSize);
	power.resize(bufferSize);
	for(int i=0; i<bufferSize; i++){
		magnitude[i] = 0.0f;
		phase[i] = 0.0f;
		power[i] = 0.0f;
	}
	avg_power = 0.0f;
	freq.resize(numWindows);
	freq_phase.resize(numWindows);
	for(int i=0; i<numWindows; i++){
		freq[i].resize(numBands);
		freq_phase[i].resize(numBands);
		for(int j=0; j<numBands; j++){
			freq[i][j] = 0.0f;
			freq_phase[i][j] = 0.0f;
		}
	}
	left.resize(bufferSize);
	right.resize(bufferSize);
	mix.resize(bufferSize);
	
	ofSoundStreamSetup(0,2, appPtr, 44100,bufferSize, 4);
}

float MyFFT::getBand(int _band){
	if(_band < numBands){
		return magnitude[_band];
	} else {
		printf("MyFFT::getBand - band index out of scope\n");
		return 0;
	}
}

vector<float>& MyFFT::getBands(){
	return magnitude;
}

float MyFFT::getAveragePower(){
	return(avg_power);
}

float MyFFT::getAverageInRange(int minBand, int maxBand){
	minBand = MAX(0, minBand);
	maxBand = MIN(numBands, maxBand);
	float max = 0;
	float avg = 0;
	for(int i=minBand; i<maxBand; i++){
		avg += magnitude[i];
		if(magnitude[i] > max) max = magnitude[i];
	}
	avg /= maxBand - minBand;
	return avg;
}

void MyFFT::update(float *_input, int _bufferSize){
	for (int i = 0; i < _bufferSize; i++){
		left[i] = _input[i*2];
		right[i] = _input[i*2+1];
		mix[i] = (left[i] + right[i])/2;
	}
	powerSpectrum(0, numBands, &mix[0], bufferSize, &magnitude[0], &phase[0], &power[0], &avg_power);
	if(bNormalizeValues){
		float runningMax = 1.0f; 
		float agcAdapt = 0.1f; 

		float max = 0;
		for(int i = 0; i < numBands; i++) {
			if(magnitude[i] > max) {
				max = magnitude[i];
			}
		}
		if(max > runningMax) {
			runningMax = max;
		} else {
			runningMax = (agcAdapt * max) + ((1.0f - agcAdapt) * runningMax);
		}
		for(int i=0; i<numBands; i++) {
			magnitude[i] /= runningMax;
		}		
	}
}

float MyFFT::getMax(){
	float max = 0;
	for(int i=0; i<numBands; i++){
		if(magnitude[i] > max){
			max = magnitude[i];
		}
	}
	return max;
}

float MyFFT::getMin(){
	float min = numeric_limits<float>::max();
	for(int i=0; i<numBands; i++){
		if(magnitude[i] < min) min = magnitude[i];
	}
	return min;
}

void MyFFT::scale(float val){
	for(int i=0; i<numBands; i++){
		magnitude[i] *= val;
	}
}

int MyFFT::getNumBands(){
	return numBands;
}

int MyFFT::getNumWindows(){
	return numWindows;
}

int MyFFT::getBufferSize(){
	return bufferSize;
}




