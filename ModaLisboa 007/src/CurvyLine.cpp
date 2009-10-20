#include "CurvyLine.h"

CurvyLine::CurvyLine(MyPhysics3d* _physics, float _ribbonWidth)
{
	physics = _physics;
	ribbonWidth = _ribbonWidth;
	points.resize(NUM_POINTS);
	colors.resize(NUM_POINTS);
	targetPoints.resize(NUM_POINTS);
	if(ofRandomuf() < 0.5){
		curveMode = LEFT_CURVE;
	} else curveMode = RIGHT_CURVE;
	screenHeight = ofGetHeight();
	screenWidth = ofGetWidth();
	width = ofRandom(200, 500);
	height = ofRandom(600, 800);
	if(curveMode == LEFT_CURVE){
		for(int i=0; i<targetPoints.size(); i++){
			float radiusIncrement = getNoise((float)i * 0.001f, counter*0.001f) * 100;
			float angle = (float)i/(targetPoints.size()-1) * PI;
			targetPoints[i].x = cos(angle) * (width + radiusIncrement) ;
			targetPoints[i].y = screenHeight - sinf(angle) * (height + radiusIncrement);
		}
	} else {
		for(int i=0; i<targetPoints.size(); i++){
			float radiusIncrement = getNoise((float)i * 0.001f, counter*0.001f) * 100;
			float angle = (float)i/(targetPoints.size()-1) * PI;
			targetPoints[i].x = screenWidth - cos(angle) * (width + radiusIncrement);
			targetPoints[i].y = screenHeight - sin(angle) * (height + radiusIncrement);
		}
	}
	for(int i=0; i<points.size(); i++){
		points[i] = new MyParticle(targetPoints[i].x, targetPoints[i].y, 0.0f, 1.0f);
		points[i]->setMass(1.0f);
		physics->addParticle(points[i]);
	}
	for(int i=0; i<colors.size(); i++){
		colors[i].r = colors[i].g = colors[i].b = colors[i].a = 0.5f;
	}
	counter = ofRandom(0, 100.0f);
}

void CurvyLine::update(MyFFT& fft){
	physics->update();
	counter += 1;
	float angle;
	if(curveMode == LEFT_CURVE){
		for(int i=0; i<targetPoints.size(); i++){
			float radiusIncrement = getNoise((float)i * 0.01f, counter*0.01f) * 100;
			angle = (float)i/(targetPoints.size()-1) * PI;
			targetPoints[i].x = cos(angle) * (width + radiusIncrement) ;
			targetPoints[i].y = screenHeight - sinf(angle) * (height + radiusIncrement);
		}
	} else {
		for(int i=0; i<targetPoints.size(); i++){
			float radiusIncrement = getNoise((float)i * 0.01f, counter*0.01f) * 100;
			angle = (float)i/(targetPoints.size()-1) * PI;
			targetPoints[i].x = screenWidth - cos(angle) * (width + radiusIncrement);
			targetPoints[i].y = screenHeight - sin(angle) * (height + radiusIncrement);
		}
	}
	ofPoint force;
	for(int i=0; i<points.size(); i++){
		force.x = (targetPoints[i].x - points[i]->x)*0.1f;
		force.y = (targetPoints[i].y - points[i]->y)*0.1f;
		points[i]->applyForce(force);
	}
}

void CurvyLine::draw(){
	glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
	glBegin(GL_QUAD_STRIP);
	ofxVec2f diff;
	for(int i=0; i<points.size()-1; i++){
		MyParticle& p1 = *points[i];
		MyParticle& p2 = *points[i+1];
		diff.set(p2.x - p1.x, p2.y - p1.y);
		diff.perpendicular();
		diff *= ribbonWidth;
		glColor4f(colors[i].r, colors[i].g, colors[i].b, colors[i].a);
		glVertex3f(p1.x + diff.x, p1.y + diff.y, p1.z);
		glVertex3f(p1.x - diff.x, p1.y - diff.y, p1.z);
	}
	glEnd();

}

