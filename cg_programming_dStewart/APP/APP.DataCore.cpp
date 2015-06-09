// APP.DataCore.cpp
/////////////////////////////////////////////////////

#include "APP.DataCore.h"

// program id
GLuint DataCore::programID = NULL;

// screen aspect ratio
float DataCore::aspectRatio = SCREEN_WIDTH / (float)SCREEN_HEIGHT;

// GLFWwindow
GLFWwindow* DataCore::window = NULL;

// deltaTime
float DataCore::deltaTime = 0.0f;

// camera
Camera DataCore::camera = Camera(vec3(0.0f, 0.0f, 3.0f));

// list of textures
vector<GLuint> DataCore::listOfTextures;

// textures
GLuint DataCore::dirtTexture = NULL;
GLuint DataCore::grassTexture = NULL;

// amount of tiles
int DataCore::xAmountOfTiles = 0;
int DataCore::yAmountOfTiles = 0;

//tiles

float DataCore::xTilePos = -2.4f;
float DataCore::yTilePos = 1.8f;
float DataCore::tileScale = 0.4f;
float DataCore::tileSpacing = 0.0f;