// APP.DataCore.h
/////////////////////////////////////////////////////////////

#pragma once 

#include "../Application.h"
#include "../CORE/CORE.Camera.h"

static class DataCore {
public:
	static int numberOfTextures;
	static GLuint programID;
	//static GLuint dirtID;

	static float aspectRatio;

	static GLFWwindow* window;

	static float deltaTime;

	static Camera camera;
};