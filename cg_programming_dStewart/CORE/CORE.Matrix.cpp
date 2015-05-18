// CORE.Matrix.cpp
//////////////////////////////////////////////////////////////////////////

#include "CORE.Matrix.h"
#include "../APP/Pong/Pong.Options.h"

///////////////////////////////////////////////////////////////////////////////
// Matrix
Matrix::Matrix() {

}

mat4 Matrix::projectionMatrix = perspective(FIELD_OF_VIEW, PongGameOptions::aspectRatio, Z_NEAR, Z_FAR);
mat4 Matrix::viewMatrix = glm::lookAt(
	vec3(0, 0, 3),		// position
	vec3(0, 0, 0),		// look at
	vec3(0, 1, 0)		// up
	);
GLuint Matrix::MVPMatrixID = NULL;