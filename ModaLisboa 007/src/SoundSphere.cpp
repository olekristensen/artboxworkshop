

#include "SoundSphere.h"

SoundSphere::SoundSphere(float _radius, int _sphereRes){
	radius = _radius;
	sphereRes = 0;
	physics = new MyPhysics3d();
	setSphereResolution(_sphereRes);
}

SoundSphere::~SoundSphere(){
	for(int i=0; i<sphereRes; i++){
		for(int j=0; j<sphereRes; j++){
			physics->deleteParticle(points[i][j]);	
		}
		points[i].clear();
		bands[i].clear();
		pointNormals[i].clear();
	}
	delete physics;
}

void SoundSphere::update(MyFFT& fft){
	if(fft.getNumBands() != numBands){
		numBands = fft.getNumBands();
		int halfBands = (int)numBands*0.5f;
		for(int i=0; i<bands.size(); i++){
			for(int j=0; j<bands[i].size(); j++){
				bands[i][j] = (int)ofRandom(0, halfBands);
			}
		}
	}
	physics->update();
	ofPoint target,force;
	float fftVal;
	for(int i=0; i<points.size(); i++){
		for(int j=0; j<points[i].size(); j++){
			fftVal = fft.getBand(bands[i][j]) * 400;
			target = pointNormals[i][j] * (radius + fftVal);
			force = (target - *points[i][j]) * 0.1f;
			points[i][j]->applyForce(force);
		}
	}	
}

void SoundSphere::drawPoints(){
	glBegin(GL_POINTS);
	for(int i=0; i<sphereRes; i++){
		for(int j=0; j<sphereRes; j++){
			MyParticle& p = *points[i][j];
			glVertex3f(p.x, p.y, p.z);
		}
	}
	glEnd();
}

void SoundSphere::drawLines(){
	for(int i=0; i<sphereRes; i++){
		glBegin(GL_LINE_STRIP);
		for(int j=0; j<sphereRes; j++){
			MyParticle& p = *points[i][j];
			glVertex3f(p.x, p.y, p.z);
		}
		MyParticle& p = *points[0][0];
		glVertex3f(p.x, p.y, p.z);
		glEnd();
	}
}

void SoundSphere::drawQuads(){
	for(int i=0; i<sphereRes-2; i++){
		glBegin(GL_QUAD_STRIP);
		for(int j=0; j<sphereRes; j++){
			MyParticle& p1 = *points[i][j];
			MyParticle& p2 = *points[i+1][j];
			glVertex3f(p1.x, p1.y, p1.z);
			glVertex3f(p2.x, p2.y, p2.z);
		}
		MyParticle& p1 = *points[i][0];
		MyParticle& p2 = *points[i+1][0];
		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p2.x, p2.y, p2.z);
		glEnd();
	}
}

void SoundSphere::setSphereResolution(int _res){
	if(_res == sphereRes) return;
	for(int i=0; i<sphereRes; i++){
		for(int j=0; j<sphereRes; j++){
			physics->deleteParticle(points[i][j]);	
		}
		points[i].clear();
	}
	points.clear();

	sphereRes = _res;
	points.resize(sphereRes);
	points.reserve(sphereRes);
	pointNormals.resize(sphereRes);
	pointNormals.reserve(sphereRes);
	bands.resize(sphereRes);
	bands.reserve(sphereRes);
	numBands = 0;
	for(int i=0; i<points.size(); i++){
		points[i].resize(sphereRes);
		points[i].reserve(sphereRes);
		pointNormals[i].resize(sphereRes);
		pointNormals[i].reserve(sphereRes);
		bands[i].resize(sphereRes);
		bands[i].reserve(sphereRes);
		for(int j=0; j<sphereRes; j++){
			points[i][j] = new MyParticle();
			points[i][j]->setDrag(0.6f);
			physics->addParticle(points[i][j]);
		}
	}
	
	float posX, posY, posZ;
	float phi, theta;
	for(int i=0; i<points.size(); i++){
		theta = TWO_PI / points.size() * i;
		for(int j=0; j<points[i].size(); j++){
			phi = TWO_PI / points[i].size() * j;
			pointNormals[i][j].x = cos(theta) * sin(phi);
			pointNormals[i][j].y = sin(theta) * sin(phi);
			pointNormals[i][j].z = cos(phi);
			points[i][j]->x = pointNormals[i][j].x * radius;
			points[i][j]->y = pointNormals[i][j].y * radius;
			points[i][j]->z = pointNormals[i][j].z * radius;
		}
	}
}