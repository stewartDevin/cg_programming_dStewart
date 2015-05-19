// Pong.Options.cpp
//////////////////////////////////////////////////////////////

#include "Pong.Options.h"

/////////////////////////////////////////////////////////////////////////////////////
// PongGameOptions


vec3 PongGameOptions::paddleScale = vec3(0.1f, 1.0f, 1.0f);
vec3 PongGameOptions::ballScale = vec3(0.1f, 0.1f, 1.0f);

vec3 PongGameOptions::ballPosition = vec3(0.0f, 0.0f, 0.0f);
vec3 PongGameOptions::leftPaddlePosition = vec3(-2.5f, 0.0f, 0.0f);
vec3 PongGameOptions::rightPaddlePosition = vec3(2.5f, 0.0f, 0.0f);
vec3 PongGameOptions::startingPos = vec3(0.0f, 0.0f, 0.0f);
float PongGameOptions::ballVelocity = 2.5f;
vec3 PongGameOptions::startingBallVelocity = vec3(2.0f, 0.0f, 0.0f);
float PongGameOptions::paddleWidth = 5.0f;
float PongGameOptions::gameTimer = 0.0f;
float PongGameOptions::maxPaddleVelocity = 2.0f;
float PongGameOptions::paddleAcceleration = 10.0f;
float PongGameOptions::currentBallBounceStrength = 0.0f;
float PongGameOptions::ballBounceStrengthIncrement = 0.01f;