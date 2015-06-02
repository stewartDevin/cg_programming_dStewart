// CORE.GameObject.cpp
//////////////////////////////////////////////////////////////////////////

#include "CORE.GameObject.h"
#include "..\APP\APP.Scene.h"
#include "CORE.Camera.h"
#include "CORE.Render.h"
#include "..\APP\APP.DataCore.h"

GameObject::GameObject(vec3 position, vec3 scale, BufferObject bufferObject) {
	this->transform.position = position;
	this->transform.scale = scale;
	this->bufferObject = bufferObject;
	//this->objectID = objectID;
	//this->colorID = colorID;
	this->initialized = false;
}

GameObject::GameObject() {
	//this->objectID = NULL;
	//this->colorID = NULL;
	this->bufferObject = BufferObject();
	this->initialized = false;
}

GameObject* GameObject::CreateObject(vec3 position, vec3 scale, BufferObject bufferObject) {
	GameObject* object = new GameObject(position, scale, bufferObject);
	Scene::listOfObjects.push_back(object);
	//Scene::listOfObjects[Scene::sizeOfListOfObjects] = object;
	//Scene::sizeOfListOfObjects++;
	return object;
}

void GameObject::DeleteObject(GameObject* object) {
	delete(object);
}
void GameObject::DeleteObject() {
	delete(this);
}

void GameObject::Init() {

}

void GameObject::Run(Camera* camera) {
	if (!this->initialized) {
		this->Init();
		this->initialized = true;
	}

	//this->MVPMatrix = camera->projectionMatrix * camera->viewMatrix * Render::RenderQuad(this->objectID, this->transform.position, this->colorID, this->transform.scale);
	this->MVPMatrix = camera->projectionMatrix * camera->viewMatrix * Render::RenderQuad(&this->bufferObject, this->transform.position, this->transform.scale);
	glUniformMatrix4fv(camera->MVPMatrixID, 1, GL_FALSE, &this->MVPMatrix[0][0]);

	this->transform.position += this->transform.velocity * DataCore::deltaTime;
}

void GameObject::RunAllObjects() {
	for (unsigned int n = 0; n < Scene::listOfObjects.size(); n++) {
		GameObject* obj = Scene::listOfObjects[n];
		obj->Run(&DataCore::camera);
	}
}