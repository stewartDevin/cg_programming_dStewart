// Main.cpp
////////////////////////////////////////////////////////////////////////

#include "Application.h"
#include "Assets\Code\APP\APP.Scene.h"
#include "Assets\Code\CORE\CORE.GL_Init.h"
#include "Assets\Code\APP\APP.DataCore.h"
#include "Assets\Code\CORE\CORE.Load.h"
#include "Assets\Code\CORE\CORE.Matrix.h"

///////////////////////////////////////////////////////////////////////////////
// main
int main() {
	// seed random number generator.
	srand(time(NULL));
	// launch the window, initialize GLEW...
	if (GL_Init::InitWindow() | GL_Init::InitGlew()) {
		return EXIT_WITH_ERROR;
	}

	// run the main loop of the program.
	if (Scene::MainLoop() == EXIT_WITH_ERROR) return EXIT_WITH_ERROR;

	// exit with success.
	return EXIT_WITH_SUCCESS;
}