#pragma once

#include "Utils.h"
#include "ofMain.h"
#include "MyPhysics3d.h"
#include "MyFFT.h"
#include "ofxVec2f.h"


#define NUM_POINTS 100

#define LEFT_CURVE "leftcurve"
#define RIGHT_CURVE "rightcurve"

class CurvyLine{
protected:
	float screenWidth, screenHeight;
	float width, height;
	MyPhysics3d* physics;
	vector<MyParticle*>points;
	vector<ofPoint>targetPoints;
	vector<ofColor>colors;
	float counter;
	string curveMode;
	float ribbonWidth;
public:
	CurvyLine(MyPhysics3d* _physics, float _ribbonWidth);
	~CurvyLine();
	
	void update(MyFFT& fft);
	void draw();
};


