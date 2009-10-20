#pragma once

#include "SceneBase.h"
#include "SoundSphere.h"

#define NUM_ROW_POINTS 50
#define NUM_LINE_POINTS 50
#define SPHERE_RADIUS 50

class SceneSoundSphere: public SceneBase{
protected:
	vector<SoundSphere*>spheres;
	ofPoint center;
public:
	SceneSoundSphere();
	~SceneSoundSphere();
	
	void update(MyFFT& fft);
	void draw();
	void openScene();
	void closeScene();
};