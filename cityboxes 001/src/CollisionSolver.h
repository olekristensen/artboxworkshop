#pragma once

#include "ofMain.h"
#include "MyParticle.h"
#include "projectionSurfaces.h"

typedef struct {
	ProjectionSurfacesObject* surface;
	MyParticle* particle;
	ofPoint normal;
	float penetration;
	bool bCollide;
} CollisionInfo;

class CollisionSolver{
public:
	static inline CollisionInfo getCollisionInfo(ProjectionSurfacesObject* surface, MyParticle* particle){
		ofPoint edgeVec;
		ofxVec2f axis;
		float minInterval = 9999999;
		
		CollisionInfo ci;
		ci.surface = surface;
		ci.particle = particle;
		ci.bCollide = true;
		
		ofPoint *surfaceVertices = surface->worldPts;
		ofPoint particleVertices[2];
		particleVertices[0] = *particle;
		particleVertices[1] = particleVertices[0] - particle->getVel();
		ofPoint surfaceMid, particleMid;
		for(int i=0; i<4; i++){
			surfaceMid += surfaceVertices[i];
		}
		surfaceMid *= 0.25f;
		particleMid = (particleVertices[0] + particleVertices[1]) * 0.5f;
		int totalVertices = 6;
		for(int i=0; i<totalVertices; i++){
			if(i<4){
				edgeVec = surfaceVertices[i] - surfaceVertices[(i+1)%4];
			} else {
				edgeVec = particleVertices[i - 4] - particleVertices[(i+3)%2];
			}
			axis.set(-edgeVec.y, edgeVec.x);
			axis.normalize();
			float minA, maxA, minB, maxB;
			project(surfaceVertices, 4, axis, minA, maxA);
			project(particleVertices, 2, axis, minB, maxB);
			float intervalDistance = getIntervalDistance(minA, maxA, minB, maxB);
			if(intervalDistance > 0){
				ci.bCollide = false;
				return ci;
			}
			intervalDistance = fabs(intervalDistance);
			if(intervalDistance < minInterval){
				minInterval = intervalDistance;
				ci.normal.set(axis.x, axis.y);
				ci.penetration = minInterval;
				ofxVec2f d = surfaceMid - particleMid;
				if(d.dot(axis) < 0) ci.normal *= -1;
			}
		}
		
		return ci;
	}
	
	static inline void project(ofPoint* vertices, int numVertices, const ofPoint& axis, float& min, float& max){
		ofxVec2f pt = vertices[0];
		float dotProduct = pt.dot(axis);
		min = dotProduct;
		max = dotProduct;
		for(int i=1; i<numVertices; i++){
			pt = vertices[i];
			dotProduct = pt.dot(axis);
			if(dotProduct < min){
				min = dotProduct;
			}
			if(dotProduct > max){
				max = dotProduct;
			}
		}
	}
	
	static inline float getIntervalDistance(float minA, float maxA, float minB, float maxB){
		if(minA < minB) return minB - maxA;
		return minA - maxB;
	}
};