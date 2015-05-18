// CORE.Object.cpp
//////////////////////////////////////////////////////////////////////////

#include "CORE.Object.h"
#include "CORE.Matrix.h"
#include "CORE.Render.h"
#include "../APP/APP.GameOptions.h"
#include "../APP/APP.Scene.h"

///////////////////////////////////////////////////////////////////////////////
// Object

Object::Object(vec3 position, vec3 scale, GLuint colorID, GLuint objectID) {
	this->transform.position = position;
	this->transform.scale = scale;
	this->objectID = objectID;
	this->colorID = colorID;
	this->initialized = false;
}

Object::Object() {
	this->objectID = NULL;
	this->colorID = NULL;
	this->initialized = false;
}

Object* Object::CreateObject(vec3 position, vec3 scale, GLuint colorID, GLuint objectID) {
	Object* object = new Object(position, scale, colorID, objectID);
	Scene::listOfObjects.push_back(object);
	//Scene::listOfObjects[Scene::sizeOfListOfObjects] = object;
	//Scene::sizeOfListOfObjects++;
	return object;
}

void Object::DeleteObject(Object* object) {
	delete(object);
}
void Object::DeleteObject() {
	delete(this);
}

void Object::Init() {

}

void Object::Run() {
	if (!this->initialized) {
		this->Init();
		this->initialized = true;
	}

	this->MVPMatrix = Matrix::projectionMatrix * Matrix::viewMatrix * Render::RenderQuad(this->objectID, this->transform.position, this->colorID, this->transform.scale);
	glUniformMatrix4fv(Matrix::MVPMatrixID, 1, GL_FALSE, &this->MVPMatrix[0][0]);

	this->transform.position += this->transform.velocity * GameOptions::deltaTime;
}

void Object::RunAllObjects() {
	for(int n = 0; n < Scene::listOfObjects.size(); n++) {
		GameObject* obj = Scene::listOfObjects[n];
		obj->Run();
	}
}