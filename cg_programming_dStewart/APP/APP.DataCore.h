// APP.DataCore.h
/////////////////////////////////////////////////////////////

#pragma once 

#include "../Application.h"
#include "../CORE/CORE.Camera.h"

static class DataCore {
public:
	static GLuint programID;
	static float aspectRatio;
	static GLFWwindow* window;
	static float deltaTime;
	static int numberOfTextures;
	static Camera camera;

};