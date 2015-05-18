// Main.cpp
////////////////////////////////////////////////////////////////////////

#include "Application.h"
#include "APP\APP.Scene.h"
#include "CORE\CORE.GL_Init.h"

///////////////////////////////////////////////////////////////////////////////
// main
int main() {
	// seed random number generator.
	srand(time(NULL));
	// launch the window, initialize GLEW...
	if (GL_Init::InitWindow() | GL_Init::InitGlew()) {
		return EXIT_WITH_ERROR;
	}

	if (Scene::MainLoop() == EXIT_WITH_ERROR) return EXIT_WITH_ERROR;

	return EXIT_WITH_SUCCESS;
}