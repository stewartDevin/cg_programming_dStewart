// CORE.BufferObject.cpp
//////////////////////////////////////////////////////////////

#include "CORE.BufferObject.h"

BufferObject::BufferObject() {
	this->index = 0;
	this->vertexBuffer = NULL;
	this->vertexColorBuffer = NULL;
	this->uvBuffer = NULL;
	this->vertexNormalBuffer = NULL;
}