
#include "MyPhysics3d.h"

MyPhysics3d::MyPhysics3d(ofPoint _gravity){
	enable();
	gravity = _gravity;
}

MyPhysics3d::~MyPhysics3d(){
	for(int i=0; i<particles.size(); i++){
		delete particles[i];
	}
	particles.clear();
	for(int i=0; i<constraints.size(); i++){
		delete constraints[i];
	}
	constraints.clear();
}

void MyPhysics3d::update(float timeStep){
	if(isDisabled())return;
	for(int i=0; i<particles.size(); i++){
		MyParticle &p = *particles[i];
		p.applyImpulse(gravity);
		p.update(timeStep);
		
	}
	for(int i=0; i<constraints.size(); i++){
		constraints[i]->update(timeStep);
	}
}

void MyPhysics3d::debugDraw(){
	for(int i=0; i<particles.size(); i++){
		MyParticle& p = *particles[i];
		glPushMatrix();
		glTranslatef(p.x, p.y, p.z);
		ofCircle(0.0f, 0.0f, p.getRadius());
		glPopMatrix();
	}
}

void MyPhysics3d::addParticle(MyParticle* p){
	particles.push_back(p);
}

MyParticle* MyPhysics3d::createParticle(float x, float y, float z, float radius, float drag){
	MyParticle *p = new MyParticle(x, y, z, radius, drag);
	addParticle(p);
	return p;
}

bool MyPhysics3d::removeParticle(MyParticle* p){
	for(int i=0; i<particles.size(); i++){
		if(particles[i] == p){
			particles.erase(particles.begin() + i);
			return true;
		}
	}
	return false;
}

bool MyPhysics3d::removeParticle(unsigned int partIndex){
	if(partIndex >= particles.size()) return false;
	particles.erase(particles.begin() + partIndex);
	return true;
}

bool MyPhysics3d::deleteParticle(MyParticle* p){
	if(removeParticle(p)){
		for(int i=0; i<constraints.size(); i++){
			if(constraints[i]->hasParticle(p)){
				delete constraints[i];
				constraints.erase(constraints.begin() + i);
				ofLog(OF_LOG_WARNING, "MyPhysics3d::deleteParticle - also deleting constraint:"+ofToString(i,0)
					  + " because it uses the particle being deleted");
			}
		}
		delete p;
		return true;
	}
	return false;
}

bool MyPhysics3d::deleteParticle(unsigned int partIndex){
	if(partIndex >= particles.size()) return false;
	for(int i=0; i<constraints.size(); i++){
		if(constraints[i]->hasParticle(particles[partIndex])){
			delete constraints[i];
			constraints.erase(constraints.begin() + i);
			ofLog(OF_LOG_WARNING, "MyPhysics3d::deleteParticle - also deleting constraint:"+ofToString(i,0)
				  + " because it uses the particle being deleted");
		}
	}
	delete particles[partIndex];
	particles.erase(particles.begin() + partIndex);
	return true;
}

vector<MyParticle*>& MyPhysics3d::getParticles(){
	return particles;
}

MyParticle* MyPhysics3d::getParticle(unsigned int partIndex){
	if(partIndex >= particles.size()){
		ofLog(OF_LOG_WARNING, "MyPhysics3d::getParticle - index out of bounds, returning NULL");
		return NULL;
	}
	return particles[partIndex];
}

int MyPhysics3d::getNumParticles(){
	return particles.size();
}

void MyPhysics3d::addConstraint(MyConstraint* c){
	constraints.push_back(c);
}

MyConstraint* MyPhysics3d::createConstraint(MyParticle* a, MyParticle* b, float strength, float rest){
	MyConstraint *c  = new MyConstraint(a, b, strength, rest);
	addConstraint(c);
	return c;
}

bool MyPhysics3d::removeConstraint(MyConstraint* c){
	for(int i=0; i<constraints.size(); i++){
		if(constraints[i] == c){
			constraints.erase(constraints.begin() + i);
			return true;
		}
	}
	return false;
}

bool MyPhysics3d::removeConstraint(unsigned int constraintIndex){
	if(constraintIndex >= constraints.size())return false;
	constraints.erase(constraints.begin() + constraintIndex);
	return true;
}

bool MyPhysics3d::deleteConstraint(MyConstraint* c){
	if(removeConstraint(c)){
		delete c;
		return true;
	}
	return false;
}

bool MyPhysics3d::deleteConstraint(unsigned constraintIndex){
	if(constraintIndex >= constraints.size()) return false;
	delete constraints[constraintIndex];
	return true;
}

vector<MyConstraint*>& MyPhysics3d::getConstraints(){
	return constraints;
}

MyConstraint* MyPhysics3d::getConstraint(unsigned int constraintIndex){
	if(constraintIndex >= constraints.size()){
		ofLog(OF_LOG_WARNING, "MyPhysics3d::getConstraint - index out of bounds, returning NULL");
		return NULL;
	}
	return constraints[constraintIndex];
}
										   
int MyPhysics3d::getNumConstraints(){
	return constraints.size();	
}

void MyPhysics3d::setGravity(const ofPoint& _gravity){
	gravity = _gravity;
}

ofPoint MyPhysics3d::getGravity(){
	return gravity;
}

void MyPhysics3d::enable(){
	bEnabled = true;
}

void MyPhysics3d::disable(){
	bEnabled = false;
}

bool MyPhysics3d::isEnabled(){
	return bEnabled;
}

bool MyPhysics3d::isDisabled(){
	return !bEnabled;	
}

MyConstraint* MyPhysics3d::getConstraintWithParticle(MyParticle* p){
	for(int i=0; i<constraints.size(); i++){
		if(constraints[i]->hasParticle(p))return constraints[i];
	}
	return NULL;
}






