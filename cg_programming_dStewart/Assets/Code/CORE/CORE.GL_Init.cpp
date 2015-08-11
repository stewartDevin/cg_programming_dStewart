// CORE.GL_Init.cpp
//////////////////////////////////////////////////////////////////////////

#include "CORE.GL_Init.h"
#include "../APP/Pong/Pong.Options.h"
#include "../Application.h"
#include "../APP/APP.DataCore.h"

///////////////////////////////////////////////////////////////////////////////
// GL_Init
int GL_Init::InitGlew() {
	glfwMakeContextCurrent(DataCore::window); // Initialize GLEW
	glewExperimental = true; // has to do with core profile. 
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW.");
		return EXIT_WITH_ERROR;
	}

	return EXIT_WITH_SUCCESS;
}

int GL_Init::InitWindow() {
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW.");
		return EXIT_WITH_ERROR;
	}

	glfwWindowHint(GLFW_SAMPLES, ANTIALIASING);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPEN_GL_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPEN_GL_VERSION);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // get mac up and running.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // we don't want the old openGL, gives the new one.
	glfwSwapInterval(1);

	DataCore::window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME, NULL, NULL);

	if (DataCore::window == NULL) {
		fprintf(stderr, "Failed to initialize window.");
		glfwTerminate();
		return EXIT_WITH_ERROR;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(DataCore::window, GLFW_STICKY_KEYS, GL_TRUE);
	// 
	glDepthFunc(GL_LESS);
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_BLEND );
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
	//glEnable( GL_COLOR_MATERIAL );
	//glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glBlendEquation( GL_FUNC_ADD );
	

	return EXIT_WITH_SUCCESS;
}