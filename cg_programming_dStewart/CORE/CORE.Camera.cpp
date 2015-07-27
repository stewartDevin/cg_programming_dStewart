// CORE.Camera.cpp
////////////////////////////////////////////////////////

#include "CORE.Camera.h"
#include "..\APP\APP.DataCore.h"
#include "CORE.Mouse.h"
#include "CORE.Keyboard.h"

// camera constructor functions.
Camera::Camera() {
	this->followSpeed = 0.0f;
	this->transform = Transform();
	this->up = vec3(0.0f, 1.0f, 0.0f);
	this->right = vec3(1.0f, 0.0f, 0.0f);
	this->forward = vec3(0.0f, 0.0f, 0.0f);
	this->viewMatrix = glm::lookAt(
		this->transform.position,		// position
		this->transform.position+this->forward,		// look at
		this->up		// up
		);
	this->MVPMatrixID = NULL;
	this->followTargetSet = false;
	// horizontal angle : toward -Z
	this->horizontalAngle = 3.14f;
	// vertical angle : 0, look at the horizon
	this->verticalAngle = 0.0f;
	this->isInitialized = false;
	this->initialFoV = FIELD_OF_VIEW;
	this->projectionMatrix = perspective(this->initialFoV, DataCore::aspectRatio, Z_NEAR, Z_FAR);
	this->moveSpeed = 3.0f; // 3 units / second
	this->FoV = this->initialFoV;
}

Camera::Camera(vec3 position) {
	this->followSpeed = 0.0f;
	this->transform = Transform();
	this->transform.position = position;
	this->up = vec3(0.0f, 1.0f, 0.0f);
	this->right = vec3(1.0f, 0.0f, 0.0f);
	this->forward = vec3(0.0f, 0.0f, 0.0f);
	this->viewMatrix = glm::lookAt(
		this->transform.position,		// position
		this->transform.position + this->forward,		// look at
		this->up		// up
		);
	this->MVPMatrixID = NULL;
	this->followTargetSet = false;
	// horizontal angle : toward -Z
	this->horizontalAngle = 3.14f;
	// vertical angle : 0, look at the horizon
	this->verticalAngle = 0.0f;
	this->isInitialized = false;
	this->initialFoV = FIELD_OF_VIEW;
	this->projectionMatrix = perspective(this->initialFoV, DataCore::aspectRatio, Z_NEAR, Z_FAR);
	this->moveSpeed = 3.0f; // 3 units / second
	this->FoV = this->initialFoV;
}

Camera::Camera(vec3 position, vec3 up, vec3 forward) {
	this->followSpeed = 0.0f;
	this->transform = Transform();
	this->transform.position = position;
	this->up = up;
	this->right = vec3(1.0f, 0.0f, 0.0f);
	this->forward = forward;
	
	this->viewMatrix = glm::lookAt(
		this->transform.position,		// position
		this->transform.position + this->forward,		// look at
		this->up		// up
		);
	this->MVPMatrixID = NULL;
	this->followTargetSet = false;
	// horizontal angle : toward -Z
	this->horizontalAngle = 3.14f;
	// vertical angle : 0, look at the horizon
	this->verticalAngle = 0.0f;
	this->isInitialized = false;
	this->initialFoV = FIELD_OF_VIEW;
	this->projectionMatrix = perspective(this->initialFoV, DataCore::aspectRatio, Z_NEAR, Z_FAR);
	this->moveSpeed = 3.0f; // 3 units / second
	this->FoV = this->initialFoV;
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
	if (!this->isInitialized) this->Init();

	//vec3 forward = vec3(0.0f, 0.0f, 0.0f);

	// get the forward of the camera
	//forward = this->transform.position;
	//forward.z = 1.0f;
	
	//forward = DataCore::playerMesh->transform.position;

	///////////////////////////////////////////////
	// for FPS camera
	
	this->CalculateVectors();

	this->viewMatrix = glm::lookAt(
		this->transform.position,	 // position
		this->transform.position + this->forward, // look at
		this->up		// up
		);
}

void Camera::CalculateVectors() {
	// forward : Spherical coordinates to Cartesian coordinates conversion
	this->forward = vec3(
		cos(this->verticalAngle) * sin(this->horizontalAngle),
		sin(this->verticalAngle),
		cos(this->verticalAngle) * cos(this->horizontalAngle)
		);

	// Right vector
	this->right = glm::vec3(
		sin(this->horizontalAngle - 3.14f / 2.0f),
		0,
		cos(this->horizontalAngle - 3.14f / 2.0f)
		);

	// Up vector : perpendicular to both direction and right
	this->up = glm::cross(this->right, this->forward);

}

void Camera::Init() {
	// init MVP Matrix ID
	this->MVPMatrixID = glGetUniformLocation(DataCore::programID, "MVP");

	// init perspective.
	this->projectionMatrix = perspective(this->initialFoV, DataCore::aspectRatio, Z_NEAR, Z_FAR);

	// initialized = true;
	this->isInitialized = true;
}

void Camera::MoveWithFPSControls() {
	if (Keyboard::Q) {
		this->transform.position -= this->up * DataCore::deltaTime * this->moveSpeed;
	}
	if (Keyboard::W) {
		this->transform.position += this->forward * DataCore::deltaTime * this->moveSpeed;
	}
	if (Keyboard::E) {
		this->transform.position += this->up * DataCore::deltaTime * this->moveSpeed;
	}
	if (Keyboard::A) {
		this->transform.position -= this->right * DataCore::deltaTime * this->moveSpeed;
	}
	if (Keyboard::S) {
		this->transform.position -= this->forward * DataCore::deltaTime * this->moveSpeed;
	}
	if (Keyboard::D) {
		this->transform.position += this->right * DataCore::deltaTime * this->moveSpeed;
	}

}

void Camera::Follow(vec3 targetPosition, float speed) {
	this->followSpeed = speed;
	this->transform.position.x += (this->followSpeed * (targetPosition.x - this->transform.position.x)) * DataCore::deltaTime;
	this->transform.position.y += (this->followSpeed * (targetPosition.y - this->transform.position.y)) * DataCore::deltaTime;
}