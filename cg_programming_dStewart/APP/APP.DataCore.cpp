// APP.DataCore.cpp
/////////////////////////////////////////////////////

#include "APP.DataCore.h"



GLuint DataCore::programID = NULL;

float DataCore::aspectRatio = SCREEN_WIDTH / (float)SCREEN_HEIGHT;

GLFWwindow* DataCore::window = NULL;

float DataCore::deltaTime = 0.0f;

int DataCore::numberOfTextures = 0;

Camera DataCore::camera = Camera(vec3(0.0f, 0.0f, 3.0f));