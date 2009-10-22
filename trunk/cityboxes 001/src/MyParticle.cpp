

#include "MyParticle.h"

MyParticle::MyParticle(float _x, float _y, float _z, float _radius, float _drag):
ofPoint(_x, _y, _z)
{
	enable();
	oldPos.x = x;
	oldPos.y = y;
	setRadius(_radius);
	setDrag(_drag);
	setMass(_radius * 0.1f);
}

MyParticle::MyParticle(MyParticle* p){
	MyParticle& _p = *p;
	enable();
	setRadius(_p.getRadius());
	setDrag(_p.getDrag());
	setMass(_p.getMass());
	setPos(_p);
}

MyParticle::~MyParticle(){
	
}

void MyParticle::update(float timeDelta){
	if(isDisabled())return;
	float tempX = x, tempY = y;
	forces *= invMass;
	x += (x - oldPos.x)*drag + forces.x * timeDelta*timeDelta;
	y += (y - oldPos.y)*drag + forces.y * timeDelta*timeDelta;
	forces.set(0,0);
	oldPos.x = tempX;
	oldPos.y = tempY;
	
}

void MyParticle::debugDraw(){
	if(isEnabled()) glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	else glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glPushMatrix();
	glTranslatef(x, y, z);
	ofCircle(0, 0, radius);
	glPopMatrix();
}

void MyParticle::applyForce(const ofPoint& force){
	forces += force;
}

void MyParticle::applyRepulsionForce(const ofPoint& repulsionCenter, float amount){
	ofPoint _force = *this - repulsionCenter;
	float dist = MAX(getDistance(repulsionCenter), 1.0f);
	_force.x = (_force.x * amount) / (dist*dist*dist);
	_force.y = (_force.y * amount) / (dist*dist*dist);
	applyForce(_force);
}

void MyParticle::applyAttractionForce(const ofPoint& attractionCenter, float amount){
	ofPoint _force = attractionCenter - *this;
	float dist = MAX(getDistance(attractionCenter), 1.0f);
	_force.x = (_force.x * amount) / (dist*dist*dist);
	_force.y = (_force.y * amount) / (dist*dist*dist);
	applyForce(_force);
}

void MyParticle::applyImpulse(const ofPoint& impulse){
	x += impulse.x;
	y += impulse.y;
}

void MyParticle::enable(){
	bIsEnabled = true;
}

void MyParticle::disable(){
	bIsEnabled = false;
}

bool MyParticle::isEnabled(){
	return bIsEnabled;
}

bool MyParticle::isDisabled(){
	return !bIsEnabled;
}

void MyParticle::moveTo(const ofPoint& target){
	ofPoint diff = target - *this;
	moveBy(diff);
}

void MyParticle::moveBy(const ofPoint& amount){
	*this += amount;
	oldPos += amount;
}

ofPoint MyParticle::getVel(){
	return ofPoint(x - oldPos.x, y - oldPos.y);
}

ofPoint& MyParticle::getForces(){
	return forces;
}

void MyParticle::setPos(const ofPoint& pos){
	x = pos.x;
	y = pos.y;
	z = pos.z;
}

void MyParticle::setMass(float _mass){
	mass = _mass;
	invMass = 1.0f / mass;
}

void MyParticle::setDrag(float _drag){
	drag = _drag;
}

float MyParticle::getMass(){
	return mass;
}

float MyParticle::getInvMass(){
	return invMass;
}

float MyParticle::getDrag(){
	return drag;
}

void MyParticle::setRadius(float _radius){
	radius = _radius;
}

float MyParticle::getRadius(){
	return radius;
}

float MyParticle::getDistance(const ofPoint& target){
	return sqrtf(getDistanceSquared(target));
}

float MyParticle::getDistanceSquared(const ofPoint& target){
	float dx = target.x - x;
	float dy = target.y - y;
	return dx*dx+dy*dy;
}

bool MyParticle::isPointInside(const ofPoint& point){
	return getDistanceSquared(point) < radius*radius;
}

void MyParticle::stopMotion(){
	oldPos = *this;
	forces.set(0,0,0);
}

















