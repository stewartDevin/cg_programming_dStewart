// CORE.GameObject.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "../Application.h"
#include "CORE.Transform.h"

///////////////////////////////////////////////////////////////////////////////
// GameObject
class GameObject {
public:
	Transform transform;
	GLuint objectID;
	GLuint colorID;
	mat4 MVPMatrix;
	bool initialized;

	GameObject::GameObject() {

	}

	virtual void Init() = 0;
	virtual void Run() = 0;
};