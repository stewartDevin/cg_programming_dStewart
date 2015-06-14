// CORE.Camera.h
/////////////////////////////////////////////////////////////////////////
#pragma once

#include "../Application.h"
#include "CORE.Transform.h"

class Camera {
public:
	// variables
	Transform transform;
	vec3 up;
	vec3 lookAt;
	mat4 projectionMatrix;
	mat4 viewMatrix;
	GLuint MVPMatrixID;
	float followSpeed;

	// constructor functions
	Camera::Camera();
	Camera::Camera(vec3 position);
	Camera::Camera(vec3 position, vec3 up, vec3 forward);

	// member functions
	void Update();
	void Follow(vec3 targetPosition, float speed);
};