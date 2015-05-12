// CORE.Matrix.cpp
//////////////////////////////////////////////////////////////////////////

#include "CORE.Matrix.h"
#include "../APP/APP.GameOptions.h"

///////////////////////////////////////////////////////////////////////////////
// Matrix
Matrix::Matrix() {

}

mat4 Matrix::projectionMatrix = perspective(FIELD_OF_VIEW, GameOptions::aspectRatio, Z_NEAR, Z_FAR);
mat4 Matrix::viewMatrix = glm::lookAt(
	vec3(0, 0, 3),		// position
	vec3(0, 0, 0),		// look at
	vec3(0, 1, 0)		// up
	);
GLuint Matrix::MVPMatrixID = NULL;