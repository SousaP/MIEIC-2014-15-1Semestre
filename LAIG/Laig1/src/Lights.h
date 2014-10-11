#ifndef _LIGHTS_H_
#define _LIGHTS_H_

#include "CGFlight.h"
#include "CGFobject.h"
#include <string>

class Light
{
	string id;
	CGFlight* lightt;
	string type;
	bool marker;
	float pos[3];

public:
	Light();
	Light(string id,CGFlight *l, float* p, string t, bool m);
	CGFlight * getLight();

};


class SpotLight : public Light{
	float target[3];
	float exponent, angle;

public:
	SpotLight(string id,CGFlight*L, float* p, string t, bool m, float*targ, float exp, float angle);

};

Light :: Light(string id,CGFlight *l, float *p,string t, bool m){
	this->id = id;
	this->marker = m;
	this->lightt = l;
	this-> type = t;
	pos[0] = p[0];
	pos[1] = p[1];
	pos[2] = p[2];
}


CGFlight * Light ::getLight(){
	return lightt;
}

SpotLight :: SpotLight(string id,CGFlight*L, float* p, string t,bool m, float*targ, float exp, float angle)
	: Light(id,L,p,t,m)
{
	target[0] = targ[0];
	target[1] = targ[1];
	target[2] = targ[2];
	exponent = exp;
	this->angle = angle;
}

#endif