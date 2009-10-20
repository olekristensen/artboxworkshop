#include "Utils.h"

static ofxPerlin _noise;


float getNoise(float x){
	return _noise.noise(x);
}

float getNoise(float x, float y){
	return _noise.noise(x, y);
}

float getNoise(float x, float y, float z){
	return _noise.noise(x, y, z);
}


