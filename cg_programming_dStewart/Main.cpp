// Main.cpp
////////////////////////////////////////////////////////////////////////

#include "Application.h"
#include "APP\APP.Scene.h"
#include "CORE\CORE.GL_Init.h"
#include "APP\APP.DataCore.h"
#include "CORE\CORE.Load.h"
#include "CORE\CORE.Matrix.h"

///////////////////////////////////////////////////////////////////////////////
// main
int main() {
	// seed random number generator.
	srand(time(NULL));
	// launch the window, initialize GLEW...
	if (GL_Init::InitWindow() | GL_Init::InitGlew()) {
		return EXIT_WITH_ERROR;
	}

	GLuint vertexArrayID = NULL;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	// Create and compile glsl from shaders.
	DataCore::programID = Load::LoadShaders("BasicVertexShader.vertexshader", "BasicFragmentShader.fragmentshader");

	Matrix::MVPMatrixID = glGetUniformLocation(DataCore::programID, "MVP");

	Matrix::projectionMatrix = perspective(FIELD_OF_VIEW, DataCore::aspectRatio, Z_NEAR, Z_FAR);

	if (Scene::MainLoop() == EXIT_WITH_ERROR) return EXIT_WITH_ERROR;

	return EXIT_WITH_SUCCESS;
}