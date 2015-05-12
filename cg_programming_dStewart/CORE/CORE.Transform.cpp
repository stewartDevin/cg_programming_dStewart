// CORE.Transform.cpp
//////////////////////////////////////////////////////////////////////////

#include "CORE.Transform.h"

///////////////////////////////////////////////////////////////////////////////
// Transform
Transform::Transform() {
	this->position = vec3(0.0f, 0.0f, 0.0f);
	this->scale = vec3(1.0f, 1.0f, 1.0f);
	this->rotation = vec3(0.0f, 0.0f, 0.0f);
	vec3 velocity = vec3(0.0f, 0.0f, 0.0f);
}

Transform::Transform(vec3 position, vec3 scale, vec3 rotation, vec3 velocity) {
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
	this->velocity = velocity;
}