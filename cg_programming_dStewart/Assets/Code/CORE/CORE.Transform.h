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
	vec3 rotationAxis;
	vec3 velocity;
	float rotationAmount;
	bool isRotating;
	bool rotateAroundAxis;


	Transform::Transform();
	Transform::Transform(vec3 position, vec3 scale, vec3 rotation, vec3 velocity);
	Transform::Transform(vec3 position);

	void Transform::Rotate(float amount, vec3 rotationAxis, bool rotateAroundAxis);
};