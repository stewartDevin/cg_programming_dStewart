// CORE.GameObject.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "../Application.h"
#include "CORE.Transform.h"
#include "CORE.Camera.h"
#include "CORE.BufferObject.h"

///////////////////////////////////////////////////////////////////////////////
// GameObject
class GameObject {
public:
	Transform transform;
	//GLuint objectID;
	//GLuint colorID;
	mat4 MVPMatrix;
	bool initialized;
	BufferObject bufferObject;

	GameObject::GameObject(vec3 position, vec3 scale, BufferObject bufferObject);

	GameObject::GameObject();

	static GameObject* GameObject::CreateObject(vec3 position, vec3 scale, BufferObject bufferObject);

	static void GameObject::DeleteObject(GameObject* object);

	static void RunAllObjects();

	void DeleteObject();

	void Init();

	void Run(Camera* camera);
};