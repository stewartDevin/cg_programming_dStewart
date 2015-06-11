// APP.Scene.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "../Application.h"
#include <vector>
#include "../CORE/CORE.GameObject.h"
using namespace std;

#define ASSETS_FOLDER_FILE_PATH "./Assets/"
#define IMAGES_FOLDER_FILE_PATH "./Assets/Images/"
#define LEVELS_FOLDER_FILE_PATH "./Assets/Levels/"

#define LEVEL_0 "Assets/Levels/level_0.txt"
#define LEVEL_1 "Assets/Levels/level_1.txt"

#define ASCII_ZERO 48

#define LOAD_TEXTURE(chr) (chr == 35)
#define LOAD_LEVELDATA(chr) (chr == 40)
#define IS_NUMBER(chr) (chr > 47 && chr < 58)
#define IS_EMPTY_LINE(chr) (chr == 32 || chr == '\0')

///////////////////////////////////////////////////////////////////////////////
// Scene
class Scene {
public:
	static vector<GameObject*> listOfObjects;

	static bool initializedPong;
	static bool sceneInitialized;

	static string loadedFile;
	static string loadedLevel;

	static void InitializeScene();
	
	static int Scene::MainLoop();
};