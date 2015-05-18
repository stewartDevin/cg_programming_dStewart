// APP.Scene.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "../Application.h"
#include "../CORE/CORE.Object.h"
#include <vector>
using namespace std;
///////////////////////////////////////////////////////////////////////////////
// Scene
static class Scene {
public:
	static vector<GameObject*> listOfObjects;

	static bool initializedPong;
	
	static int Scene::MainLoop();
};