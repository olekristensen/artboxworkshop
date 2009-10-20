#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofAddListener(tuio.objectAdded,this,&testApp::objectAdded);
	ofAddListener(tuio.objectRemoved,this,&testApp::objectRemoved);
	ofAddListener(tuio.objectUpdated,this,&testApp::objectUpdated);
	ofAddListener(tuio.cursorAdded,this,&testApp::tuioAdded);
	ofAddListener(tuio.cursorRemoved,this,&testApp::tuioRemoved);
	ofAddListener(tuio.cursorUpdated,this,&testApp::tuioUpdated);

	ofSetFrameRate(60);
	ofBackground(0,0,0);
	tuio.start(3333);
	ofEnableAlphaBlending();
	noise = new ofxPerlin();
}

//--------------------------------------------------------------
void testApp::update(){
	tuio.getMessage();
	list<ofxTuioCursor*> fingers = tuio.getTuioCursors();
	list<ofxTuioCursor*>::iterator it;
	ofPoint target;
	for(int i=0; i<ribbons.size(); i++){
		for(it = fingers.begin(); it != fingers.end(); it++){
			ofxTuioCursor& cur = (*(*it));
			if(ribbons[i]->getSessionId() == cur.getSessionId()){
				target.x = cur.getX() * ofGetWidth();
				target.y = cur.getY() * ofGetHeight();
				ribbons[i]->goTo(target);
			}
		}
		ribbons[i]->update();
	}
}


//--------------------------------------------------------------
void testApp::draw(){
	for(int i=0; i<ribbons.size(); i++){
		ribbons[i]->draw();									
	}
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

}

void testApp::keyReleased(int key){
	switch(key){
		case 'f':
			ofToggleFullscreen();
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
void testApp::mouseReleased(){
}


void testApp::objectAdded(ofxTuioObject & tuioObject){
	cout << " new object: " + ofToString(tuioObject.getFiducialId())+
		" X: "+ofToString(tuioObject.getX())+
		" Y: "+ofToString(tuioObject.getY())+
		" angle: "+ofToString(tuioObject.getAngleDegrees())
	<< endl;
}
void testApp::objectRemoved(ofxTuioObject & tuioObject){
	cout << " object removed: " + ofToString(tuioObject.getFiducialId())+
		" X: "+ofToString(tuioObject.getX())+
		" Y: "+ofToString(tuioObject.getY())+
		" angle: "+ofToString(tuioObject.getAngleDegrees())
	<< endl;
}
void testApp::objectUpdated(ofxTuioObject & tuioObject){
	cout << " object updated: " + ofToString(tuioObject.getFiducialId())+
		" X: "+ofToString(tuioObject.getX())+
		" Y: "+ofToString(tuioObject.getY())+
		" angle: "+ofToString(tuioObject.getAngleDegrees())
	<< endl;
}

void testApp::tuioAdded(ofxTuioCursor & tuioCursor){
	cout << " new cursor: " + ofToString(tuioCursor.getFingerId())+
		" X: "+ofToString(tuioCursor.getX())+
		" Y: "+ofToString(tuioCursor.getY())
	<< endl;
	ofPoint pos(tuioCursor.getX() * ofGetWidth(), tuioCursor.getY() * ofGetHeight());
	Ribbon*r = new Ribbon(noise, pos, tuioCursor.getSessionId());
	ribbons.push_back(r);
}
void testApp::tuioRemoved(ofxTuioCursor & tuioCursor){
	cout << " cursor removed: " + ofToString(tuioCursor.getFingerId())+
		" X: "+ofToString(tuioCursor.getX())+
		" Y: "+ofToString(tuioCursor.getY())
	<< endl;
	for(int i=0; i<ribbons.size(); i++){
		if(ribbons[i]->getSessionId() == tuioCursor.getSessionId()){
			delete ribbons[i];
			ribbons.erase(ribbons.begin() + i);
		}	
	}
}
void testApp::tuioUpdated(ofxTuioCursor & tuioCursor){
	cout << " cursor updated: " + ofToString(tuioCursor.getFingerId())+
		" X: "+ofToString(tuioCursor.getX())+
		" Y: "+ofToString(tuioCursor.getY())
	<< endl;
}
