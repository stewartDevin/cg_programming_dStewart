// CORE.Transform.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "../Application.h"

///////////////////////////////////////////////////////////////////////////////
// Transform
class Transform {
public:
	vec3 position;
	vec3 scale;
	vec3 rotation;
	vec3 velocity;
	float angle;
	float rotationSpeed;

	Transform::Transform();
	Transform::Transform(vec3 position, vec3 scale, vec3 rotation, vec3 velocity);
};