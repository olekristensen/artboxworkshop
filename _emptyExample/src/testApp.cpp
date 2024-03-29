#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	surfaces.setup();
	surfaces.addSurface(new ProjectionSurfacesObject);
	surfaces.addSurface(new ProjectionSurfacesObject);
	surfaces.addSurface(new ProjectionSurfacesObject);
	cameraSurfaces.setup(&surfaces);
	
	grabber = new ofVideoGrabber;
	grabber->initGrabber(800,600);
}

//--------------------------------------------------------------
void testApp::update(){
	grabber->grabFrame();	
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0, 0, 0);
	ofEnableAlphaBlending();
	for(int i=0;i<surfaces.surfaces.size();i++){
		surfaces.applyProjection(i);
		ofSetColor(255, 100*i, 255, 100);
		ofRect(0, 0, 1, 1);
		ofSetColor(0, 100*i, 255);
		ofRect(0.2, 0.2, 0.6, 0.6);
		
		glPopMatrix();
	}
	
	for(int i=0;i<cameraSurfaces.surfaces.size();i++){
		cameraSurfaces.applyWarp(i);
		ofSetColor(255, 255, 255,255);
				grabber->draw(0,0,1,1);
		//ofSetColor(255, 100*i, 255, 100);
		//ofRect(0, 0, 1, 1);
		
		glPopMatrix();
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key=='c'){
		grabber->videoSettings();
	}
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

