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
	mat4 MVPMatrix;
	mat4 positionMatrix;
	bool initialized;
	BufferObject bufferObject;
	GLuint textureID;
	GLuint MVP_MatrixID;
	int numIndices;
	

	GameObject::GameObject(vec3 position, vec3 scale, BufferObject bufferObject, GLuint textureID);

	GameObject::GameObject();

	static GameObject* GameObject::CreateObject(vec3 position, vec3 scale, BufferObject bufferObject, GLuint textureID);

	//static GameObject* GameObject::CreateMeshOBJObject(vec3 position, vec3 scale, BufferObject bufferObject, GLuint textureID);

	static void GameObject::DeleteObject(GameObject* object);

	static void RunAllObjects();

	static void GameObject::DeleteAllObjects();

	void DeleteObject();

	void Init();

	void virtual Run(Camera* camera);

	~GameObject();
};