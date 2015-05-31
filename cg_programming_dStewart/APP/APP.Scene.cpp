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
#include "SOIL.h"
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

void loadTexture(GLuint* texture, char* path){
	*texture = SOIL_load_OGL_texture(path,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA
		);
	if (*texture == NULL){
		printf("[Texture loader] \"%s\" failed to load!\n", path);
	}
}

void drawTexturedRect(int x, int y, int w, int h, GLuint texture){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	glBegin(GL_QUADS);
	glColor3f(255, 255, 255);
	glTexCoord2f(0, 0);
	glVertex2f(x, y);
	glTexCoord2f(1, 0);
	glVertex2f(x + w, y);
	glTexCoord2f(0, 1);
	glVertex2f(x, y + h);
	glTexCoord2f(1, 1);
	glVertex2f(x + w, y + h);
	glTexCoord2f(0, 1);
	glVertex2f(x, y + h);
	glEnd();
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}


GLuint texture1 = NULL;
void Scene::InitializeScene() {
	if (!Scene::sceneInitialized) {
		
		// Load Grid
		LoadGrid();

		// load file
		Scene::loadedFile = Load::LoadFile(LEVEL_0);
		
		
		/* load an image file directly as a new OpenGL texture */
		loadTexture(&texture1, "Assets/Images/grass.png");

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

		// Run Keyboard Input
		Keyboard::RunKeyboardKeys();

		Scene::InitializeScene();

		DataCore::camera.Update();
		// Run Objects
		GameObject::RunAllObjects();
		drawTexturedRect(25, 25, 256, 256, texture1);

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