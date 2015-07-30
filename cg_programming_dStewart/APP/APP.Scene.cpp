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
#include "..\CORE\CORE.Material.h"
#include "..\CORE\CORE.Mesh.h"
#include "..\CORE\CORE.Mouse.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Scene

bool Scene::sceneInitialized = false;

string Scene::loadedFile = "";
string Scene::loadedLevel = "";

vector<GameObject*> Scene::listOfObjects;

GLfloat timer = 0.0f;
GLint timeLoc = NULL;

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



void RunControls1(vec3& position, float const& speed) {
	if (Keyboard::Q) {
		position.z += speed * DataCore::deltaTime;
	}
	if (Keyboard::W) {
		position.y += speed * DataCore::deltaTime;
	}
	if (Keyboard::E) {
		position.z -= speed * DataCore::deltaTime;
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

Material* sceneMaterial = NULL;
Material* bunnyMaterial = NULL;
Mesh* floorMesh = NULL;
Mesh* bunnyMesh = NULL;

void Scene::LoadLevelOne() {
	sceneMaterial = Material::CreateMaterial("./Assets/Images/floorPillarStairs_Diffuse.png");
	bunnyMaterial = Material::CreateMaterial("./Assets/Images/dirt.jpg");

	floorMesh = Mesh::CreateMeshObject("./Assets/Models/floor1.obj", *sceneMaterial, Transform(vec3(0.0f, 0.0f, 0.0f)));
	// floor
	//Mesh::CreateMeshObject("./Assets/Models/floor1.obj", *sceneMaterial, Transform(vec3(0.0f, 0.0f, 0.0f)));
	// stairs
	Mesh::CreateMeshObject("./Assets/Models/stairs1.obj", *sceneMaterial, Transform(vec3(0.0f, 0.0f, 0.0f)));
	bunnyMesh = Mesh::CreateMeshObject("./Assets/Models/bunny.obj", *bunnyMaterial, Transform(vec3(0.0f, 0.0f, 0.0f)));
	//// pillars
	//first row
	Mesh::CreateMeshObject("./Assets/Models/pillar.obj", *sceneMaterial, Transform(vec3(0.0f, 0.0f, 0.0f)));
	Mesh::CreateMeshObject("./Assets/Models/pillar.obj", *sceneMaterial, Transform(vec3(4.0f, 0.0f, 0.0f)));
	Mesh::CreateMeshObject("./Assets/Models/pillar.obj", *sceneMaterial, Transform(vec3(8.0f, 0.0f, 0.0f)));
	//second row
	Mesh::CreateMeshObject("./Assets/Models/pillar.obj", *sceneMaterial, Transform(vec3(0.0f, 0.0f, 5.8f)));
	Mesh::CreateMeshObject("./Assets/Models/pillar.obj", *sceneMaterial, Transform(vec3(4.0f, 0.0f, 5.8f)));
	Mesh::CreateMeshObject("./Assets/Models/pillar.obj", *sceneMaterial, Transform(vec3(8.0f, 0.0f, 5.8f)));
}

void Scene::InitializeScene() {
	if (!Scene::sceneInitialized) {

		// tell openGL to use our program...
		glUseProgram(DataCore::programID);
		// enable the depth test for 3d
		glEnable(GL_DEPTH_TEST);
		// init the mouse
		Mouse::InitMouse();

		Scene::LoadLevelOne();

		timeLoc = glGetUniformLocationARB(DataCore::programID, "timer");

		// init scene variable = true;
		Scene::sceneInitialized = true;
	}
}



void Update() {
	
	// clear the screen...
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// get the deltaTime...
	DataCore::deltaTime = Utility::getDeltaTime();
	//fprintf(stdout, "Delta Time: %f", getDeltaTime()); 
	// update the camera
	DataCore::camera.Update();
	// move with FPS controls
	DataCore::camera.MoveWithFPSControls();
	// Run FPS mouse look
	Mouse::RunFPSMouse();
	// Run Keyboard Input
	Keyboard::RunKeyboardKeys();
	
	bunnyMesh->transform.angle += 1.0f * DataCore::deltaTime;
	
	// Run Objects
	GameObject::RunAllObjects();



	//send the timer to the vertex Shader
	glUniform1fARB(timeLoc, timer);

	timer += 2.0f * DataCore::deltaTime;
}

int Scene::MainLoop() {
	
	Scene::InitializeScene();

	do {
		// Run OpenGL's Event Handler...
		glfwPollEvents();
		// update
		Update();
		// swap the screen buffers...
		glfwSwapBuffers(DataCore::window);

	} while (!Keyboard::Escape && glfwWindowShouldClose(DataCore::window) == 0);

	SOIL_save_screenshot
		(
		"screenshot.bmp",
		SOIL_SAVE_TYPE_BMP,
		0, 0, 1200, 800
		);

	return EXIT_WITH_SUCCESS;
}