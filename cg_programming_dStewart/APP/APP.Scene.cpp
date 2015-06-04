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


void LoadGrid() {
	// load grid
	float xPos = -2.4f;
	float yPos = 1.8f;
	float tileScale = 0.4f;
	float tileSpacing = 0.0f;
	int xTiles = 16;
	int yTiles = 16;

	int counter = 0;

	for (int m = 0; m < yTiles; ++m) {
		for (int n = 0; n < xTiles; ++n) {

			BufferObject bufferObj;
			bufferObj.vertexBuffer = Load::LoadQuad();
			bufferObj.uvBuffer = Load::LoadUVs();

			if(counter == 0) {
				GameObject::CreateObject(
				vec3(xPos + (n * (tileScale + tileSpacing)), yPos - (m * (tileScale + tileSpacing)), 0.0f),
				vec3(tileScale, tileScale, 1.0f),
				bufferObj,
				DataCore::grassTexture);
				counter = 1;
				continue;
			}

			if(counter == 1) {
				GameObject::CreateObject(
				vec3(xPos + (n * (tileScale + tileSpacing)), yPos - (m * (tileScale + tileSpacing)), 0.0f),
				vec3(tileScale, tileScale, 1.0f),
				bufferObj,
				DataCore::dirtTexture);
				counter = 0;
				continue;
			}

			
		}
	}

}

void _LoadTexture(GLuint* texture, char* path){
	if(texture == NULL) return;
	GLuint n = SOIL_load_OGL_texture(path,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA
		);
	*texture = n;
	if (*texture == NULL){
		printf("[Texture loader] \"%s\" failed to load!\n", path);
	}
}


void Scene::InitializeScene() {
	if (!Scene::sceneInitialized) {
		// load file
		//Scene::loadedFile = Load::LoadFile(LEVEL_0);
		Load::LoadFile(LEVEL_0);

		/* load an image file directly as a new OpenGL texture */
		//_LoadTexture(&grassTexture, "./Assets/Images/grass.jpg");
		_LoadTexture(&DataCore::grassTexture, "./Assets/Images/grass2.png");
		
		_LoadTexture(&DataCore::dirtTexture, "./Assets/Images/dirt.jpg");

		// Load Grid
		LoadGrid();

		// init scene variable = true;
		Scene::sceneInitialized = true;
	}
}

vector<GameObject*> Scene::listOfObjects;

void RunControls(vec3& position, float const& speed) {
	if (Keyboard::W || Keyboard::UpArrow) {
		position.z -= speed * DataCore::deltaTime;
	}
	if (Keyboard::A || Keyboard::LeftArrow) {
		position.y += speed * DataCore::deltaTime;
	}
	if (Keyboard::S || Keyboard::DownArrow) {
		position.z += speed * DataCore::deltaTime;
	}
	if (Keyboard::D || Keyboard::RightArrow) {
		position.y -= speed * DataCore::deltaTime;
	}
	if (Keyboard::Q) {
		position.x -= speed * DataCore::deltaTime;
	}
	if (Keyboard::E) {
		position.x += speed * DataCore::deltaTime;
	}
}

void Update() {
	
	RunControls(DataCore::camera.transform.position, 1.0f);
	// update the camera
	DataCore::camera.Update();
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