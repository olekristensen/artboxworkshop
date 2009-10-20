#pragma once

#include "MyParticle.h"

class MyPhysics3d;

class ParticleEmmiter: public MyParticle{
protected:
	MyPhysics3d* particleManager;
public:
	ParticleEmmiter(MyPhysics3d* _particleManager, float _x = 0, float _y = 0, float _z = 0, float radius = DEFAULT_RADIUS, float _drag = DEFAULT_DRAG);

MyParticle* createParticle();
};
