#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0,0,0);
	ofSetVerticalSync(true);
	ofSetFullscreen(true);
	boxManager.setup();
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for(int i=0; i<7; i++){
		Box1* b = new Box1();
		boxManager.addBoxSurface(b);
		particleManager.addSurfaceToColision(b);
	}
	
	bgVideo.loadMovie("video/background.mov");
	//bgVideo.setLoop(OF_LOOP_NORMAL);
	bgVideo.play();
}

//--------------------------------------------------------------
void testApp::update(){
	boxManager.update();
	particleManager.update();
	bgVideo.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	//115 y
	bgVideo.draw(0,115, ofGetWidth(), ofGetHeight());
	boxManager.draw();
	particleManager.draw();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	ofRect(0, 0, ofGetWidth(), 115);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	if(key == 'f')ofToggleFullscreen();
	if(key == 'c')boxManager.toggleCalibration();
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

