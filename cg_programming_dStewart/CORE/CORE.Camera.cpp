// CORE.Camera.cpp
////////////////////////////////////////////////////////

#include "CORE.Camera.h"
#include "..\APP\APP.DataCore.h"

// camera constructor functions.
Camera::Camera() {
	this->followSpeed = 0.0f;
	this->transform = Transform();
	this->up = vec3(0.0f, 1.0f, 0.0f);
	this->lookAt = vec3(0.0f, 0.0f, 0.0f);
	this->projectionMatrix = perspective(FIELD_OF_VIEW, DataCore::aspectRatio, Z_NEAR, Z_FAR);
	this->viewMatrix = glm::lookAt(
		this->transform.position,		// position
		this->lookAt,		// look at
		this->up		// up
		);
	this->MVPMatrixID = NULL;
	this->followTargetSet = false;
	// horizontal angle : toward -Z
	this->horizontalAngle = 3.14f;
	// vertical angle : 0, look at the horizon
	this->verticalAngle = 0.0f;
}

Camera::Camera(vec3 position) {
	this->followSpeed = 0.0f;
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
	this->MVPMatrixID = NULL;
	this->followTargetSet = false;
	// horizontal angle : toward -Z
	this->horizontalAngle = 3.14f;
	// vertical angle : 0, look at the horizon
	this->verticalAngle = 0.0f;
}

Camera::Camera(vec3 position, vec3 up, vec3 forward) {
	this->followSpeed = 0.0f;
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
	this->MVPMatrixID = NULL;
	this->followTargetSet = false;
	// horizontal angle : toward -Z
	this->horizontalAngle = 3.14f;
	// vertical angle : 0, look at the horizon
	this->verticalAngle = 0.0f;
}

// member functions
void Camera::ConstrainMovement(float left, float top, float right, float bottom) {
	if(this->transform.position.x <= left) {
		this->transform.position.x = left;
	}
	if(this->transform.position.y >= top) {
		this->transform.position.y = top;
	}
	if(this->transform.position.x >= right) {
		this->transform.position.x = right;
	}
	if(this->transform.position.y <= bottom) {
		this->transform.position.y = bottom;
	}
}

void Camera::Update() {
	vec3 forward = vec3(0.0f, 0.0f, 0.0f);

	// get the forward of the camera
	forward = this->transform.position;
	forward.z = 1.0f;
	
	//forward = DataCore::playerMesh->transform.position;

	this->viewMatrix = glm::lookAt(
		this->transform.position,	 // position
		//forward,        // look at
		this->lookAt,        
		this->up		// up
		);
}

void LookAtTarget(vec3 targetPosition) {

}

void Camera::Follow(vec3 targetPosition, float speed) {
	this->followSpeed = speed;
	this->transform.position.x += (this->followSpeed * (targetPosition.x - this->transform.position.x)) * DataCore::deltaTime;
	this->transform.position.y += (this->followSpeed * (targetPosition.y - this->transform.position.y)) * DataCore::deltaTime;
}