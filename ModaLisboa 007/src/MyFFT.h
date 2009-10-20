#pragma once

#include "ofMain.h"
#include "fft.h"
#include <limits>

class testApp;

class MyFFT:public fft{
protected:
	int numBands;
	int numWindows;
	int bufferSize;
	int bufferCounter;
	float avg_power;
	vector<float>magnitude;
	vector<float>phase;
	vector<float>power;
	vector<vector<float> >freq;
	vector<vector<float> >freq_phase;
	vector<float> left;
	vector<float> right;
	vector<float> mix;
	bool bNormalizeValues;
	
public:
	MyFFT();
	~MyFFT();
	void setup(testApp* appPtr, int _numBands, bool _bNormalized = true); 
	float getBand(int _band);
	vector<float>& getBands();
	float getAveragePower();
	float getAverageInRange(int minBand, int maxBand);
	void update(float *_input, int _bufferSize);
	void normalize();
	float getMax();
	float getMin();
	void scale(float val);
	int getNumBands();
	int getNumWindows();
	int getBufferSize();
};