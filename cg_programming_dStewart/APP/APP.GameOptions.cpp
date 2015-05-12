// APP.GameOptions.cpp
//////////////////////////////////////////////////////////////////////////
#include "APP.GameOptions.h"

/////////////////////////////////////////////////////////////////////////////////////
// GameOptions
float GameOptions::aspectRatio = SCREEN_WIDTH / (float)SCREEN_HEIGHT;
GLuint GameOptions::programID = NULL;
vec3 GameOptions::paddleScale = vec3(0.1f, 1.0f, 1.0f);
vec3 GameOptions::ballScale = vec3(0.1f, 0.1f, 1.0f);
GLFWwindow* GameOptions::window = NULL;
float GameOptions::deltaTime = 0.0f;
vec3 GameOptions::ballPosition = vec3(0.0f, 0.0f, 0.0f);
vec3 GameOptions::leftPaddlePosition = vec3(-2.5f, 0.0f, 0.0f);
vec3 GameOptions::rightPaddlePosition = vec3(2.5f, 0.0f, 0.0f);
vec3 GameOptions::startingPos = vec3(0.0f, 0.0f, 0.0f);
float GameOptions::ballVelocity = 2.5f;
vec3 GameOptions::startingBallVelocity = vec3(2.0f, 0.0f, 0.0f);
float GameOptions::paddleWidth = 5.0f;
float GameOptions::gameTimer = 0.0f;
float GameOptions::maxPaddleVelocity = 2.0f;
float GameOptions::paddleAcceleration = 10.0f;
float GameOptions::currentBallBounceStrength = 0.0f;
float GameOptions::ballBounceStrengthIncrement = 0.01f;