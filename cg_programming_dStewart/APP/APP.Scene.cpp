// APP.Scene.cpp
//////////////////////////////////////////////////////////////////////////

#include "../CORE/CORE.Utility.h"
#include "../CORE/CORE.Keyboard.h"
#include "../CORE/CORE.Matrix.h"
#include "../CORE/CORE.Load.h"
#include "../CORE/CORE.GL_Init.h"
#include "APP.GameOptions.h"
#include "APP.Scene.h"
#include <vector>
#include "Pong\Pong.Scene.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Scene

vector<GameObject*> Scene::listOfObjects;

int Scene::MainLoop() {
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//fprintf(stdout, "Delta Time: %f", getDeltaTime()); 
		GameOptions::deltaTime = Utility::getDeltaTime();

		/*if (!Scene::initializedPong) {
			if (Scene::InitializePong() == EXIT_WITH_ERROR) return EXIT_WITH_ERROR;
			Scene::initializedPong = true;
			}*/

		Keyboard::RunKeyboardKeys();
		Object::RunAllObjects();

		PongScene::PongMainLoop();

		glUseProgram(GameOptions::programID);

		// camera matrix
		Matrix::viewMatrix = glm::lookAt(
			vec3(0, 0, 3),		// position
			vec3(0, 0, 0),		// look at
			vec3(0, 1, 0)		// up
			);

		//Update();
		//Render();
		glfwSwapBuffers(GameOptions::window);
		glfwPollEvents();

	} while (glfwGetKey(GameOptions::window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(GameOptions::window) == 0);

	return EXIT_WITH_SUCCESS;
}