

#include "SceneLinhasCurvas.h"

SceneLinhasCurvas::SceneLinhasCurvas()
{
	for(int i=0; i<NUM_LINES; i++){
		float ribbonWidth = ofRandom(20, 60);
		lines.push_back(new CurvyLine(physics, ribbonWidth));
	}
}

SceneLinhasCurvas::~SceneLinhasCurvas(){
	
}

void SceneLinhasCurvas::update(MyFFT& fft){
	for(int i=0; i<lines.size(); i++){
		lines[i]->update(fft);
	}
}

void SceneLinhasCurvas::draw(){
	for(int i=0; i<lines.size(); i++){
		lines[i]->draw();
	}
}

