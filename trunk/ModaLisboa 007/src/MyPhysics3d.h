#pragma once

#include "MyParticle.h"
#include "MyConstraint.h"

class MyPhysics3d{
protected:
	vector<MyParticle*> particles;
	vector<MyConstraint*> constraints;
	ofPoint gravity;
	bool bEnabled;
public:
	MyPhysics3d(ofPoint _gravity = ofPoint() );
	virtual ~MyPhysics3d();
	
	virtual void update(float _timeStep = 1.0f);
	virtual void draw(){debugDraw();}
	virtual void debugDraw();
	virtual void addParticle(MyParticle* p);
	virtual MyParticle* createParticle(float x = 0.0f, float y = 0.0f, float z = 0.0f, float radius = DEFAULT_RADIUS, float drag = DEFAULT_DRAG);
	virtual bool removeParticle(MyParticle* p);
	virtual bool removeParticle(unsigned int partIndex);
	virtual bool deleteParticle(MyParticle* p);
	virtual bool deleteParticle(unsigned int partIndex);
	virtual vector<MyParticle*>& getParticles();
	virtual MyParticle* getParticle(unsigned int partIndex);
	virtual int getNumParticles();
	virtual void addConstraint(MyConstraint* c);
	virtual MyConstraint* createConstraint(MyParticle*a, MyParticle*b, float strenght = 1.0f, float rest = -1);
	virtual bool removeConstraint(MyConstraint* c);
	virtual bool removeConstraint(unsigned int constraintIndex);
	virtual bool deleteConstraint(MyConstraint* c);
	virtual bool deleteConstraint(unsigned int constraintIndex);
	virtual vector<MyConstraint*>& getConstraints();
	virtual MyConstraint* getConstraint(unsigned int constraintIndex);
	virtual int getNumConstraints();
	virtual void setGravity(const ofPoint& _gravity);
	virtual ofPoint getGravity();
	virtual void enable();
	virtual void disable();
	virtual bool isEnabled();
	virtual bool isDisabled();
	virtual MyConstraint* getConstraintWithParticle(MyParticle* p);
};
