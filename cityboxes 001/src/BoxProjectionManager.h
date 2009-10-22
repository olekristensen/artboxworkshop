#pragma once

#include "projectionSurfaces.h"
#include "Box1.h"
#include "ofxDirList.h"
#include "ofxOpenCv.h"

class BoxProjectionManager: public ProjectionSurfaces{
protected:
	vector<BoxProjection*> boxes;
	bool bCalibrate;
	vector<ofxCvColorImage*> textures;
	float brightnessAmount, contrastAmount;
public:
	BoxProjectionManager(){
		disableCalibration();
		ofxDirList dir;
		int numFiles = dir.listDir("textures");
		ofImage img;
		for(int i=0; i<numFiles; i++){
			img.loadImage(dir.getPath(i));
			img.setImageType(OF_IMAGE_COLOR);
			//ofImage *_img = new ofImage();
			//_img->loadImage(dir.getPath(i));
			ofxCvColorImage * cvImg = new ofxCvColorImage();
			cvImg->allocate(img.getWidth(), img.getHeight());
			cvImg->setFromPixels(img.getPixels(), cvImg->width, cvImg->height);
			textures.push_back(cvImg);
		}
		brightnessAmount = 50.0;
		contrastAmount = 50.0f;
	}
	
	void addBoxSurface(BoxProjection* box){
		addSurface(box);
		boxes.push_back(box);
		if(textures.size() > 0){
			box->setTexture(textures[box->surfaceId % textures.size()]);
		}
	}
	
	void update(){
		if(brightnessAmount != 0.0f or contrastAmount != 0.0f){
			for(int i=0; i<textures.size(); i++){
				brightnessAndContrast(*textures[i], brightnessAmount, contrastAmount);
				//textures[i]->flagImageChanged();
			}
		}
		for(int i=0; i<boxes.size(); i++){
			boxes[i]->update();
		}
	}
	
	void draw(){
		if(bCalibrate){
			for(int i=0; i<surfaces.size(); i++){
				boxes[i]->drawCalibration();
			}
		} else{
			for(int i=0; i<surfaces.size(); i++){
				applyProjection(i);
				boxes[i]->draw();
				glPopMatrix();
			}
		}
	}
	
	void enableCalibration(){
		ofShowCursor();	
		bCalibrate = true;
		ofBackground(200, 200, 200);
	}
	
	void disableCalibration(){
		ofHideCursor();
		bCalibrate = false;
		ofBackground(0,0,0);
	}
	
	void toggleCalibration(){
		if(bCalibrate)disableCalibration();
		else enableCalibration();
	}
	
	void brightnessAndContrast(ofxCvColorImage& img, float _bright, float _contrast){
		uchar data[ 256 ];
		CvMat * matrix;
		double delta, a, b;
		
		matrix = cvCreateMatHeader( 1, 256, CV_8UC1 );
		cvSetData( matrix, data, 0 );
		
		if ( _contrast>0 ) {
			delta = (127.*_contrast) / 128;
			a = 255. / ( 255.-(delta*2) );
			b = a * (_bright-delta);
		}
		else {
			delta = (-128.*_contrast) / 128;
			a = ( 256.-(delta*2) ) / 255.;
			b = ( a*_bright )+delta;
		}
		
		for( int i=0; i<256; i++ ) {
			int value = cvRound( (a*i)+b );
			data[i]	= (uchar) min( max(0,value), 255 );
		}
		
		cvLUT( img.getCvImage(), img.getCvImage(), matrix );
		cvReleaseMat( &matrix );
	}
	
};

