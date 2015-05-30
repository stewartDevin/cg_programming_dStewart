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
#include "APP.DataCore.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Scene

bool Scene::sceneInitialized = false;

string Scene::loadedFile = "";
string Scene::loadedLevel = "";

int offset = 0;

void LoadGrid() {
	// load grid
	float xPos = -2.4f;
	float yPos = 1.8f;
	float tileScale = 0.2f;
	float tileSpacing = 0.01f;
	int xTiles = 24;
	int yTiles = 24;

	for (int m = 0; m < yTiles; ++m) {
		for (int n = 0; n < xTiles; ++n) {
			GameObject::CreateObject(
				vec3(xPos + (n * (tileScale + tileSpacing)), yPos - (m * (tileScale + tileSpacing)), 0.0f),
				vec3(tileScale, tileScale, 1.0f),
				Load::LoadColor(vec3(0.2f + n*0.4f, 0.5f + n*0.1f, 1.0f - n*0.4f)),
				Load::LoadQuad());
		}
	}

}

void Scene::InitializeScene() {
	if (!Scene::sceneInitialized) {
		
		// Load Grid
		LoadGrid();

		// load file
		Scene::loadedFile = Load::LoadFile(LEVEL_0);

		// init scene variable = true;
		Scene::sceneInitialized = true;
	}
}

vector<GameObject*> Scene::listOfObjects;

int Scene::MainLoop() {
	do {
		// clear the screen...
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// get the deltaTime...
		//fprintf(stdout, "Delta Time: %f", getDeltaTime()); 
		DataCore::deltaTime = Utility::getDeltaTime();

		// tell openGL to use our program...
		glUseProgram(DataCore::programID);

		// update the camera matrix...
		//Matrix::viewMatrix = glm::lookAt(
		//	vec3(0, 0, 3),		// position
		//	vec3(0, 0, 0),		// look at
		//	vec3(0, 1, 0)		// up
		//	);

		Scene::InitializeScene();
		DataCore::camera.Update();

		// Run Keyboard Input
		Keyboard::RunKeyboardKeys();

		// Run Objects
		GameObject::RunAllObjects();

		// Run Pong
		//PongScene::PongMainLoop();

		// swap the screen buffers...
		glfwSwapBuffers(DataCore::window);
		// Run OpenGL's Event Handler...
		glfwPollEvents();

	} while (glfwGetKey(DataCore::window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(DataCore::window) == 0);

	return EXIT_WITH_SUCCESS;
}