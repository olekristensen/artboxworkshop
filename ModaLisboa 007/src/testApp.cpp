#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
	ofDisableArbTex();
	fft = new MyFFT();
	fft->setup(this, 1024);
	sceneManager = new SceneManager(fft);
	fader.setFadeSeconds(5.0f);
	fader.setAlpha(1.0f);
	fader.stopFade();

	projection.setup();
}

//--------------------------------------------------------------
void testApp::update(){
	sceneManager->update();
	unsigned long currentTime = ofGetSystemTime();
	fader.updateFade(currentTime);
}

//--------------------------------------------------------------
void testApp::draw(){
	projection.applyProjection(0);
	glDisable(GL_DEPTH_TEST);
	float invScaleX = 1.0f / ofGetWidth();
	float invScaleY = 1.0f / ofGetHeight();
	glPushMatrix();
	glScalef(invScaleX, invScaleY, invScaleX);
	sceneManager->draw();
	glPopMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	//ofSetColor(255, 255, 255);
	//ofRect(0,0,1,1);
	glPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	switch(key){
		case OF_KEY_UP:
			sceneManager->goToPrevScene();
			break;
		case OF_KEY_DOWN:
			sceneManager->goToNextScene();
			break;
		case '1':
			sceneManager->goToScene(0);
			break;
		case '2':
			sceneManager->goToScene(1);
			break;
		case '3':
			sceneManager->goToScene(2);
			break;
		case 'f':
			ofToggleFullscreen();
			break;
		case'o':
			fader.fadeIn();
			break;
		case 'i':
			fader.fadeOut();
			break;
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

void testApp::audioReceived(float * input, int bufferSize, int nChannels){
	fft->update(input, bufferSize);
}

