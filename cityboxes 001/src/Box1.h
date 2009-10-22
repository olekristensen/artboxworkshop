#pragma once

#include "BoxProjection.h"

class Box1: public BoxProjection{
protected:
	float counter;
	ofPoint aabbMin, aabbMax;
public:
	
	Box1(){
		counter = 0;
		tex = NULL;
	}
	
	~Box1(){
		
	}
	
	void update(){
		counter += 0.0005f;
	}
	
	//draw a rectangle
	void draw(){
		if(tex == NULL){
		ofFill();
		glColor3f(0.5f, 0.5f, 0.5f);
		ofRect(0,0,1,1);
		} else {
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			tex->draw(0,0,1,1);
		}
	}
	
	inline bool isPointInside(float x, float y, float z){
		return x > aabbMin.x and x < aabbMax.x and y > aabbMin.y and y < aabbMax.y and z > aabbMin.z and z < aabbMin.x;
	}
};

