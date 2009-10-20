#pragma once

#include "ofMain.h"

#define DEFAULT_DRAG 0.6f
#define DEFAULT_RADIUS 10.0f

class MyParticle: public ofPoint{
protected:
	ofPoint oldPos, forces;
	float radius, drag, mass, invMass;
	bool bIsEnabled;
public:
	MyParticle(float _x = 0, float _y = 0, float _z = 0, float radius = DEFAULT_RADIUS, float _drag = DEFAULT_DRAG);
	MyParticle(MyParticle* p);
	virtual ~MyParticle();
	
	virtual void update(float timeDelta = 1.0f);
	virtual void draw(){debugDraw();}
	virtual void debugDraw();
	virtual void applyForce(const ofPoint& force);
	virtual void applyRepulsionForce(const ofPoint& repulsionCenter, float amount);
	virtual void applyAttractionForce(const ofPoint& attractionCenter, float amount);
	virtual void applyImpulse(const ofPoint& impulse);
	virtual void enable();
	virtual void disable();
	virtual bool isEnabled();
	virtual bool isDisabled();
	virtual void moveTo(const ofPoint& target);
	virtual void moveBy(const ofPoint& amount);
	virtual ofPoint getVel();
	virtual ofPoint& getForces();
	virtual void setPos(const ofPoint& pos);
	virtual void setMass(float _mass);
	virtual void setDrag(float _drag);
	virtual float getMass();
	virtual float getInvMass();
	virtual float getDrag();
	virtual void setRadius(float _radius);
	virtual float getRadius();
	virtual float getDistance(const ofPoint& target);
	virtual float getDistanceSquared(const ofPoint& target);
	virtual bool isPointInside(const ofPoint& point);
	virtual void stopMotion();
};
