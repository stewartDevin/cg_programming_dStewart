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
	vec3 right;
	vec3 forward;
	mat4 projectionMatrix;
	mat4 viewMatrix;
	GLuint MVPMatrixID;
	float followSpeed;
	bool followTargetSet;
	bool isInitialized;

	// horizontal angle : toward -Z
	float horizontalAngle;
	// vertical angle : 0, look at the horizon
	float verticalAngle;
	// Initial Field of View
	float initialFoV;
	float FoV;

	float moveSpeed; // 3 units / second
	

	// constructor functions
	Camera::Camera();
	Camera::Camera(vec3 position);
	Camera::Camera(vec3 position, vec3 up, vec3 forward);

	// member functions
	void Update();
	void Follow(vec3 targetPosition, float speed);
	void ConstrainMovement(float left, float top, float right, float bottom);
	void LookAtTarget(vec3 targetPosition);
	void MoveWithFPSControls();

	// private section
private:
	// private member functions
	void Init();

};