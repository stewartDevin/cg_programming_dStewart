// CORE.BufferObject.h
////////////////////////////////////////////////////////////////////
#pragma once

#include "../Application.h"

class BufferObject {
public:
	int index;
	GLuint vertexBuffer;
	GLuint vertexColorBuffer;
	GLuint uvBuffer;
	GLuint vertexNormalBuffer;

	BufferObject::BufferObject();
};
