#pragma once

#include "SceneLinhasCurvas.h"
#include "SceneSoundSphere.h"
#include "SceneSmoke.h"

class SceneManager{
protected:
	vector<SceneBase*>scenes;
	int activeSceneIndex;
	MyFFT* fft;
public:
	SceneManager(MyFFT* _fft);
	~SceneManager();
	
	void update();
	void draw();
	bool goToScene(int sceneIndex);
	bool goToNextScene();
	bool goToPrevScene();
	void goToRandomScene();
	int getActiveSceneIndex();
	SceneBase* getActiveScene();
	void addScene(SceneBase* s);
	vector<SceneBase*>& getScenes();
};