#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	surfaces.setup();
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	/*ofBackground(0, 0, 0);
	for(int i=0;i<surfaces.surfaces.size();i++){
		surfaces.applyProjection(i);
		ofSetColor(255, 100*i, 255);
		ofRect(0, 0, 1, 1);
		ofSetColor(0, 100*i, 255);
		ofRect(0.2, 0.2, 0.6, 0.6);

		glPopMatrix();
	}*/
	
	surfaces.applyProjection(EYELINER);
	ofRect(0, 0, 1, 1);
	ofSetColor(0, 100, 255);
	
	glPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

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

