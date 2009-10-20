#include "Ribbon.h"

Ribbon::Ribbon(ofxPerlin* _noise, const ofPoint& pos, long _sessionId, int _numNodes, int _width){
	noise = _noise;
	physics = new ofxPhysics2d();
	sessionId = _sessionId;
	width = _width;
	float currentWidth;
	numNodes = _numNodes;
	for(int i=0; i<numNodes; i++){
		ofxParticle* p = new ofxParticle(pos);
		p->setDrag(0.5);
		physics->add(p);
	}
	counter = 0.0f;
}

Ribbon::~Ribbon(){
	physics->deleteAll();
	delete physics;
}

void Ribbon::update(){
	if(numNodes < 2){
		ofLog(OF_LOG_WARNING, "Ribbon::update, not enought nodes to create ribbon");
		return;
	}
	physics->update();
	counter += 1.0f;
	vector<ofxParticle*>& particles = physics->getParticles();
	ofPoint force;
	ofPoint rndForce;
	float noiseMul = 1.0f;
	float noiseRes = 0.01f;
	float angle;
	for(int i=0; i<numNodes-1; i++){
		ofPoint& pt = *particles[i];
		force = (*particles[i+1] - pt)*0.2f;
		angle = noise->noise(pt.x * noiseRes, pt.y * noiseRes, counter*noiseRes) * TWO_PI;
		rndForce.x = cos(angle) * noiseMul;
		rndForce.y = -sin(angle) * noiseMul;
		force += rndForce;
		particles[i]->applyForce(force);
	}
}

void Ribbon::draw(){
	glBegin(GL_QUAD_STRIP);
	float nodeWidth;
	ofxVec2f diff;
	float n;
	ofPoint vertice1, vertice2;
	vector<ofxParticle*>& particles = physics->getParticles();
	for(int i=0; i<numNodes-1; i++){
		ofPoint& pt1 = *particles[i];
		ofPoint& pt2 = *particles[i+1];
		diff = pt1 - pt2;
		diff.perpendicular();
		n = (float)i / (numNodes-1);
		nodeWidth = width - (width * n);
		diff *= nodeWidth;
		glColor4f(1.0f, 1.0f, 1.0f, n);
		vertice1 = pt1 + diff;
		vertice2 = pt1 - diff;
		glVertex2f(vertice1.x, vertice1.y);
		glVertex2f(vertice2.x, vertice2.y);
	}
	ofPoint lastPt = *particles.back();
	glVertex2f(lastPt.x, lastPt.y);
	glVertex2f(lastPt.x, lastPt.y);
	glEnd();
}

void Ribbon::goTo(const ofPoint& pos){
	if(numNodes < 1){
		ofLog(OF_LOG_WARNING, "Ribbon::goTo - no nodes to move around...");
		return;
	}
	ofxParticle& p = *(physics->getParticles().back());
	ofPoint force = (pos - p)*0.1f;
	p.applyForce(force);
}

long Ribbon::getSessionId(){
	return sessionId;	
}
