#include "SceneManager.h"

SceneManager::SceneManager(MyFFT* _fft){
	fft = _fft;
	//addScene(new SceneLinhasCurvas());
	//addScene(new SceneSoundSphere());
	addScene(new SceneSmoke());
	activeSceneIndex = -1;
	goToScene(0);
}

SceneManager::~SceneManager(){
	for(int i=0; i<scenes.size(); i++){
		delete scenes[i];
	}
	scenes.clear();
}

void SceneManager::update(){
	unsigned long currentTime = ofGetSystemTime();
	scenes[activeSceneIndex]->update(*fft);
}

void SceneManager::draw(){
	scenes[activeSceneIndex]->draw();
}

bool SceneManager::goToScene(int sceneIndex){
	if(scenes.size() == 0)return false;
	if(sceneIndex >= scenes.size()) return false;
	if(activeSceneIndex == sceneIndex) return false;
	if(activeSceneIndex >= 0)scenes[activeSceneIndex]->closeScene();
	activeSceneIndex = sceneIndex;
	scenes[activeSceneIndex]->openScene();
	return true;
}

bool SceneManager::goToNextScene(){
	return goToScene(activeSceneIndex+1);
}

bool SceneManager::goToPrevScene(){
	if(activeSceneIndex < 1)return false;
	return goToScene(activeSceneIndex-1);
}

int SceneManager::getActiveSceneIndex(){
	return activeSceneIndex;
}

SceneBase* SceneManager::getActiveScene(){
	return scenes[activeSceneIndex];
}

void SceneManager::addScene(SceneBase* s){
	scenes.push_back(s);
}

vector<SceneBase*>& SceneManager::getScenes(){
	return scenes;
}

