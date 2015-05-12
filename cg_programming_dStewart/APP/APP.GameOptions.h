// APP.GameOptions.h
//////////////////////////////////////////////////////////////////////////

#pragma once

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
using namespace glm;

///////////////////////////////////////////////////////////////////////////////
// GameOptions
static class GameOptions {
public:
	static float aspectRatio;
	static GLuint programID;
	static vec3 paddleScale;
	static vec3 ballScale;
	static GLFWwindow* window;
	static float deltaTime;
	static vec3 ballPosition;
	static vec3 leftPaddlePosition;
	static vec3 rightPaddlePosition;
	static vec3 startingPos;
	static float ballVelocity;
	static vec3 startingBallVelocity;
	static float paddleWidth;
	static float gameTimer;
	static float currentBallBounceStrength;
	static float ballBounceStrengthIncrement;

	static float maxPaddleVelocity;
	static float paddleAcceleration;

	GameOptions::GameOptions() {
		GameOptions::aspectRatio = SCREEN_WIDTH / (float)SCREEN_HEIGHT;
		//this->programID = glCreateProgram();
		GameOptions::paddleScale = vec3(0.1f, 1.0f, 1.0f);
		GameOptions::ballScale = vec3(0.1f, 0.1f, 1.0f);

		GameOptions::window = NULL;
		GameOptions::deltaTime = 0.0f;
		GameOptions::ballPosition = vec3(0.0f, 0.0f, 0.0f);
		GameOptions::leftPaddlePosition = vec3(-2.5f, 0.0f, 0.0f);
		GameOptions::rightPaddlePosition = vec3(2.5f, 0.0f, 0.0f);

		GameOptions::startingPos = vec3(0.0f, 0.0f, 0.0f);
		GameOptions::ballVelocity = 2.5f;
		GameOptions::startingBallVelocity = vec3(2.0f, 0.0f, 0.0f);
		GameOptions::paddleWidth = 5.0f;

		GameOptions::gameTimer = 0.0f;

		GameOptions::maxPaddleVelocity = 2.0f;
		GameOptions::paddleAcceleration = 10.0f;
		GameOptions::currentBallBounceStrength = 0.0f;
		GameOptions::ballBounceStrengthIncrement = 0.01f;
	}

};