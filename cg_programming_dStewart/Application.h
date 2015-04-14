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

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#define GLFW_DLL
#define APP_NAME "Devin Stewart -- Application"
#define EXIT_WITH_ERROR -1
#define EXIT_WITH_SUCCESS 0
#define OPEN_GL_VERSION 3
#define ANTIALIASING 4
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define GLFW_OK 0

extern GLFWwindow* window;
extern GLint shaderStatus;
extern bool activeRef;

// using namespaces
using namespace std;
using namespace glm;

//void Update();
//void Render();
