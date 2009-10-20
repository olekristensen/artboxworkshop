#pragma once

#include "ofxCamera.h"
#include "ofxVectorMath.h"

class SoundReactiveCam: public ofxCamera, MyParticle{
protected:
	ofPoint target;
public:
	SoundReactiveCam(){
		target = getPosition();
	}
	~SoundReactiveCam(){
		
	}

	void updateSoundReactive(MyFFT& fft){
		MyParticle::update();
		float fftVal = fft.getAveragePower() * 300;
		float randomStep = 1 + (fftVal);
		ofPoint randPt(ofRandom(-randomStep, randomStep), ofRandom(-randomStep, randomStep), ofRandom(-randomStep, randomStep));
		ofPoint& thisRef = *this;
		thisRef += (target + randPt - thisRef) * 0.1f;
		position(x, y, z);
		eye(x, y, z - 1);
	}
	
};

