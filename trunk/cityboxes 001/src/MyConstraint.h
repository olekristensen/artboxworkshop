#pragma once

#include "MyParticle.h"

class MyConstraint{
protected:
	MyParticle*a, *b;
	float strength, invStrength;
	float rest, invRest;
	bool bEnabled;
	ofPoint delta;
public:
	MyConstraint(MyParticle* _a, MyParticle* _b, float _strength = 1.0f, float _rest = -1);
	virtual ~MyConstraint();
	virtual void update(float timeStep = 1.0f);
	virtual void draw(){debugDraw();}
	virtual void debugDraw();
	virtual void setA(MyParticle* _a);
	virtual void setB(MyParticle* _b);
	virtual MyParticle* getA();
	virtual MyParticle* getB();
	virtual void setRest(float _rest);
	virtual float getRest();
	virtual float getInvRest();
	virtual void setStrength(float _strength);
	virtual float getStrength();
	virtual float getInvStrength();
	virtual bool hasParticle(MyParticle* p);
	virtual void enable();
	virtual void disable();
	virtual bool isEnabled();
	virtual bool isDisabled();
};

