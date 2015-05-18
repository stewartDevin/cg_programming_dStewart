// Main.cpp
////////////////////////////////////////////////////////////////////////

#include "Application.h"
#include "APP\APP.Scene.h"

///////////////////////////////////////////////////////////////////////////////
// main
int main() {
	// seed random number generator.
	srand(time(NULL));
	if (Scene::MainLoop() == EXIT_WITH_ERROR) return EXIT_WITH_ERROR;

	return EXIT_WITH_SUCCESS;
}