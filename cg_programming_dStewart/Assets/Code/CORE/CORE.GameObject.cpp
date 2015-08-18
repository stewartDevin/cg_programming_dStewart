// CORE.GameObject.cpp
//////////////////////////////////////////////////////////////////////////

#include "CORE.GameObject.h"
#include "..\APP\APP.Scene.h"
#include "CORE.Camera.h"
#include "CORE.Render.h"
#include "..\APP\APP.DataCore.h"

GameObject::~GameObject() {

}

GameObject::GameObject(vec3 position, vec3 scale, BufferObject bufferObject, GLuint textureID) {
	this->transform.position = position;
	this->transform.scale = scale;
	this->bufferObject = bufferObject;
	this->textureID = textureID;
	//this->objectID = objectID;
	//this->colorID = colorID;
	this->initialized = false;
	this->numIndices = 0;
	this->positionMatrix = mat4(1.0f);
	this->MVP_MatrixID = NULL;
}

GameObject::GameObject() {
	//this->objectID = NULL;
	//this->colorID = NULL;
	this->textureID = NULL;
	this->bufferObject = BufferObject();
	this->initialized = false;
	this->numIndices = 0;
	this->positionMatrix = mat4(1.0f);
	this->MVP_MatrixID = NULL;
}

GameObject* GameObject::CreateObject(vec3 position, vec3 scale, BufferObject bufferObject, GLuint textureID) {
	GameObject* object = new GameObject(position, scale, bufferObject, textureID);
	DataCore::listOfObjects.push_back(object);
	//Scene::listOfObjects[Scene::sizeOfListOfObjects] = object;
	//Scene::sizeOfListOfObjects++;
	return object;
}

//GameObject* GameObject::CreateMeshOBJObject(vec3 position, vec3 scale, BufferObject bufferObject, GLuint textureID) {
//	GameObject* object = new GameObject(position, scale, bufferObject, textureID);
//	Scene::listOfObjects.push_back(object);
//
//	return object;
//}

// when calling this, remember to null out pointers.
void GameObject::DeleteObject(GameObject* object) {
	if (object == nullptr) return;
	for (int n = DataCore::listOfObjects.size() - 1; n > -1; n--) {
		GameObject* obj = DataCore::listOfObjects[n];
		if (obj == object) {
			DataCore::listOfObjects.erase(DataCore::listOfObjects.begin() + n);
			delete object;
			object = nullptr;
			return;
		}
	}
}

void GameObject::DeleteObject() {
	for (int n = DataCore::listOfObjects.size() - 1; n > -1; n--) {
		GameObject* obj = DataCore::listOfObjects[n];
		if (obj == this) {
			DataCore::listOfObjects.erase(DataCore::listOfObjects.begin() + n);
			delete this;
			return;
		}
	}
}

void GameObject::Init() {

}

void GameObject::Run(Camera* camera) {
//	if (!this->initialized) {
//		this->Init();
//		this->initialized = true;
//	}
//
////	this->MVPMatrix = camera->projectionMatrix * camera->viewMatrix * Render::RenderQuad(&this->bufferObject, this->transform.position, this->transform.scale, this->textureID);
//	glUniformMatrix4fv(camera->MVPMatrixID, 1, GL_FALSE, &this->MVPMatrix[0][0]);
//
//	this->transform.position += this->transform.velocity * DataCore::deltaTime;
//	this->transform.angle += this->transform.rotationSpeed * DataCore::deltaTime;
}

void GameObject::RunAllObjects() {
	for (int n = DataCore::listOfObjects.size() - 1; n > -1; n--) {
		GameObject* obj = DataCore::listOfObjects[n];
		obj->Run(&DataCore::camera);
	}
}

void GameObject::DeleteAllObjects() {
	for (int n = DataCore::listOfObjects.size() - 1; n > -1; n--) {
		GameObject* obj = DataCore::listOfObjects[n];
		obj->DeleteObject();
	}
	DataCore::listOfObjects.clear();
}