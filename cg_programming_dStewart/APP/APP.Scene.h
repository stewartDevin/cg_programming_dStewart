// APP.Scene.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "../Application.h"
#include "../CORE/CORE.Object.h"
///////////////////////////////////////////////////////////////////////////////
// Scene
static class Scene {
public:
	static bool initializedPong;
	static Object leftPaddle;
	static Object rightPaddle;
	static Object ball;

	static float gameTimer;
	static bool isTimerRunning;
	static bool isGameRunning;
	static bool ballVelocityInitialized;

	static float leftBound;
	static float rightBound;
	static float topBound;
	static float bottomBound;
	
	Scene::Scene();

	static vec3 DecideStartingBallDirection();
	static void Scene::RunGameTimer();
	static void Scene::RunBallConstraints();
	static void Scene::RunLeftPaddleControls();
	static void Scene::RunRightPaddleControls();
	static void Scene::RunPaddleVelocityConstraints();
	static void Scene::KillLowVelocity();
	static void Scene::RunPaddleControls();
	static void Scene::RunLeftPaddleCollision();
	static void Scene::RunRightPaddleCollision();
	static void Scene::RunLeftPaddlePositionConstraints();
	static void Scene::RunRightPaddlePositionConstraints();
	static void Scene::RunPaddlePositionConstraints();
	static void Scene::RunPaddleCollision();
	static void Scene::InitScene();
	static int Scene::InitializePong();
	static void Scene::RunBallBehavior();
	static int Scene::MainLoop();
};