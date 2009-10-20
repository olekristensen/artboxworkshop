#pragma once

#include "FadableBase.h"

class Fader: public FadableBase{
public:
	void draw(float x, float y,	float w, float h){
		//if(alpha <= 0.0f) return;
		
		ofEnableAlphaBlending();
		glColor4f(0.0f, 0.0f, 0.0f, alpha);
		ofSetRectMode(OF_RECTMODE_CORNER);
		glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x + w, y);
		glVertex2f(x + w, y + h);
		glVertex2f(x, y + h);
		glEnd();
	}
};