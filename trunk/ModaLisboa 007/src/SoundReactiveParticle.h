#pragma once

class SoundReactiveParticle: public MyParticle{
protected:
	int band;
	unsigned int lifeMillis;
	unsigned long timeAtCreation, timeToDie;
	float lifeNorm;
	ofColor color;
	bool bLimitedLife;
	float alphaIncrease;
	float fftVal;
	float iniRadius;
	float targetRadius;
public:
	SoundReactiveParticle(float _x = 0, float _y = 0, float _z = 0, float _radius = DEFAULT_RADIUS, float _drag = DEFAULT_DRAG):
	MyParticle(_x, _y, _z, _radius, _drag)
	{
		band = 0;
		iniRadius = radius;
		targetRadius = radius;
	}
	
	virtual ~SoundReactiveParticle(){
		
	}
	
	void update(float timeStep = 1.0f){
		if(bLimitedLife){
			unsigned long currentTime = ofGetSystemTime();
			if(currentTime > timeToDie)lifeNorm = 0.0f;
			else lifeNorm =  (float)(timeToDie - currentTime) / (float)(timeToDie - timeAtCreation);
		}
		MyParticle::update(timeStep);
		color.a = lifeNorm * 0.2f;
		color.r *= 0.99f;
		color.g *= 0.99f;
		color.b *= 0.99f;
		targetRadius = (iniRadius * lifeNorm) + (fftVal * 50);
		if(targetRadius > radius)radius = targetRadius;
		else radius += (targetRadius - radius) * 0.1f;
	}
	
	void updateSoundReactive(MyFFT& fft){
		float tempFFTval = fft.getBand(band);
		if(tempFFTval > fftVal){
			fftVal = tempFFTval;
		}else fftVal *= 0.9f;
	}
	
	void setBand(int _band){
		band = _band;
	}
	
	int getBand(){
		return band;	
	}
	
	virtual void setLifeSeconds(float seconds){ //if < 0.0 has infinite life
		if(seconds > 0.0f){
			bLimitedLife = true;
			lifeMillis = (unsigned long)(seconds*1000.0f);
			lifeNorm = 1.0f;
			timeAtCreation = ofGetSystemTime();
			timeToDie = timeAtCreation + lifeMillis;
		} else{
			bLimitedLife = false;
			lifeNorm = 1.0f;
			timeAtCreation = lifeMillis = timeToDie = 0UL;
		}	
	}
	virtual float getTotalLife(){ //seconds
		if(bLimitedLife){
			return (float)(timeToDie - timeAtCreation);
		}
		ofLog(OF_LOG_NOTICE, "MyParticle::getTotalLife - particle does not have limited life, returning 0");
		return 0.0f;
	}
	
	virtual float getRemainingLife(){ // seconds
		if(bLimitedLife){
			return getTotalLife() * getLifeNorm();
		}
		ofLog(OF_LOG_NOTICE, "MyParticle::getRemainingLife - particle does not have limitedlife, returning 0");
		return 0.0f;
	}
	
	virtual float getLifeNorm(){ //0..1 life
			return lifeNorm;
	}
	
	float getAlpha(){
		return MIN(1.0f, color.a + fftVal*20);
	}
	
	float getRadius(){
		return radius;
	}
	
	void setColor(const ofColor& _col){
		setColor(_col.r, _col.g, _col.b, _col.a);	
	}
	
	void setColor(float r, float g, float b, float a){
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}
	
	ofColor& getColor(){
		return color;	
	}
	
};
