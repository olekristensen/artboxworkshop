#pragma once 

#include "ofMain.h"
#include "SceneBase.h" 
#include "ParticleEmmiter.h"
#include "SoundReactiveParticle.h"
#include "SoundReactiveCam.h"
#include "Utils.h"
#include "ofx3DUtils.h"
#include "ofxShader.h"

#define USE_LIVE_INPUT

#define MAX_PARTICLES 10000

#define SCENE_W 1024
#define SCENE_H 768

class SceneSmoke:public SceneBase{
protected:
	vector<ParticleEmmiter*> emmiters;
	SoundReactiveParticle** particlePool;
	vector<GLfloat>partPoints;
	vector<GLfloat>partSizes;
	//vector<GLfloat> partAlphas;
	vector<GLfloat> partColors;
	ofPoint sceneCenter, emiterCenter;
	ofPoint wind;
	float counter;
	ofImage smokeTexture;
	ofImage backgroundTexture;
	ofImage foregroundTexture;
	ofxShader shader;
	
	ofPoint nameRot;
	ofPoint nameRotTarget;
	ofPoint namePos, namePosTarget;
	
	bool bExplosionMode;
	
#ifndef USE_LIVE_INPUT
	ofSoundPlayer soundPlayer;
#endif
	
public:
	SceneSmoke();
	~SceneSmoke();
	void update(MyFFT& fft);
	void draw();
	ParticleEmmiter* createParticleEmmiter();
	bool deleteParticleEmmiter(unsigned int emmiterIndex);
	bool deleteParticleEmmiter(ParticleEmmiter* p);
	void drawParticle(MyParticle& p);
	void openScene();
	void closeScene();
	
	void createParticle(ParticleEmmiter& p, float minRadius, float maxRadius);
	void removeParticle(unsigned int partIndex);
	void removeParticle(MyParticle* p);
	
	void setExplosionMode(bool _bMode);
	void onKeyReleased(ofKeyEventArgs& e);
	void onKeyPressed(ofKeyEventArgs& e);
	
	SoundReactiveCam cam;
};
