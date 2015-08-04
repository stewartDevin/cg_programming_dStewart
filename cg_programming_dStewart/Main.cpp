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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLuint vertexArrayID = NULL;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	// Create and compile glsl from shaders.
	//DataCore::programID = Load::LoadShaders("./Assets/Shaders/FlattenTextureVertexShader.vertexshader", "./Assets/Shaders/FlattenTextureFragmentShader.fragmentshader");
	DataCore::programID = Load::LoadShaders("./Assets/Shaders/TextureVertexShader.vertexshader", "./Assets/Shaders/TextureFragmentShader.fragmentshader");
	//DataCore::programID = Load::LoadShaders("./Assets/Shaders/Dance.vertexshader", "./Assets/Shaders/Dance.fragmentshader");
	//DataCore::programID = Load::LoadShaders("./Assets/Shaders/Toon.vertexshader", "./Assets/Shaders/Toon.fragmentshader");
	//DataCore::programID = Load::LoadShaders("./Assets/Shaders/DiffuseTextureVertexShader.vertexshader", "./Assets/Shaders/DiffuseTextureFragmentShader.fragmentshader");

	//// init camera.
	//// link the shaders to the camera.
	//DataCore::camera.MVPMatrixID = glGetUniformLocation(DataCore::programID, "MVP");
	////DataCore::camera.MVPMatrixID = glGetUniformLocation(DataCore::dirtID, "MVP");

	//// init perspective.
	//DataCore::camera.projectionMatrix = perspective(FIELD_OF_VIEW, DataCore::aspectRatio, Z_NEAR, Z_FAR);

	// render lines...
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);

	// run the main loop of the program.
	if (Scene::MainLoop() == EXIT_WITH_ERROR) return EXIT_WITH_ERROR;

	// exit with success.
	return EXIT_WITH_SUCCESS;
}