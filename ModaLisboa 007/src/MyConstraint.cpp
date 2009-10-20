

#include "MyConstraint.h"

MyConstraint::MyConstraint(MyParticle* _a, MyParticle* _b, float _strength, float _rest){
	enable();
	setA(_a);
	setB(_b);
	setStrength(_strength);
	if(_rest > 0.0f){
		setRest(_rest);
	} else {
		setRest(a->getDistance(*b));
	}
}

MyConstraint::~MyConstraint(){
	
}

void MyConstraint::update(float timeStep){
	if(isDisabled())return;
	MyParticle& aRef = *a;
	MyParticle& bRef = *b;
	if(aRef.isDisabled() and bRef.isDisabled())return;
	delta = bRef - aRef;
	float dist = delta.x*delta.x + delta.y*delta.y;
	if(dist < 1) dist = 1;
	else dist = sqrtf(dist);
	float moveAmount;
	if(aRef.isEnabled() and bRef.isEnabled()){
		moveAmount = strength * (dist - rest)/(dist*(aRef.getInvMass() + bRef.getInvMass()));
		aRef.x += delta.x * moveAmount * aRef.getInvMass();
		aRef.y += delta.y * moveAmount * aRef.getInvMass();
		bRef.x -= delta.x * moveAmount * bRef.getInvMass();
		bRef.y -= delta.y * moveAmount * bRef.getInvMass();
	} else {
		moveAmount = strength * (dist - rest) / dist;
		if(aRef.isEnabled()){
			aRef.x += delta.x * moveAmount;
			aRef.y += delta.y * moveAmount;
		} else {
			bRef.x -= delta.x * moveAmount;
			bRef.y -= delta.y * moveAmount;
		}
	}
}

void MyConstraint::debugDraw(){
	glBegin(GL_LINES);
	glVertex3f(a->x, a->y, a->z);
	glVertex3f(b->x, b->y, b->z);
	glEnd();
}

void MyConstraint::setA(MyParticle* _a){
	a = _a;
}

void MyConstraint::setB(MyParticle* _b){
	b = _b;
}

MyParticle* MyConstraint::getA(){
	return a;
}

MyParticle* MyConstraint::getB(){
	return b;
}

void MyConstraint::setRest(float _rest){
	rest = _rest;
	invRest = 1.0f / rest;
}

float MyConstraint::getRest(){
	return rest;
}

float MyConstraint::getInvRest(){
	return invRest;
}

void MyConstraint::setStrength(float _strength){
	strength = _strength;
	invStrength = 1.0f / strength;
}

float MyConstraint::getStrength(){
	return strength;	
}

float MyConstraint::getInvStrength(){
	return invStrength;
}

bool MyConstraint::hasParticle(MyParticle* p){
	return a == p or b == p;
}

void MyConstraint::enable(){
	bEnabled = true;
}

void MyConstraint::disable(){
	bEnabled = false;	
}

bool MyConstraint::isEnabled(){
	return bEnabled;	
}

bool MyConstraint::isDisabled(){
	return !bEnabled;	
}

