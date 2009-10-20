#include "ParticleEmmiter.h"
#include "MyPhysics3d.h"

ParticleEmmiter::ParticleEmmiter(MyPhysics3d* _pm, float _x, float _y, float _z, float _radius, float _drag):
MyParticle(_x, _y, _z, _radius, _drag)
{
	particleManager = _pm;
}

MyParticle* ParticleEmmiter::createParticle(){
	float radius = ofRandom(10, 50);
	MyParticle*p = particleManager->createParticle(x, y, z, radius);
	ofPoint impulse = getVel()*10;
	impulse.x += ofRandom(-10, 10);
	impulse.y += ofRandom(-10, 10);
	p->applyImpulse(impulse);
	return p;
}


