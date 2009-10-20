#pragma once

#include "CurvyLine.h"
#include "SceneBase.h"
#include "MyPhysics3d.h"

#define NUM_LINES 10

class SceneLinhasCurvas: public SceneBase{
protected:
	MyFFT* fft;
	vector<CurvyLine*> lines;
public:
	SceneLinhasCurvas();
	~SceneLinhasCurvas();
	
	void update(MyFFT& fft);
	void draw();
};
