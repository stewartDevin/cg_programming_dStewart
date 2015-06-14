// Pong.Paddles.cpp
////////////////////////////////////////////////////////////////////////////

#include "Pong.Scene.h"
#include "../CORE/CORE.Utility.h"
#include "../CORE/CORE.Keyboard.h"
#include "../CORE/CORE.Matrix.h"
#include "../CORE/CORE.Load.h"
#include "../CORE/CORE.GL_Init.h"
#include "../Pong/Pong.Options.h"
#include "../APP.DataCore.h"
#include "../../CORE/CORE.BufferObject.h"
#include <vector>
using namespace std;

bool PongScene::initializedPong = false;
GameObject PongScene::leftPaddle;
GameObject PongScene::rightPaddle;
GameObject PongScene::ball;

float PongScene::gameTimer = 0.0f;
bool PongScene::isTimerRunning = true;
bool PongScene::isGameRunning = false;
bool PongScene::ballVelocityInitialized = false;

float PongScene::leftBound = -2.6f;
float PongScene::rightBound = 2.6f;
float PongScene::topBound = 1.9f;
float PongScene::bottomBound = -1.9f;

vec3 PongScene::DecideStartingBallDirection() {
	int randInt = Utility::GetRandomInt(1, 2);
	if (randInt == 1) {
		return vec3(-PongGameOptions::ballVelocity, 0.0f, 0.0f);
	}
	else {
		return vec3(PongGameOptions::ballVelocity, 0.0f, 0.0f);
	}
}

void PongScene::RunGameTimer() {
	if (PongScene::isTimerRunning) PongScene::gameTimer += 1.0f * DataCore::deltaTime;

	if (PongScene::gameTimer > 2.0f) {
		PongScene::gameTimer = 0.0f;
		PongScene::isTimerRunning = false;
		PongScene::isGameRunning = true;
		PongScene::ballVelocityInitialized = false;
	}
}

void PongScene::RunBallConstraints() {

	if (PongScene::ball.transform.position.x <= PongScene::leftBound) {
		PongScene::ball.transform.position.x = PongScene::leftBound;
		PongScene::isGameRunning = false;
		PongScene::isTimerRunning = true;
		//PongScene::ball.transform.velocity = Utility::CalculateReflectionVector(PongScene::ball.transform.velocity, vec3(1.0f, 0.0f, 0.0f));
	}
	if (PongScene::ball.transform.position.x >= PongScene::rightBound) {
		PongScene::ball.transform.position.x = PongScene::rightBound;
		PongScene::isGameRunning = false;
		PongScene::isTimerRunning = true;
		//PongScene::ball.transform.velocity = Utility::CalculateReflectionVector(PongScene::ball.transform.velocity, vec3(-1.0f, 0.0f, 0.0f));
	}
	if (PongScene::ball.transform.position.y >= PongScene::topBound) {
		PongScene::ball.transform.position.y = PongScene::topBound;
		PongScene::ball.transform.velocity = Utility::CalculateReflectionVector(PongScene::ball.transform.velocity, vec3(0.0f, -1.0f, 0.0f));

	}
	if (PongScene::ball.transform.position.y <= PongScene::bottomBound) {
		PongScene::ball.transform.position.y = PongScene::bottomBound;
		PongScene::ball.transform.velocity = Utility::CalculateReflectionVector(PongScene::ball.transform.velocity, vec3(0.0f, 1.0f, 0.0f));

	}
}

void PongScene::RunLeftPaddleControls() {
	if (Keyboard::W) {
		PongScene::leftPaddle.transform.velocity.y += PongGameOptions::paddleAcceleration * DataCore::deltaTime;
	}
	else {
		if (PongScene::leftPaddle.transform.velocity.y > 0.0f) {
			PongScene::leftPaddle.transform.velocity.y -= PongGameOptions::paddleAcceleration * DataCore::deltaTime;
		}
	}

	if (Keyboard::S) {
		PongScene::leftPaddle.transform.velocity.y -= PongGameOptions::paddleAcceleration * DataCore::deltaTime;
	}
	else {
		if (PongScene::leftPaddle.transform.velocity.y < 0.0f) {
			PongScene::leftPaddle.transform.velocity.y += PongGameOptions::paddleAcceleration * DataCore::deltaTime;
		}
	}
}

void PongScene::RunRightPaddleControls() {
	if (Keyboard::UpArrow) {
		PongScene::rightPaddle.transform.velocity.y += PongGameOptions::paddleAcceleration * DataCore::deltaTime;
	}
	else {
		if (PongScene::rightPaddle.transform.velocity.y > 0.0f) {
			PongScene::rightPaddle.transform.velocity.y -= PongGameOptions::paddleAcceleration * DataCore::deltaTime;
		}
	}

	if (Keyboard::DownArrow) {
		PongScene::rightPaddle.transform.velocity.y -= PongGameOptions::paddleAcceleration * DataCore::deltaTime;
	}
	else {
		if (PongScene::rightPaddle.transform.velocity.y < 0.0f) {
			PongScene::rightPaddle.transform.velocity.y += PongGameOptions::paddleAcceleration * DataCore::deltaTime;
		}
	}
}

void PongScene::RunPaddleVelocityConstraints() {
	// left
	if (PongScene::leftPaddle.transform.velocity.y >= PongGameOptions::maxPaddleVelocity) {
		PongScene::leftPaddle.transform.velocity.y = PongGameOptions::maxPaddleVelocity;
	}
	if (PongScene::leftPaddle.transform.velocity.y <= -PongGameOptions::maxPaddleVelocity) {
		PongScene::leftPaddle.transform.velocity.y = -PongGameOptions::maxPaddleVelocity;
	}

	// right
	if (PongScene::rightPaddle.transform.velocity.y >= PongGameOptions::maxPaddleVelocity) {
		PongScene::rightPaddle.transform.velocity.y = PongGameOptions::maxPaddleVelocity;
	}
	if (PongScene::rightPaddle.transform.velocity.y <= -PongGameOptions::maxPaddleVelocity) {
		PongScene::rightPaddle.transform.velocity.y = -PongGameOptions::maxPaddleVelocity;
	}
}

void PongScene::KillLowVelocity() {
	float tolerance = 0.1f;
	if ((!Keyboard::W && !Keyboard::S) && (PongScene::leftPaddle.transform.velocity.y <= tolerance && PongScene::leftPaddle.transform.velocity.y > 0.0f)) {
		PongScene::leftPaddle.transform.velocity.y = 0.0f;
	}
	if ((!Keyboard::W && !Keyboard::S) && (PongScene::leftPaddle.transform.velocity.y >= -tolerance && PongScene::leftPaddle.transform.velocity.y < 0.0f)) {
		PongScene::leftPaddle.transform.velocity.y = 0.0f;
	}

	if ((!Keyboard::UpArrow && !Keyboard::DownArrow) && (PongScene::rightPaddle.transform.velocity.y <= tolerance && PongScene::rightPaddle.transform.velocity.y > 0.0f)) {
		PongScene::rightPaddle.transform.velocity.y = 0.0f;
	}
	if ((!Keyboard::UpArrow && !Keyboard::DownArrow) && (PongScene::rightPaddle.transform.velocity.y >= -tolerance && PongScene::rightPaddle.transform.velocity.y < 0.0f)) {
		PongScene::rightPaddle.transform.velocity.y = 0.0f;
	}
}

void PongScene::RunPaddleControls() {
	PongScene::KillLowVelocity();
	PongScene::RunLeftPaddleControls();
	PongScene::RunRightPaddleControls();
	PongScene::RunPaddleVelocityConstraints();
}

void PongScene::RunLeftPaddleCollision() {
	float offset = 0.05;
	bool leftMet = (PongScene::ball.transform.position.x <= ((PongScene::leftPaddle.transform.position.x) + (PongScene::ball.transform.scale.x * 0.5f) + offset));
	bool belowTopMet = ((PongScene::ball.transform.position.y <= PongScene::leftPaddle.transform.position.y + ((PongScene::leftPaddle.transform.scale.y * 0.5f) + PongScene::ball.transform.scale.y * 0.5f)) && (PongScene::ball.transform.position.y >= PongScene::leftPaddle.transform.position.y));
	bool aboveBottomMet = ((PongScene::ball.transform.position.y >= PongScene::leftPaddle.transform.position.y - ((PongScene::leftPaddle.transform.scale.y * 0.5f) + PongScene::ball.transform.scale.y * 0.5f)) && (PongScene::ball.transform.position.y <= PongScene::leftPaddle.transform.position.y));
	bool tooFarToTheLeft = (PongScene::ball.transform.position.x + PongScene::ball.transform.scale.x * 0.5f) <= (PongScene::leftPaddle.transform.position.x + PongScene::leftPaddle.transform.scale.x * 0.5f);

	if ((leftMet && belowTopMet && !tooFarToTheLeft) || (leftMet && aboveBottomMet && !tooFarToTheLeft))
	{
		PongScene::ball.transform.position.x = PongScene::leftPaddle.transform.position.x + (PongScene::ball.transform.scale.x * 0.5f) + offset;
		PongGameOptions::currentBallBounceStrength += PongGameOptions::ballBounceStrengthIncrement;
		PongScene::ball.transform.velocity.x -= PongGameOptions::currentBallBounceStrength;
		PongScene::ball.transform.velocity = Utility::CalculateReflectionVector(PongScene::ball.transform.velocity + PongScene::leftPaddle.transform.velocity, vec3(1.0f, 0.0f, 0.0f));
	}
}

void PongScene::RunRightPaddleCollision() {
	float offset = 0.05;
	bool rightMet = (PongScene::ball.transform.position.x >= ((PongScene::rightPaddle.transform.position.x) - (PongScene::ball.transform.scale.x * 0.5f) - offset));
	bool belowTopMet = ((PongScene::ball.transform.position.y <= PongScene::rightPaddle.transform.position.y + ((PongScene::rightPaddle.transform.scale.y * 0.5f) + PongScene::ball.transform.scale.y * 0.5f)) && (PongScene::ball.transform.position.y >= PongScene::rightPaddle.transform.position.y));
	bool aboveBottomMet = ((PongScene::ball.transform.position.y >= PongScene::rightPaddle.transform.position.y - ((PongScene::rightPaddle.transform.scale.y * 0.5f) + PongScene::ball.transform.scale.y * 0.5f)) && (PongScene::ball.transform.position.y <= PongScene::rightPaddle.transform.position.y));
	bool tooFarToTheRight = (PongScene::ball.transform.position.x + PongScene::ball.transform.scale.x * 0.5f) >= (PongScene::rightPaddle.transform.position.x + PongScene::rightPaddle.transform.scale.x * 0.5f);

	if ((rightMet && belowTopMet && !tooFarToTheRight) || (rightMet && aboveBottomMet && !tooFarToTheRight))
	{
		PongScene::ball.transform.position.x = PongScene::rightPaddle.transform.position.x - (PongScene::ball.transform.scale.x * 0.5f) - offset;
		PongGameOptions::currentBallBounceStrength += PongGameOptions::ballBounceStrengthIncrement;
		PongScene::ball.transform.velocity.x += PongGameOptions::currentBallBounceStrength;
		PongScene::ball.transform.velocity = Utility::CalculateReflectionVector(PongScene::ball.transform.velocity + PongScene::rightPaddle.transform.velocity, vec3(-1.0f, 0.0f, 0.0f));
	}
}

void PongScene::RunLeftPaddlePositionConstraints() {
	float botOffset = 0.05f;
	if (PongScene::leftPaddle.transform.position.y + (PongScene::leftPaddle.transform.scale.y * 0.5f) < PongScene::bottomBound + PongScene::leftPaddle.transform.scale.y - botOffset) {
		PongScene::leftPaddle.transform.position.y = (PongScene::bottomBound + PongScene::leftPaddle.transform.scale.y * 0.5f) - botOffset;
		PongScene::leftPaddle.transform.velocity = vec3(0.0f, 0.0f, 0.0f);
	}

	float topOffset = 0.05f;
	if (PongScene::leftPaddle.transform.position.y + (PongScene::leftPaddle.transform.scale.y * 0.5f) > PongScene::topBound + topOffset) {
		PongScene::leftPaddle.transform.position.y = (PongScene::topBound - PongScene::leftPaddle.transform.scale.y * 0.5f) + topOffset;
		PongScene::leftPaddle.transform.velocity = vec3(0.0f, 0.0f, 0.0f);
	}

}

void PongScene::RunRightPaddlePositionConstraints() {
	float botOffset = 0.05f;
	if (PongScene::rightPaddle.transform.position.y + (PongScene::rightPaddle.transform.scale.y * 0.5f) < PongScene::bottomBound + PongScene::rightPaddle.transform.scale.y - botOffset) {
		PongScene::rightPaddle.transform.position.y = (PongScene::bottomBound + PongScene::rightPaddle.transform.scale.y * 0.5f) - botOffset;
		PongScene::rightPaddle.transform.velocity = vec3(0.0f, 0.0f, 0.0f);
	}

	float topOffset = 0.05f;
	if (PongScene::rightPaddle.transform.position.y + (PongScene::rightPaddle.transform.scale.y * 0.5f) > PongScene::topBound + topOffset) {
		PongScene::rightPaddle.transform.position.y = (PongScene::topBound - PongScene::rightPaddle.transform.scale.y * 0.5f) + topOffset;
		PongScene::rightPaddle.transform.velocity = vec3(0.0f, 0.0f, 0.0f);
	}

}

void PongScene::RunPaddlePositionConstraints() {
	PongScene::RunLeftPaddlePositionConstraints();
	PongScene::RunRightPaddlePositionConstraints();

}

void PongScene::RunPaddleCollision() {
	PongScene::RunLeftPaddleCollision();
	PongScene::RunRightPaddleCollision();
}



void PongScene::InitScene() {
	//GLuint vertexArrayID = NULL;
	//glGenVertexArrays(1, &vertexArrayID);
	//glBindVertexArray(vertexArrayID);

	//// Create and compile glsl from shaders.
	//PongGameOptions::programID = Load::LoadShaders("BasicVertexShader.vertexshader", "BasicFragmentShader.fragmentshader");

	//Matrix::MVPMatrixID = glGetUniformLocation(PongGameOptions::programID, "MVP");

	//Matrix::projectionMatrix = perspective(FIELD_OF_VIEW, PongGameOptions::aspectRatio, Z_NEAR, Z_FAR);
	BufferObject _bufferObj;
	_bufferObj.vertexBuffer = Load::LoadQuad();
	_bufferObj.vertexColorBuffer = Load::LoadColor(vec3(1.0f, 1.0f, 1.0f));

	PongScene::leftPaddle = GameObject(PongGameOptions::leftPaddlePosition, PongGameOptions::paddleScale, _bufferObj, DataCore::grassTexture);
	PongScene::rightPaddle = GameObject(PongGameOptions::rightPaddlePosition, PongGameOptions::paddleScale, _bufferObj, DataCore::grassTexture);
	PongScene::ball = GameObject(PongGameOptions::ballPosition, PongGameOptions::ballScale, _bufferObj, DataCore::grassTexture);

}

int PongScene::InitializePong() {
	PongScene::InitScene();
	//PongScene::ball.transform.velocity = PongGameOptions::startingBallVelocity;
	/*PongScene::leftPaddle.transform.position = vec3(-2.0f, 0.0, 0.0f);
	PongScene::rightPaddle.transform.position = vec3(2.0f, 0.0, 0.0f);*/
	return 0;
}

void PongScene::RunBallBehavior() {
	if (PongScene::isGameRunning && !PongScene::ballVelocityInitialized) {
		//PongScene::ball.transform.velocity = PongGameOptions::startingBallVelocity;
		PongScene::ball.transform.velocity = DecideStartingBallDirection();
		PongScene::ballVelocityInitialized = true;
	}
	else if (!PongScene::isGameRunning) {
		PongScene::ball.transform.position = PongGameOptions::startingPos;
		PongScene::ball.transform.velocity = vec3(0.0f, 0.0f, 0.0f);
		PongGameOptions::currentBallBounceStrength = 0.0f;

	}
}

int PongScene::PongMainLoop() {
	if (!PongScene::initializedPong) {
		if (PongScene::InitializePong() == EXIT_WITH_ERROR) return EXIT_WITH_ERROR;
		PongScene::initializedPong = true;
	}

	PongScene::RunGameTimer();
	PongScene::RunBallBehavior();
	PongScene::ball.Run(&DataCore::camera);
	PongScene::leftPaddle.Run(&DataCore::camera);
	PongScene::rightPaddle.Run(&DataCore::camera);
	PongScene::RunBallConstraints();
	PongScene::RunPaddleCollision();
	PongScene::RunPaddleControls();
	PongScene::RunPaddlePositionConstraints();
	return 0;
}

