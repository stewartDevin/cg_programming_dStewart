// CORE.Camera.cpp
////////////////////////////////////////////////////////

#include "CORE.Camera.h"
#include "..\APP\APP.DataCore.h"

// camera constructor functions.
Camera::Camera() {
	this->transform = Transform();
	this->up = vec3(0.0f, 1.0f, 0.0f);
	this->lookAt = vec3(0.0f, 0.0f, 0.0f);
	this->projectionMatrix = perspective(FIELD_OF_VIEW, DataCore::aspectRatio, Z_NEAR, Z_FAR);
	this->viewMatrix = glm::lookAt(
		this->transform.position,		// position
		this->lookAt,		// look at
		this->up		// up
		);
	GLuint MVPMatrixID = NULL;
}

Camera::Camera(vec3 position) {
	this->transform = Transform();
	this->transform.position = position;
	this->up = vec3(0.0f, 1.0f, 0.0f);
	this->lookAt = vec3(0.0f, 0.0f, 0.0f);
	this->projectionMatrix = perspective(FIELD_OF_VIEW, DataCore::aspectRatio, Z_NEAR, Z_FAR);
	this->viewMatrix = glm::lookAt(
		this->transform.position,		// position
		this->lookAt,		// look at
		this->up		// up
		);
	GLuint MVPMatrixID = NULL;
}

Camera::Camera(vec3 position, vec3 up, vec3 forward) {
	this->transform = Transform();
	this->transform.position = position;
	this->up = up;
	this->lookAt = forward;
	this->projectionMatrix = perspective(FIELD_OF_VIEW, DataCore::aspectRatio, Z_NEAR, Z_FAR);
	this->viewMatrix = glm::lookAt(
		this->transform.position,		// position
		this->lookAt,		// look at
		this->up		// up
		);
	GLuint MVPMatrixID = NULL;
}

// member functions
void Camera::Update() {
	vec3 tempVec(0.0f, 0.0f, 0.0f);

	tempVec = this->transform.position;
	tempVec.z = 1.0f;
	
	//float length = tempVec.length();
	//tempVec /= length;
	
	this->viewMatrix = glm::lookAt(
		this->transform.position,		// position
		tempVec,
		//this->lookAt,		// look at
		this->up		// up
		);
}