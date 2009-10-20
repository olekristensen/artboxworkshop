#pragma once


#include "MyFFT.h"
#include "MyPhysics3d.h"

class SceneBase{
protected:
	MyPhysics3d* physics;
public:
	SceneBase(){
		physics = new MyPhysics3d();
	}
	virtual ~SceneBase(){delete physics;}
	virtual void update(MyFFT& fft) = 0;
	virtual void draw() = 0;
	virtual void openScene(){}
	virtual void closeScene(){}
};

