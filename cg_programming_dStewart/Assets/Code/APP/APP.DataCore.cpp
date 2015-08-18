// APP.DataCore.cpp
/////////////////////////////////////////////////////

#include "APP.DataCore.h"
#include "../CORE/CORE.OBJ_Loader.h"
#include "../CORE/CORE.Mesh.h"

// list of game objects
vector<GameObject*> DataCore::listOfObjects;

// program id
GLuint DataCore::programID = NULL;

// screen aspect ratio
float DataCore::aspectRatio = SCREEN_WIDTH / (float)SCREEN_HEIGHT;

// GLFWwindow
GLFWwindow* DataCore::window = NULL;

// deltaTime
float DataCore::deltaTime = 0.0f;

// camera
Camera DataCore::camera = Camera(vec3(0.0f, 1.0f, 8.0f));

// list of textures
vector<GLuint> DataCore::listOfTextures;

// textures
GLuint DataCore::dirtTexture = NULL;
GLuint DataCore::grassTexture = NULL;
GLuint DataCore::bushTexture = NULL;
GLuint DataCore::playerTexture = NULL;

// amount of tiles
int DataCore::xAmountOfTiles = 0;
int DataCore::yAmountOfTiles = 0;

//tiles

float DataCore::xTilePos = -2.4f;
float DataCore::yTilePos = 1.8f;
float DataCore::tileScale = 0.8f;
float DataCore::tileSpacing = -0.02f;

// playerMesh
Mesh* DataCore::playerMesh = NULL;

void CReceiver::MyHandler1(int nValue) {
	printf("MyHandler1 was called with value %d.\n", nValue);
}

void CReceiver::MyHandler2(int nValue) {
	printf("MyHandler2 was called with value %d.\n", nValue);
}

void CReceiver::hookEvent(CSource* pSource) {
	__hook(&CSource::MyEvent, pSource, &CReceiver::MyHandler1);
	__hook(&CSource::MyEvent, pSource, &CReceiver::MyHandler2);
}

void CReceiver::unhookEvent(CSource* pSource) {
	__unhook(&CSource::MyEvent, pSource, &CReceiver::MyHandler1);
	__unhook(&CSource::MyEvent, pSource, &CReceiver::MyHandler2);
}

// Read our .obj file
//std::vector< glm::vec3 > DataCore::vertices;
//std::vector< glm::vec2 > DataCore::uvs;
//std::vector< glm::vec3 > DataCore::normals; // Won't be used at the moment.
//bool DataCore::res = OBJ_Loader::LoadOBJ("./Assets/Models/pillar.obj", vertices, uvs, normals);