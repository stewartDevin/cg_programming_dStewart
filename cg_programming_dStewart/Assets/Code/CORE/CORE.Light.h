// CORE.Light.h
////////////////////////////////////////////////////////////////
#pragma once

#include "../Application.h"
#include "CORE.GameObject.h"

class Light : public GameObject {
public:

	// public member variables
	int type;
	vec3 lightColor;
	float lightPower;

	// constructor functions
	Light();
	Light(Transform transform, int type);
	Light(Transform transform, vec3 lightColor, float lightPower, int type);
};