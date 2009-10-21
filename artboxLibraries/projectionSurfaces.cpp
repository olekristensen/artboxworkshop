#include "projectionSurfaces.h"



#pragma mark Object


ProjectionSurfacesObject::ProjectionSurfacesObject(){
	for(int i=0;i<4;i++){
		corners[i] = new ofxPoint2f;
	}
	*corners[0] = ofxPoint2f(0,0);
	*corners[1] = ofxPoint2f(1,0);
	*corners[2] = ofxPoint2f(1,1);
	*corners[3] = ofxPoint2f(0,1);
	
}

void ProjectionSurfacesObject::recalculate(){
	for(int i=0;i<4;i++){
		warp->SetCorner(i, (*corners[i]).x, (*corners[i]).y);
	}
	
	warp->MatrixCalculate();
	ofxPoint2f a[4];
	a[0] = ofxPoint2f(0,0);
	a[1] = ofxPoint2f(1,0);
	a[2] = ofxPoint2f(1,1);
	a[3] = ofxPoint2f(0,1);
	coordWarp->calculateMatrix(a, warp->corners);
}

void ProjectionSurfacesObject::SetCorner(int n, float x, float y){
	corners[n]->set(x,y);
}

void ProjectionSurfacesObject::drawCalibration(){
	ofPoint pos[4];
	for(int i=0; i<4; i++){
		pos[i] = *corners[i];
		pos[i].x *= ofGetWidth();
		pos[i].y *= ofGetHeight();
	}
	
	glColor3f(1.0f, 0.0f, 1.0f);
	ofDrawBitmapString(ofToString(surfaceId), pos[0].x + 10, pos[0].y + 10);
	glColor3f(1.0f, 0.0f, 0.0f);
	
	for(int i=0; i<4; i++){
		ofCircle(pos[i].x, pos[i].y, 3);
	}
	glBegin(GL_LINE_STRIP);
	for(int i=0; i<4; i++){
		glVertex2f(pos[i].x, pos[i].y);
	}
	glVertex2f(pos[0].x, pos[0].y);
	glEnd();
}




#pragma mark Class

void ProjectionSurfaces::setup(){
	/*
	 for(int i=0;i<_numSurfaces ;i++){
	 surfaces.push_back(new ProjectionSurfacesObject);
	 surfaces[i]->warp = new Warp();
	 surfaces[i]->coordWarp = new coordWarping;
	 surfaces[i]->aspect = 1.0;
	 surfaces[i]->recalculate();
	 }	
	 
	 selectedCorner = 0;
	 selectedKeystoner = -1;
	 */
	ofAddListener(ofEvents.mousePressed, this, &ProjectionSurfaces::mousePressed);
	ofAddListener(ofEvents.mouseDragged, this, &ProjectionSurfaces::mouseDragged);
	ofAddListener(ofEvents.keyPressed, this, &ProjectionSurfaces::keyPressed);	
	
	keystoneXml = new ofxXmlSettings;
	keystoneXml->loadFile("../../../artboxLibraries/surfaces.xml");
	//loadXml();
}

void ProjectionSurfaces::addSurface(ProjectionSurfacesObject * surface){
	surface->surfaceId = surfaces.size();
	surfaces.push_back(surface);
	surface->warp = new Warp();
	surface->coordWarp = new coordWarping;
	surface->aspect = 1.0;
	surface->recalculate();
	
	selectedCorner = 0;
	selectedKeystoner = 0;
	
	loadXml();
}

ProjectionSurfacesObject * ProjectionSurfaces::getSurface(int surface){
	return surfaces[surface];
}
void ProjectionSurfaces::applyProjection(int surface, float _w, float _h){
	if(surface >= surfaces.size()){
		ofLog(OF_LOG_WARNING, "surface index out of bounds");
		return;
	}
	glPushMatrix();
	ProjectionSurfacesObject * obj = getSurface(surface);
	float setW = 1.0/ (obj->aspect);
	float setH = 1.0;
	
	glScaled(_w, _h, 1.0);
	obj->warp->MatrixMultiply();
	glScaled(setW, setH, 1.0);
	
}
ofxVec2f  ProjectionSurfaces::convertToCoordinate(int surface,  ofxVec2f v){
	ProjectionSurfacesObject * obj = getSurface(surface);
	ofxVec2f r;
	ofxPoint2f p = obj->coordWarp->inversetransform(v.x, v.y);
	r.x = p.x*obj->aspect;
	r.y = p.y;
	return r;
}

ofxVec2f  ProjectionSurfaces::convertBetweenSurfaces(int obj1, int obj2,  ofxVec2f v){
	ofxVec2f proj = convertToCoordinate(obj1, v);
	ofxVec2f p = convertToCoordinate(obj2, proj);
	return p;
}

void ProjectionSurfaces::mousePressed(ofMouseEventArgs & args){
	if(selectedKeystoner != -1){		
		ofxVec2f curMouse = ofxVec2f((float)args.x/ofGetWidth(), ((float)args.y/ofGetHeight()));
		selectedCorner = surfaces[selectedKeystoner]->warp->GetClosestCorner(curMouse.x, curMouse.y);
		lastMousePos = curMouse;
	}
}

void ProjectionSurfaces::mouseDragged(ofMouseEventArgs & args){
	if(selectedKeystoner != -1){
		
		ofxVec2f curMouse = ofxVec2f((float)args.x/ofGetWidth(),( (float)args.y/ofGetHeight()));
		ofxVec2f newPos =  surfaces[selectedKeystoner]->warp->corners[selectedCorner] + (curMouse-lastMousePos);
		surfaces[selectedKeystoner]->SetCorner(selectedCorner, newPos.x, newPos.y);
		lastMousePos = curMouse;
		for(int i=0;i<surfaces.size();i++){
			surfaces[i]->recalculate();
		}	
		saveXml();
	}
}

void ProjectionSurfaces::keyPressed(ofKeyEventArgs & args){
	bool setCorner = true;
	bool doneSomething = false;
	if(selectedKeystoner != -1){
		ofxVec2f newPos =  surfaces[selectedKeystoner]->warp->corners[selectedCorner] ;
		
		
		if(args.key == OF_KEY_DOWN){
			newPos -= ofxVec2f(0,-0.0003);
			doneSomething = true;
		}
		if(args.key == OF_KEY_UP){
			newPos += ofxVec2f(0,-0.0003);
			doneSomething = true;
		}
		if(args.key == OF_KEY_LEFT){
			newPos += ofxVec2f(-0.0003,0);
			doneSomething = true;
		}
		if(args.key == OF_KEY_RIGHT){
			newPos -= ofxVec2f(-0.0003,0);
			doneSomething = true;
		}
		
		if(setCorner){
			surfaces[selectedKeystoner]->SetCorner(selectedCorner, newPos.x, newPos.y);
			for(int i=0;i<surfaces.size();i++){
				surfaces[i]->recalculate();
			}	
		}
	}
	if(args.key >= '1' && args.key <= '9'){
		selectedKeystoner = args.key-49;
		setCorner = false;
		doneSomething = true;
	}
	
	if(!doneSomething){
		selectedKeystoner = -1;
	}
	saveXml();
	
}

void ProjectionSurfaces::saveXml(){
	keystoneXml->clear();
	for (int i=0;i<surfaces.size(); i++) {
		keystoneXml->addTag("surface");
		keystoneXml->pushTag("surface", i);
		for(int u=0;u<4;u++){
			keystoneXml->addTag("corner");
			keystoneXml->addAttribute("corner", "x", getSurface(i)->warp->corners[u].x, u);
			keystoneXml->addAttribute("corner", "y", getSurface(i)->warp->corners[u].y, u);		
		}
		keystoneXml->popTag();
	}
	keystoneXml->saveFile("../../../artboxLibraries/surfaces.xml");
}

void ProjectionSurfaces::loadXml(){
	for (int i=0;i<surfaces.size(); i++) {
		keystoneXml->pushTag("surface", i);
		for(int u=0;u<4;u++){
			getSurface(i)->SetCorner(u ,  keystoneXml->getAttribute("corner", "x", 0.0, u),  keystoneXml->getAttribute("corner", "y", 0.0, u));
		}
		keystoneXml->popTag();
		getSurface(i)->recalculate();
	}
	
	
}

