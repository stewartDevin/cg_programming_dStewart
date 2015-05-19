// APP.Scene.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "../Application.h"
#include "../CORE/CORE.Object.h"
#include <vector>
using namespace std;

#define LEVEL_0 "Assets/Levels/level_0.txt"

///////////////////////////////////////////////////////////////////////////////
// Scene
static class Scene {
public:
	static vector<GameObject*> listOfObjects;

	static bool initializedPong;
	static bool sceneInitialized;

	static string loadedFile;
	static string loadedLevel;

	

	static void InitializeScene();
	
	static int Scene::MainLoop();
};