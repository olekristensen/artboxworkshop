#include "SceneSoundSphere.h"

SceneSoundSphere::SceneSoundSphere(){
	center.x = ofGetWidth() * 0.5f;
	center.y = ofGetHeight() * 0.5;
	center.z = 0.0f;
	for(int i=0; i<3; i++){
		spheres.push_back(new SoundSphere(ofRandom(100, 150)));
	}
}

SceneSoundSphere::~SceneSoundSphere(){
	for(int i=0; i<spheres.size(); i++){
		delete spheres[i];	
	}
	spheres.clear();
}

void SceneSoundSphere::update(MyFFT& fft){
	for(int i=0; i<spheres.size(); i++){
		spheres[i]->update(fft);
	}
}

void SceneSoundSphere::draw(){
	glPushMatrix();
	glTranslatef(center.x, center.y, center.z);
	glColor3f(0.0f, 0.0f, 0.0f);
	//glRotatef(ofGetFrameNum()*0.5, 1.0f, 1.0f, 0.0f);
	for(int i=0; i<spheres.size(); i++){
		//spheres[i]->drawPoints();
		//spheres[i]->drawQuads();
		spheres[i]->drawLines();
	}
	glPopMatrix();
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 20, 20);
}

void SceneSoundSphere::openScene(){
	ofBackground(97.0f, 0.0f, 24.0f);
}

void SceneSoundSphere::closeScene(){
	ofBackground(255, 255, 255);
}

