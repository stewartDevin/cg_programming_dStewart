// APP.DataCore.h
/////////////////////////////////////////////////////////////

#pragma once 

#include "../Application.h"
#include "../CORE/CORE.Camera.h"

class DataCore {
public:
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
};