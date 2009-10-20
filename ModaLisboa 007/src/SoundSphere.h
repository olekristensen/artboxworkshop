#pragma once

#include "MyPhysics3d.h"
#include "MyFFT.h"

class SoundSphere{
protected:
	vector< vector<MyParticle*> > points;
	vector< vector<ofPoint> > pointNormals;
	vector< vector<int> > bands;
	ofPoint center;
	int numBands;
	int sphereRes;
	float radius;
	MyPhysics3d*physics;
public:
	
	SoundSphere(float _radius = 100.0f, int _sphereRes = 50.0f);
	~SoundSphere();
	
	void update(MyFFT& fft);
	void drawPoints();
	void drawQuads();
	void drawLines();
	void setSphereResolution(int _res);
	
};