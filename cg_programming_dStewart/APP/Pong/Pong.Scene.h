// Pong.Paddles.h
////////////////////////////////////////////////////////////////////////////

#pragma once
#include "..\..\CORE\CORE.GameObject.h"

static class PongScene {
public:
	static GameObject leftPaddle;
	static GameObject rightPaddle;
	static GameObject ball;

	static float gameTimer;
	static bool isTimerRunning;
	static bool isGameRunning;
	static bool ballVelocityInitialized;
	static bool initializedPong;

	static float leftBound;
	static float rightBound;
	static float topBound;
	static float bottomBound;

	static vec3 DecideStartingBallDirection();
	static void PongScene::RunGameTimer();
	static void PongScene::RunBallConstraints();
	static void PongScene::RunLeftPaddleControls();
	static void PongScene::RunRightPaddleControls();
	static void PongScene::RunPaddleVelocityConstraints();
	static void PongScene::KillLowVelocity();
	static void PongScene::RunPaddleControls();
	static void PongScene::RunLeftPaddleCollision();
	static void PongScene::RunRightPaddleCollision();
	static void PongScene::RunLeftPaddlePositionConstraints();
	static void PongScene::RunRightPaddlePositionConstraints();
	static void PongScene::RunPaddlePositionConstraints();
	static void PongScene::RunPaddleCollision();
	static void PongScene::InitScene();
	static int PongScene::InitializePong();
	static void PongScene::RunBallBehavior();
	static int PongScene::PongMainLoop();

};