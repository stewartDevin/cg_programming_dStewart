// Pong.Options.h
//////////////////////////////////////////////////////////////

#pragma once

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
using namespace glm;

///////////////////////////////////////////////////////////////////////////////
// PongGameOptions
static class PongGameOptions {
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

};

