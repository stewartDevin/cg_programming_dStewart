// APP.DataCore.cpp
/////////////////////////////////////////////////////

#include "APP.DataCore.h"

// program id
GLuint DataCore::programID = NULL;
GLuint DataCore::dirtID = NULL;

// screen aspect ratio
float DataCore::aspectRatio = SCREEN_WIDTH / (float)SCREEN_HEIGHT;

// GLFWwindow
GLFWwindow* DataCore::window = NULL;

// deltaTime
float DataCore::deltaTime = 0.0f;

// camera
Camera DataCore::camera = Camera(vec3(0.0f, 0.0f, 3.0f));