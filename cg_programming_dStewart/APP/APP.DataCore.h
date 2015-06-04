// APP.DataCore.h
/////////////////////////////////////////////////////////////

#pragma once 

#include "../Application.h"
#include "../CORE/CORE.Camera.h"

class DataCore {
public:
	static int numberOfTextures;
	static GLuint programID;
	//static GLuint dirtID;

	// aspect ratio
	static float aspectRatio;

	//window
	static GLFWwindow* window;

	// deltaTime
	static float deltaTime;

	// camera
	static Camera camera;

	//textures
	static GLuint dirtTexture;
	static GLuint grassTexture;
};