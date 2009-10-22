#pragma once

#include "MyPhysics3d.h"
#include "ofxNoise.h"
#include "ofMain.h"
#include "CollisionSolver.h"

class ParticleManager{
protected:
	ofxPerlin *noise;
	MyPhysics3d *physics;
	ofPoint wind;
	float counter;
	vector<ProjectionSurfacesObject*>surfaces;
public:
	ParticleManager(){
		physics = new MyPhysics3d();
		noise = new ofxPerlin();
		wind.set(0.0f, 0.2f);
	}
	
	void addSurfaceToColision(ProjectionSurfacesObject* surface){
		surfaces.push_back(surface);
	}
	
	ofPoint particleDisplacement;
	void update(){
		physics->update();
		float maxW = ofGetWidth();
		float maxH = ofGetHeight();
		float maxZ = 500.0f;
		int numParticles = (int)ofRandom(0, 10);
		ofPoint pos, force;
		for(int i=0; i<numParticles; i++){
			//pos.x = 0;
			//pos.y = ofRandom(0, maxH);
			pos.x = ofRandom(0, maxW);
			pos.y = 0.0f;
			force.x = ofRandom(0, 1);
			force.y = 0;
			createParticle(pos, force);
		}
		counter += 0.5f;
		float noiseRes = 0.001f;
		ofPoint noiseMul(0.1, 0.1, 0.1);
		float randomStep = 0.05f;
		float angleXZ, angleY;
		ofxPerlin& noiseRef = *noise;
		vector<MyParticle*>& particles = physics->getParticles();
		for(int i=0; i<particles.size(); i++){
			MyParticle& p = *particles[i];
			if(p.x < 0 or p.x > maxW or p.y < 0 or p.y > maxH or p.z < -maxZ or p.z > maxZ){
				physics->deleteParticle(i);
				continue;
			}
			angleXZ = noiseRef.noise(p.x * noiseRes, p.z * noiseRes, counter*noiseRes) * TWO_PI;
			angleY = noiseRef.noise(p.x * noiseRes, p.y * noiseRes, counter*noiseRes) * TWO_PI;
			force.x = cos(angleXZ) * noiseMul.x + ofRandom(-randomStep, randomStep);
			force.y = -sin(angleY) * noiseMul.y + ofRandom(-randomStep, randomStep);
			force.z = sin(angleXZ) * noiseMul.z + ofRandom(-randomStep, randomStep);
			p.applyForce(force);
			p.applyForce(wind);
			//printf("p.x:%f, p.y:%f, p.z:%f\n", p.x, p.y, p.z);
		}
		
		int numSurfaces = surfaces.size();
		numParticles = particles.size();
		for(int i=0; i<numSurfaces; i++){
			ProjectionSurfacesObject& s = *surfaces[i];
			for(int j=0; j<numParticles; j++){
				MyParticle& p = *particles[j];
				CollisionInfo ci = CollisionSolver::getCollisionInfo(surfaces[i], particles[j]);
				if(ci.bCollide){
					particleDisplacement = ci.normal * -ci.penetration;
					p += (particleDisplacement);
					//p.applyForce(particleDisplacement * 0.2f);
				}
			}
		}
	}
	
	void draw(){
		glPointSize(3);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBegin(GL_POINTS);
		vector<MyParticle*>& particles = physics->getParticles();
		ofPoint vel;
		for(int i=0; i<particles.size(); i++){
			MyParticle& p = *particles[i];
			glVertex2f(p.x, p.y);
			//vel = p.getVel();
			//glVertex2f(p.x - vel.x, p.y- vel.y);
		}
		glEnd();
	}
	
	MyParticle* createParticle(const ofPoint& pos, const ofPoint& impulse){
		MyParticle* newP = new MyParticle(pos.x, pos.y, pos.z, 1);
		newP->applyImpulse(impulse);
		physics->addParticle(newP);
		return newP;
	}
};