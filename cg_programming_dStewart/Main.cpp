// Main.cpp
////////////////////////////////////////////////////////////////////////

#include "Application.h"
#include "Main.h"
#include "CORE\CORE.Keyboard.h"
#include "APP\APP.GameOptions.h"
#include "CORE\CORE.GL_Init.h"
#include "CORE\CORE.Utility.h"
#include "CORE\CORE.Transform.h"
#include "CORE\CORE.GameObject.h"
#include "CORE\CORE.Matrix.h"
#include "CORE\CORE.Render.h"
#include "CORE\CORE.Object.h"
#include "CORE\CORE.Load.h"
#include "APP\APP.Scene.h"

///////////////////////////////////////////////////////////////////////////////
// main
int main() {
	srand(time(NULL));
	if (Scene::MainLoop() == EXIT_WITH_ERROR) return EXIT_WITH_ERROR;

	return EXIT_WITH_SUCCESS;
}