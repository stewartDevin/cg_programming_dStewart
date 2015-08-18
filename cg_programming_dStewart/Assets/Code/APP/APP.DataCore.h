// APP.DataCore.h
/////////////////////////////////////////////////////////////

#pragma once 

#include "../Application.h"
#include "../CORE/CORE.Camera.h"
#include "../CORE/CORE.Mesh.h"


class DataCore {
public:
	// list of game objects
	static vector<GameObject*> listOfObjects;

	// program id
	static GLuint programID;

	// aspect ratio
	static float aspectRatio;

	//window
	static GLFWwindow* window;

	// deltaTime
	static float deltaTime;

	// camera
	static Camera camera;

	static vector<GLuint> listOfTextures;

	//textures
	static GLuint dirtTexture;
	static GLuint grassTexture;
	static GLuint bushTexture;
	static GLuint playerTexture;

	// amount of tiles
	static int xAmountOfTiles;
	static int yAmountOfTiles;
	static float DataCore::xTilePos;
	static float DataCore::yTilePos;
	static float DataCore::tileScale;
	static float DataCore::tileSpacing;

	// Read our .obj file
	static std::vector< glm::vec3 > vertices;
	static std::vector< glm::vec2 > uvs;
	static std::vector< glm::vec3 > normals; // Won't be used at the moment.
	static bool res;

	//playerMesh
	static Mesh* playerMesh;
};

class CSource {
public:
	__event void MyEvent(int nValue);
};


class CReceiver {
public:
	void MyHandler1(int nValue);
	
	void MyHandler2(int nValue);
	
	void hookEvent(CSource* pSource);
	
	void unhookEvent(CSource* pSource);
};