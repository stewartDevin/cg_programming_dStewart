// CORE.Light.cpp
////////////////////////////////////////////////////////////////

#include "CORE.Light.h"

// constructor functions
Light::Light() {
	this->lightColor = vec3(1.0, 1.0, 1.0);
	this->lightPower = 0.5f;
	this->type = 0;
}

Light::Light(Transform transform, int type) {
	this->lightColor = vec3(1.0, 1.0, 1.0);
	this->lightPower = 0.5f;
	this->transform = transform;
	this->type = 0;
}

Light::Light(Transform transform, vec3 lightColor, float lightPower, int type) {
	this->lightColor = lightColor;
	this->lightPower = lightPower;
	this->transform = transform;
	this->type = 0;

}