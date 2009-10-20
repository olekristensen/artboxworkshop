#include "SceneSmoke.h"

SceneSmoke::SceneSmoke(){
	for(int i=0; i<1; i++){
		createParticleEmmiter();
	}
	particlePool = new SoundReactiveParticle*[MAX_PARTICLES];
	for(int i=0; i<MAX_PARTICLES; i++){
		particlePool[i] = new SoundReactiveParticle();
		particlePool[i]->disable();
	}
	partPoints.resize(MAX_PARTICLES * 3);
	partSizes.resize(MAX_PARTICLES);
	//partAlphas.resize(MAX_PARTICLES);
	partColors.resize(MAX_PARTICLES*4);
	emiterCenter.x = SCENE_W * 0.5f;
	emiterCenter.y = SCENE_H * 0.8f;
	emiterCenter.z = 0.0f;
	sceneCenter.x = SCENE_W * 0.5f;
	sceneCenter.y = SCENE_H * 0.5f;
	sceneCenter.z = 0.0f;
	counter = 0.0f;
	wind.set(0, -1);
	smokeTexture.loadImage("smoke.png");
	shader.loadShader("VBOShader");
	backgroundTexture.loadImage("background.png");
	foregroundTexture.loadImage("logo-aleksander-protic.png");
	namePos = sceneCenter;
	namePosTarget = sceneCenter;
	bExplosionMode = false;
	ofAddListener(ofEvents.keyReleased, this, &SceneSmoke::onKeyReleased);
	ofAddListener(ofEvents.keyPressed, this, &SceneSmoke::onKeyPressed);
#ifndef USE_LIVE_INPUT
	soundPlayer.loadSound("sound.mp3");
#endif
}

SceneSmoke::~SceneSmoke(){
	for(int i=0; i<emmiters.size(); i++){
		delete emmiters[i];	
	}
	emmiters.clear();
	for(int i; i<MAX_PARTICLES; i++){
		delete particlePool[i];
	}
	delete[] particlePool;
}

void SceneSmoke::update(MyFFT& fft){
	cam.updateSoundReactive(fft);
	physics->setGravity(wind);
	physics->update();
	counter += 0.05f;
	ofPoint force;
	float randomStep;
	float radXZ, radY;
	float averageFftVal = fft.getAveragePower();
	int numParticles;
	int halfBands = (int)(fft.getNumBands()*0.5f);
	for(int i=0; i<emmiters.size(); i++){
		ParticleEmmiter& p = *emmiters[i];
		p.update();
		randomStep = averageFftVal * 20 + 1;
		force.x = (emiterCenter.x - p.x) * 0.02f + ofRandom(-randomStep, randomStep);
		force.y = (emiterCenter.y - p.y) * 0.02f + ofRandom(-randomStep, randomStep);
		force.z = (emiterCenter.z - p.z) * 0.02f + ofRandom(-randomStep, randomStep);
		p.applyForce(force);
		numParticles = (int)(averageFftVal * 50);
		for(int j=0; j<numParticles; j++){
			createParticle(p, 15, 100);
		}
	}
	float noiseRes = 0.01f;
	float noiseMul = 2;
	randomStep = 2;
	int partIndex;
	vector<MyParticle*>& particles = physics->getParticles();
	for(int i=0; i<particles.size(); i++){
		SoundReactiveParticle& p = *(SoundReactiveParticle*)particles[i];
		if(p.getLifeNorm() <= 0.0f){
			removeParticle(i);
		} else{
			p.updateSoundReactive(fft);
			radXZ = getNoise(p.x*noiseRes, p.z*noiseRes, counter*3)*TWO_PI;
			radY = getNoise(p.x*noiseRes, p.y*noiseRes, counter*3)*TWO_PI;
			noiseMul = 2 + (2 * averageFftVal);
			force.x = cos(radXZ) * noiseMul + ofRandom(-randomStep, randomStep);
			force.y = -sin(radY) * noiseMul + ofRandom(-randomStep, randomStep);
			force.z = sin(radXZ) * noiseMul + ofRandom(-randomStep, randomStep);
			p.applyForce(force);
			partIndex = i*3;
			partPoints[partIndex] = p.x;
			partPoints[partIndex+1] = p.y;
			partPoints[partIndex+2] = p.z;
			partSizes[i] = p.getRadius();
			partIndex = i*4;
			ofColor& col = p.getColor();
			partColors[partIndex] = 0.5f;
			partColors[partIndex+1] = 0.5f;
			partColors[partIndex+2] = 0.5f;
			partColors[partIndex+3] = col.a;
		}
	}
	/*
	float rotStep = averageFftVal * 5;
	float maxRot = 10.0f;
	nameRotTarget *= 0.9;
	nameRotTarget.x += ofRandom(-rotStep, rotStep);
	nameRotTarget.y += ofRandom(-rotStep, rotStep);
	if(nameRotTarget.x < -maxRot)nameRotTarget.x = -maxRot;
	else if(nameRotTarget.x > maxRot)nameRotTarget.x = maxRot;
	if(nameRotTarget.y < -maxRot)nameRotTarget.y = -maxRot;
	else if(nameRotTarget.y > maxRot) nameRotTarget.y = maxRot;
	nameRot += (nameRotTarget - nameRot) * 0.1f;
	float posStep = averageFftVal * 10;
	namePosTarget.x += ofRandom(-posStep, posStep);
	namePosTarget.y += ofRandom(-posStep, posStep);
	namePosTarget.z += ofRandom(-posStep, posStep);
	namePosTarget += (ofPoint(sceneCenter.x, sceneCenter.y, sceneCenter.z) - namePosTarget) * 0.1f;
	namePos += (namePosTarget - namePos) * 0.1f;*/
	
	if(bExplosionMode){
		float minRadius = 3;
		float maxRadius = (int)ofRandom(10, 20);
		for(int i=0; i<200; i++){
			createParticle(*emmiters[0], minRadius, maxRadius);
		}
	}
}

void SceneSmoke::draw(){
	/*ofSetRectMode(OF_RECTMODE_CENTER);
	ofxVec3f camPos = cam.getPosition();
	float diffX = (backgroundTexture.getWidth() - 600) * 0.5f;
	float diffY = (backgroundTexture.getHeight() - 800) * 0.5f;
	float maxBG_X = 300 + diffX;
	float minBG_X = 300 - diffX;
	float maxBG_Y = 400 + diffY;
	float minBG_Y = 400 - diffY;
	float bgX = MAX(minBG_X, MIN(maxBG_X, camPos.x));
	float bgY = MAX(minBG_Y, MIN(minBG_Y, camPos.y));
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	backgroundTexture.draw(bgX, bgY);
	//backgroundTexture.draw(camPos.x, camPos.y);*/
	cam.place();
	ofSetRectMode(OF_RECTMODE_CORNER);
	shader.setShaderActive(true);
	smokeTexture.getTextureReference().bind();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLint sizeArrayLoc = glGetAttribLocationARB(shader.shader, "partSize");
	glVertexAttribPointerARB(sizeArrayLoc, 1, GL_FLOAT, false, 0, &partSizes[0]);
	glBindAttribLocationARB(shader.shader, sizeArrayLoc, "partSize");
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnableVertexAttribArrayARB(sizeArrayLoc);
	
	glEnable(GL_POINT_SPRITE);
	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, &partColors[0]);
	glVertexPointer(3, GL_FLOAT, 0, &partPoints[0]);
	glDrawArrays(GL_POINTS, 0, physics->getNumParticles());
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	smokeTexture.getTextureReference().unbind();
	shader.setShaderActive(false);
	cam.remove();
	/*glDisable(GL_DEPTH_TEST);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glRotatef(nameRot.x, 0.0f, 1.0f, 0.0f);
	glRotatef(nameRot.y, 1.0f, 0.0f, 0.0f);
	glTranslatef(namePos.x, namePos.y, namePos.z);
	ofSetRectMode(OF_RECTMODE_CENTER);
	foregroundTexture.draw(-3.0f, 0.0f, 320, 320);
	ofSetRectMode(OF_RECTMODE_CORNER);
	glPopMatrix();*/
}

ParticleEmmiter* SceneSmoke::createParticleEmmiter(){
	ParticleEmmiter* e = new ParticleEmmiter(physics, emiterCenter.x, emiterCenter.y);
	e->setDrag(0.7f);
	emmiters.push_back(e);
	return e;
}

bool SceneSmoke::deleteParticleEmmiter(unsigned int emmiterIndex){
	if(emmiterIndex >= emmiters.size()) return false;
	delete emmiters[emmiterIndex];
	emmiters.erase(emmiters.begin() + emmiterIndex);
	return true;
}

bool SceneSmoke::deleteParticleEmmiter(ParticleEmmiter* p){
	for(int i=0; i<emmiters.size(); i++){
		if(emmiters[i] == p){
			delete p;
			emmiters.erase(emmiters.begin() + i);
			return true;
		}
	}
	return false;
}

void SceneSmoke::openScene(){
#ifndef USE_LIVE_INPUT
	soundPlayer.play();
#endif
}

void SceneSmoke::closeScene(){
#ifndef USE_LIVE_INPUT
	soundPlayer.stop();
#endif
}

void SceneSmoke::createParticle(ParticleEmmiter& p, float minRadius, float maxRadius){
	for(int i=0; i<MAX_PARTICLES; i++){
		if(particlePool[i]->isDisabled()){
			if(bExplosionMode){
				float radius = ofRandom(minRadius, maxRadius);
				SoundReactiveParticle& newPart = *particlePool[i];
				newPart.setPos(p);
				newPart.stopMotion();
				newPart.setRadius(radius);
				newPart.setMass(radius*0.1f);
				newPart.setDrag(0.8f);
				newPart.setLifeSeconds(2.0f);
				newPart.enable();
				float bandNorm = ofRandomuf();
				int band = (int)bandNorm;
				newPart.setBand(bandNorm);
				newPart.applyForce(p.getVel()*20);
				newPart.setColor(1.0f, 1.0f, 1.0f, 0.0f);
				physics->addParticle(particlePool[i]);
			}else {
				float radius = ofRandom(minRadius, maxRadius);
				SoundReactiveParticle& newPart = *particlePool[i];
				newPart.setPos(p);
				newPart.stopMotion();
				newPart.setRadius(radius);
				newPart.setMass(radius*0.1f);
				newPart.setDrag(0.8f);
				newPart.setLifeSeconds(3.0f);
				newPart.enable();
				float bandNorm = ofRandomuf();
				int band = (int)bandNorm;
				newPart.setBand(bandNorm);
				newPart.applyForce(p.getVel()*5);
				newPart.setColor(0.0f, 0.0f, 0.0f, 0.0f);
				physics->addParticle(particlePool[i]);
			}
			break;
		}
	}
}

void SceneSmoke::removeParticle(unsigned int partIndex){
	vector<MyParticle*>& parts = physics->getParticles();
	if(partIndex >= parts.size())return;
	removeParticle(parts[partIndex]);
}

void SceneSmoke::removeParticle(MyParticle* p){
	if(physics->removeParticle(p)){
		p->disable();
	}
}

void SceneSmoke::setExplosionMode(bool _bMode){
	bExplosionMode = _bMode;
}

void SceneSmoke::onKeyReleased(ofKeyEventArgs& e){
	if(e.key == ' '){
		bExplosionMode = false;
	}
}

void SceneSmoke::onKeyPressed(ofKeyEventArgs& e){
	if(e.key == ' '){
		bExplosionMode = true;
	}
}


