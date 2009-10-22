#pragma once

#include "projectionSurfaces.h"
#include "ofxOpenCv.h"


class BoxProjection: public ProjectionSurfacesObject{
protected:
	float height;
	friend class BoxProjectionManager;
	ofxCvColorImage* tex;

public:
	BoxProjection(){
		tex = NULL;
	}
	virtual ~BoxProjection(){
	}
	virtual void setTexture(ofxCvColorImage*t){
		tex = t;
	}
	virtual void update() = 0;
	virtual void draw() = 0;
};

