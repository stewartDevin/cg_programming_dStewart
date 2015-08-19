// Application.h
///////////////////////////////////////////////////////////////////

#pragma once
// Standard headers...
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <fstream>
#include <string>
#include <time.h>
#include <windows.h>
#include <GL/glew.h>
#include <vector>

#include "GL/GL.h"

#include <GLFW/glfw3.h>
#include <glm.hpp>
#include "gtc/matrix_transform.hpp"
#include "SOIL.h"

#define GLFW_DLL
#define APP_NAME "Devin Stewart -- Application"
#define EXIT_WITH_ERROR -1
#define EXIT_WITH_SUCCESS 0
#define OPEN_GL_VERSION 3
#define ANTIALIASING 4
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800
#define FIELD_OF_VIEW 45.0f
#define Z_NEAR 0.1f
#define Z_FAR 2000.0f
#define GLFW_OK 0
#define MAX_TEXTURES 4

// using namespaces
using namespace std;
using namespace glm;

//void Update();
//void Render();


