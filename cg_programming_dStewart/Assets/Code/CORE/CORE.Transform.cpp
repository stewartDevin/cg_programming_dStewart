// CORE.Transform.cpp
//////////////////////////////////////////////////////////////////////////

#include "CORE.Transform.h"
#include "..\APP\APP.DataCore.h"

///////////////////////////////////////////////////////////////////////////////
// Transform
Transform::Transform() {
	this->position = vec3(0.0f, 0.0f, 0.0f);
	this->scale = vec3(1.0f, 1.0f, 1.0f);
	this->rotationAxis = vec3(0.0f, 1.0f, 0.0f);
	this->velocity = vec3(0.0f, 0.0f, 0.0f);
	this->rotationAmount = 0.0f;
	this->isRotating = false;
	this->rotateAroundAxis = false;
}

Transform::Transform(vec3 position, vec3 scale, vec3 rotationAxis, vec3 velocity) {
	this->position = position;
	this->scale = scale;
	this->rotationAxis = rotationAxis;
	this->velocity = velocity;
	this->rotationAmount = 0.0f;
	this->isRotating = false;
	this->rotateAroundAxis = false;
}

Transform::Transform(vec3 position) {
	this->position = position;
	this->scale = vec3(1.0f, 1.0f, 1.0f);
	this->rotationAxis = vec3(0.0f, 1.0f, 0.0f);
	this->velocity = vec3(0.0f, 0.0f, 0.0f);
	this->rotationAmount = 0.0f;
	this->isRotating = false;
	this->rotateAroundAxis = false;
}


void Transform::Rotate(float amount, vec3 rotationAxis, bool rotateAroundAxis) {
	this->isRotating = true;
	this->rotationAmount += amount;
	this->rotationAxis = rotationAxis;
	this->rotateAroundAxis = rotateAroundAxis;
}