
#pragma once

#include "ofMain.h"
#include "ofxPhysics2d.h"
#include "ofxNoise.h"

class Ribbon{
protected:
	ofxPhysics2d* physics;
	float width;
	int numNodes;
	long sessionId;
	ofxPerlin* noise;
	float counter;
public:
	Ribbon(ofxPerlin* _noise, const ofPoint& pos, long _sessionID, int _numNodes = 10, int _width = 30);
	~Ribbon();
	virtual void update();
	virtual void draw();
	virtual void goTo(const ofPoint& pos);
	long getSessionId();
};

