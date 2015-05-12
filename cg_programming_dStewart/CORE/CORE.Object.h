// CORE.Object.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "../Application.h"
#include "CORE.GameObject.h"

///////////////////////////////////////////////////////////////////////////////
// Object
class Object : public GameObject {
public:

	Object::Object(vec3 position, vec3 scale, GLuint colorID, GLuint objectID);

	Object::Object();

	static Object* Object::CreateObject(vec3 position, vec3 scale, GLuint colorID, GLuint objectID);

	static void Object::DeleteObject(Object* object);

	void DeleteObject();

	void Init();

	void Run();
};