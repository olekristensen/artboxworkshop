#pragma once

#include "coordWarp.h"
#include "ofxXmlSettings.h"
#include "Warp.h"

class ProjectionSurfacesObject {
public:
	float aspect;
	Warp * warp;
	coordWarping * coordWarp;
	string name;
	
	ofxPoint2f * corners[4];
	
	ProjectionSurfacesObject();
	
	void recalculate();
	void SetCorner(int n, float x, float y);
};



class ProjectionSurfaces {
public:
	void setup();
	
	vector<ProjectionSurfacesObject*> surfaces;
	ProjectionSurfacesObject * getSurface(int surface);
	void applyProjection(int surface, float w=ofGetWidth(), float h=ofGetHeight());
	ofxVec2f  convertToCoordinate(int surface,  ofxVec2f v);
	ofxVec2f  convertBetweenSurfaces(int obj1, int obj2,  ofxVec2f v);
	
	ofxVec2f lastMousePos;
	int selectedCorner;
	int selectedKeystoner;

	void mousePressed(ofMouseEventArgs & args);
	void mouseDragged(ofMouseEventArgs & args);
	void keyPressed(ofKeyEventArgs & args);

	void saveXml();
	void loadXml();
	
	ofxXmlSettings * keystoneXml;


};