// APP.Scene.cpp
//////////////////////////////////////////////////////////////////////////

#include "../Application.h"
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


//void LoadGrid() {
//	// load grid
//	/*float xPos = -2.4f;
//	float yPos = 1.8f;
//	float tileScale = 0.4f;
//	float tileSpacing = 0.0f;*/
//	int xTiles = 16;
//	int yTiles = 16;
//
//	int counter = 0;
//
//	for (int m = 0; m < yTiles; ++m) {
//		for (int n = 0; n < xTiles; ++n) {
//
//			BufferObject bufferObj;
//			bufferObj.vertexBuffer = Load::LoadQuad();
//			bufferObj.uvBuffer = Load::LoadUVs();
//
//			if (counter == 0) {
//				GameObject::CreateObject(
//					vec3(DataCore::xTilePos + (n * (DataCore::tileScale + DataCore::tileSpacing)), DataCore::yTilePos - (m * (DataCore::tileScale + DataCore::tileSpacing)), 0.0f),
//					vec3(DataCore::tileScale, DataCore::tileScale, 1.0f),
//					bufferObj,
//					DataCore::listOfTextures[0]);
//				counter = 1;
//				continue;
//			}
//
//			if (counter == 1) {
//				GameObject::CreateObject(
//					vec3(DataCore::xTilePos + (n * (DataCore::tileScale + DataCore::tileSpacing)), DataCore::yTilePos - (m * (DataCore::tileScale + DataCore::tileSpacing)), 0.0f),
//					vec3(DataCore::tileScale, DataCore::tileScale, 1.0f),
//					bufferObj,
//					DataCore::listOfTextures[1]);
//				counter = 0;
//				continue;
//			}
//
//
//		}
//	}
//
//}

GameObject* gObj = NULL;


void Scene::InitializeScene() {
	if (!Scene::sceneInitialized) {
		/* load an image file directly as a new OpenGL texture */
		//Load::_LoadTexture(&DataCore::grassTexture, "./Assets/Images/grass2.png");

		//Load::_LoadTexture(&DataCore::dirtTexture, "./Assets/Images/dirt.jpg");
		//Load::__LoadTexture("./Assets/Images/grass2.png");
		//Load::__LoadTexture("./Assets/Images/dirt.jpg");

		// load file
		Load::LoadFile(LEVEL_1);
		// Load Grid
		//LoadGrid();
		Load::_LoadTexture(&DataCore::playerTexture, "./Assets/Images/player.png");

		BufferObject bufferObj;
		bufferObj.vertexBuffer = Load::LoadQuad();
		bufferObj.uvBuffer = Load::LoadUVs();
		gObj = GameObject::CreateObject(
			vec3(-2.4f, 1.4f, 0.01f),
			vec3(DataCore::tileScale, DataCore::tileScale, 1.0f),
			bufferObj,
			DataCore::playerTexture
		);

		// init scene variable = true;
		Scene::sceneInitialized = true;
	}
}

vector<GameObject*> Scene::listOfObjects;

void RunControls1(vec3& position, float const& speed) {
	if (Keyboard::Q) {
		position.z -= speed * DataCore::deltaTime;
	}
	if (Keyboard::W) {
		position.y += speed * DataCore::deltaTime;
	}
	if (Keyboard::E) {
		position.z += speed * DataCore::deltaTime;
	}
	if (Keyboard::S) {
		position.y -= speed * DataCore::deltaTime;
	}
	if (Keyboard::A) {
		position.x -= speed * DataCore::deltaTime;
	}
	if (Keyboard::D) {
		position.x += speed * DataCore::deltaTime;
	}
}

void RunControls2(vec3& position, float const& speed) {
	if (Keyboard::LeftArrow) {
		position.x -= speed * DataCore::deltaTime;
	}
	if (Keyboard::UpArrow) {
		position.y += speed * DataCore::deltaTime;
	}
	if (Keyboard::RightArrow) {
		position.x += speed * DataCore::deltaTime;
	}
	if (Keyboard::DownArrow) {
		position.y -= speed * DataCore::deltaTime;
	}
}

void Update() {

	RunControls2(DataCore::camera.transform.position, 2.0f);

	//GameObject* player = Scene::listOfObjects[Scene::listOfObjects.size()-1];
	RunControls1(gObj->transform.position, 1.0f);
	//gObj->transform.scale = vec3(0.6f, 0.6f, 0.6f);

	// update the camera
	DataCore::camera.Update();
	DataCore::camera.Follow(gObj->transform.position, 6.0f);
	// Run Objects
	GameObject::RunAllObjects();

	// Run Pong
	//PongScene::PongMainLoop();
}

int Scene::MainLoop() {
	Scene::InitializeScene();
	do {
		// clear the screen...
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		// get the deltaTime...
		//fprintf(stdout, "Delta Time: %f", getDeltaTime()); 
		DataCore::deltaTime = Utility::getDeltaTime();

		// tell openGL to use our program...
		glUseProgram(DataCore::programID);
		// Run Keyboard Input
		Keyboard::RunKeyboardKeys();
		// update
		Update();
		// swap the screen buffers...
		glfwSwapBuffers(DataCore::window);
		// Run OpenGL's Event Handler...
		glfwPollEvents();

	} while (glfwGetKey(DataCore::window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(DataCore::window) == 0);

	int save_result = SOIL_save_screenshot
		(
		"screenshot.bmp",
		SOIL_SAVE_TYPE_BMP,
		0, 0, 1024, 768
		);

	return EXIT_WITH_SUCCESS;
}