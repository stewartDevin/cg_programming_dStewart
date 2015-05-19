// APP.DataCore.cpp
/////////////////////////////////////////////////////

#include "APP.DataCore.h"



GLuint DataCore::programID = NULL;

float DataCore::aspectRatio = SCREEN_WIDTH / (float)SCREEN_HEIGHT;

GLFWwindow* DataCore::window = NULL;

float DataCore::deltaTime = 0.0f;

int DataCore:: numberOfTextures = 0;