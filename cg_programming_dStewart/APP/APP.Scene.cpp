// APP.Scene.cpp
//////////////////////////////////////////////////////////////////////////

#include "../CORE/CORE.Utility.h"
#include "../CORE/CORE.Keyboard.h"
#include "../CORE/CORE.Matrix.h"
#include "../CORE/CORE.Load.h"
#include "../CORE/CORE.GL_Init.h"
#include "APP.Scene.h"
#include <vector>
#include "Pong\Pong.Options.h"
#include "Pong\Pong.Scene.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Scene

vector<GameObject*> Scene::listOfObjects;

int Scene::MainLoop() {
	do {
		// clear the screen...
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// get the deltaTime...
		//fprintf(stdout, "Delta Time: %f", getDeltaTime()); 
		PongGameOptions::deltaTime = Utility::getDeltaTime();

		// tell openGL to use our program...
		glUseProgram(PongGameOptions::programID);

		// update the camera matrix...
		Matrix::viewMatrix = glm::lookAt(
			vec3(0, 0, 3),		// position
			vec3(0, 0, 0),		// look at
			vec3(0, 1, 0)		// up
			);

		// Run Keyboard Input
		Keyboard::RunKeyboardKeys();
		
		// Run Objects
		Object::RunAllObjects();

		// Run Pong
		//PongScene::PongMainLoop();

		// swap the screen buffers...
		glfwSwapBuffers(PongGameOptions::window);
		// Run OpenGL's Event Handler...
		glfwPollEvents();

	} while (glfwGetKey(PongGameOptions::window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(PongGameOptions::window) == 0);

	return EXIT_WITH_SUCCESS;
}