// CORE.Matrix.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "../Application.h"

///////////////////////////////////////////////////////////////////////////////
// Matrix
static class Matrix {
public:
	static mat4 projectionMatrix;
	static mat4 viewMatrix;
	static GLuint MVPMatrixID;

	Matrix::Matrix();
};