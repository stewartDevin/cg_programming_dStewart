// CORE.GameObject.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "../Application.h"
#include "CORE.Transform.h"
#include "CORE.Camera.h"

///////////////////////////////////////////////////////////////////////////////
// GameObject
class GameObject {
public:
	Transform transform;
	GLuint objectID;
	GLuint colorID;
	mat4 MVPMatrix;
	bool initialized;

	GameObject::GameObject(vec3 position, vec3 scale, GLuint colorID, GLuint objectID);

	GameObject::GameObject();

	static GameObject* GameObject::CreateObject(vec3 position, vec3 scale, GLuint colorID, GLuint objectID);

	static void GameObject::DeleteObject(GameObject* object);

	static void RunAllObjects();

	void DeleteObject();

	void Init();

	void Run(Camera* camera);
};