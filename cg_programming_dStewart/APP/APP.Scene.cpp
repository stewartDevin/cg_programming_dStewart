// APP.Scene.cpp
//////////////////////////////////////////////////////////////////////////

#include "APP.Scene.h"
#include "../CORE/CORE.Utility.h"
#include "APP.GameOptions.h"
#include "../CORE/CORE.Keyboard.h"
#include "../CORE/CORE.Matrix.h"
#include "../CORE/CORE.Load.h"
#include "../CORE/CORE.GL_Init.h"

///////////////////////////////////////////////////////////////////////////////
// Scene
bool Scene::initializedPong = false;
Object Scene::leftPaddle;
Object Scene::rightPaddle;
Object Scene::ball;

float Scene::gameTimer;
bool Scene::isTimerRunning;
bool Scene::isGameRunning;
bool Scene::ballVelocityInitialized;

float Scene::leftBound;
float Scene::rightBound;
float Scene::topBound;
float Scene::bottomBound;

Scene::Scene() {
	
}

vec3 Scene::DecideStartingBallDirection() {
	int randInt = Utility::GetRandomInt(1, 2);
	if (randInt == 1) {
		return vec3(-GameOptions::ballVelocity, 0.0f, 0.0f);
	}
	else {
		return vec3(GameOptions::ballVelocity, 0.0f, 0.0f);
	}
}

void Scene::RunGameTimer() {
	if (Scene::isTimerRunning) Scene::gameTimer += 1.0f * GameOptions::deltaTime;

	if (Scene::gameTimer > 2.0f) {
		Scene::gameTimer = 0.0f;
		Scene::isTimerRunning = false;
		Scene::isGameRunning = true;
		Scene::ballVelocityInitialized = false;
	}
}

void Scene::RunBallConstraints() {

	if (Scene::ball.transform.position.x <= Scene::leftBound) {
		Scene::ball.transform.position.x = Scene::leftBound;
		Scene::isGameRunning = false;
		Scene::isTimerRunning = true;
		//Scene::ball.transform.velocity = Utility::CalculateReflectionVector(Scene::ball.transform.velocity, vec3(1.0f, 0.0f, 0.0f));
	}
	if (Scene::ball.transform.position.x >= Scene::rightBound) {
		Scene::ball.transform.position.x = Scene::rightBound;
		Scene::isGameRunning = false;
		Scene::isTimerRunning = true;
		//Scene::ball.transform.velocity = Utility::CalculateReflectionVector(Scene::ball.transform.velocity, vec3(-1.0f, 0.0f, 0.0f));
	}
	if (Scene::ball.transform.position.y >= Scene::topBound) {
		Scene::ball.transform.position.y = Scene::topBound;
		Scene::ball.transform.velocity = Utility::CalculateReflectionVector(Scene::ball.transform.velocity, vec3(0.0f, -1.0f, 0.0f));

	}
	if (Scene::ball.transform.position.y <= Scene::bottomBound) {
		Scene::ball.transform.position.y = Scene::bottomBound;
		Scene::ball.transform.velocity = Utility::CalculateReflectionVector(Scene::ball.transform.velocity, vec3(0.0f, 1.0f, 0.0f));

	}
}

void Scene::RunLeftPaddleControls() {
	if (Keyboard::W) {
		Scene::leftPaddle.transform.velocity.y += GameOptions::paddleAcceleration * GameOptions::deltaTime;
	}
	else {
		if (Scene::leftPaddle.transform.velocity.y > 0.0f) {
			Scene::leftPaddle.transform.velocity.y -= GameOptions::paddleAcceleration * GameOptions::deltaTime;
		}
	}

	if (Keyboard::S) {
		Scene::leftPaddle.transform.velocity.y -= GameOptions::paddleAcceleration * GameOptions::deltaTime;
	}
	else {
		if (Scene::leftPaddle.transform.velocity.y < 0.0f) {
			Scene::leftPaddle.transform.velocity.y += GameOptions::paddleAcceleration * GameOptions::deltaTime;
		}
	}
}

void Scene::RunRightPaddleControls() {
	if (Keyboard::UpArrow) {
		Scene::rightPaddle.transform.velocity.y += GameOptions::paddleAcceleration * GameOptions::deltaTime;
	}
	else {
		if (Scene::rightPaddle.transform.velocity.y > 0.0f) {
			Scene::rightPaddle.transform.velocity.y -= GameOptions::paddleAcceleration * GameOptions::deltaTime;
		}
	}

	if (Keyboard::DownArrow) {
		Scene::rightPaddle.transform.velocity.y -= GameOptions::paddleAcceleration * GameOptions::deltaTime;
	}
	else {
		if (Scene::rightPaddle.transform.velocity.y < 0.0f) {
			Scene::rightPaddle.transform.velocity.y += GameOptions::paddleAcceleration * GameOptions::deltaTime;
		}
	}
}

void Scene::RunPaddleVelocityConstraints() {
	// left
	if (Scene::leftPaddle.transform.velocity.y >= GameOptions::maxPaddleVelocity) {
		Scene::leftPaddle.transform.velocity.y = GameOptions::maxPaddleVelocity;
	}
	if (Scene::leftPaddle.transform.velocity.y <= -GameOptions::maxPaddleVelocity) {
		Scene::leftPaddle.transform.velocity.y = -GameOptions::maxPaddleVelocity;
	}

	// right
	if (Scene::rightPaddle.transform.velocity.y >= GameOptions::maxPaddleVelocity) {
		Scene::rightPaddle.transform.velocity.y = GameOptions::maxPaddleVelocity;
	}
	if (Scene::rightPaddle.transform.velocity.y <= -GameOptions::maxPaddleVelocity) {
		Scene::rightPaddle.transform.velocity.y = -GameOptions::maxPaddleVelocity;
	}
}

void Scene::KillLowVelocity() {
	float tolerance = 0.1f;
	if ((!Keyboard::W && !Keyboard::S) && (Scene::leftPaddle.transform.velocity.y <= tolerance && Scene::leftPaddle.transform.velocity.y > 0.0f)) {
		Scene::leftPaddle.transform.velocity.y = 0.0f;
	}
	if ((!Keyboard::W && !Keyboard::S) && (Scene::leftPaddle.transform.velocity.y >= -tolerance && Scene::leftPaddle.transform.velocity.y < 0.0f)) {
		Scene::leftPaddle.transform.velocity.y = 0.0f;
	}

	if ((!Keyboard::UpArrow && !Keyboard::DownArrow) && (Scene::rightPaddle.transform.velocity.y <= tolerance && Scene::rightPaddle.transform.velocity.y > 0.0f)) {
		Scene::rightPaddle.transform.velocity.y = 0.0f;
	}
	if ((!Keyboard::UpArrow && !Keyboard::DownArrow) && (Scene::rightPaddle.transform.velocity.y >= -tolerance && Scene::rightPaddle.transform.velocity.y < 0.0f)) {
		Scene::rightPaddle.transform.velocity.y = 0.0f;
	}
}

void Scene::RunPaddleControls() {
	Scene::KillLowVelocity();
	Scene::RunLeftPaddleControls();
	Scene::RunRightPaddleControls();
	Scene::RunPaddleVelocityConstraints();
}

void Scene::RunLeftPaddleCollision() {
	float offset = 0.05;
	bool leftMet = (Scene::ball.transform.position.x <= ((Scene::leftPaddle.transform.position.x) + (Scene::ball.transform.scale.x * 0.5f) + offset));
	bool belowTopMet = ((Scene::ball.transform.position.y <= Scene::leftPaddle.transform.position.y + ((Scene::leftPaddle.transform.scale.y * 0.5f) + Scene::ball.transform.scale.y * 0.5f)) && (Scene::ball.transform.position.y >= Scene::leftPaddle.transform.position.y));
	bool aboveBottomMet = ((Scene::ball.transform.position.y >= Scene::leftPaddle.transform.position.y - ((Scene::leftPaddle.transform.scale.y * 0.5f) + Scene::ball.transform.scale.y * 0.5f)) && (Scene::ball.transform.position.y <= Scene::leftPaddle.transform.position.y));
	bool tooFarToTheLeft = (Scene::ball.transform.position.x + Scene::ball.transform.scale.x * 0.5f) <= (Scene::leftPaddle.transform.position.x + Scene::leftPaddle.transform.scale.x * 0.5f);

	if ((leftMet && belowTopMet && !tooFarToTheLeft) || (leftMet && aboveBottomMet && !tooFarToTheLeft))
	{
		Scene::ball.transform.position.x = Scene::leftPaddle.transform.position.x + (Scene::ball.transform.scale.x * 0.5f) + offset;
		GameOptions::currentBallBounceStrength += GameOptions::ballBounceStrengthIncrement;
		Scene::ball.transform.velocity.x -= GameOptions::currentBallBounceStrength;
		Scene::ball.transform.velocity = Utility::CalculateReflectionVector(Scene::ball.transform.velocity + Scene::leftPaddle.transform.velocity, vec3(1.0f, 0.0f, 0.0f));
	}
}

void Scene::RunRightPaddleCollision() {
	float offset = 0.05;
	bool rightMet = (Scene::ball.transform.position.x >= ((Scene::rightPaddle.transform.position.x) - (Scene::ball.transform.scale.x * 0.5f) - offset));
	bool belowTopMet = ((Scene::ball.transform.position.y <= Scene::rightPaddle.transform.position.y + ((Scene::rightPaddle.transform.scale.y * 0.5f) + Scene::ball.transform.scale.y * 0.5f)) && (Scene::ball.transform.position.y >= Scene::rightPaddle.transform.position.y));
	bool aboveBottomMet = ((Scene::ball.transform.position.y >= Scene::rightPaddle.transform.position.y - ((Scene::rightPaddle.transform.scale.y * 0.5f) + Scene::ball.transform.scale.y * 0.5f)) && (Scene::ball.transform.position.y <= Scene::rightPaddle.transform.position.y));
	bool tooFarToTheRight = (Scene::ball.transform.position.x + Scene::ball.transform.scale.x * 0.5f) >= (Scene::rightPaddle.transform.position.x + Scene::rightPaddle.transform.scale.x * 0.5f);

	if ((rightMet && belowTopMet && !tooFarToTheRight) || (rightMet && aboveBottomMet && !tooFarToTheRight))
	{
		Scene::ball.transform.position.x = Scene::rightPaddle.transform.position.x - (Scene::ball.transform.scale.x * 0.5f) - offset;
		GameOptions::currentBallBounceStrength += GameOptions::ballBounceStrengthIncrement;
		Scene::ball.transform.velocity.x += GameOptions::currentBallBounceStrength;
		Scene::ball.transform.velocity = Utility::CalculateReflectionVector(Scene::ball.transform.velocity + Scene::rightPaddle.transform.velocity, vec3(-1.0f, 0.0f, 0.0f));
	}
}

void Scene::RunLeftPaddlePositionConstraints() {
	float botOffset = 0.05f;
	if (Scene::leftPaddle.transform.position.y + (Scene::leftPaddle.transform.scale.y * 0.5f) < Scene::bottomBound + Scene::leftPaddle.transform.scale.y - botOffset) {
		Scene::leftPaddle.transform.position.y = (Scene::bottomBound + Scene::leftPaddle.transform.scale.y * 0.5f) - botOffset;
		Scene::leftPaddle.transform.velocity = vec3(0.0f, 0.0f, 0.0f);
	}

	float topOffset = 0.05f;
	if (Scene::leftPaddle.transform.position.y + (Scene::leftPaddle.transform.scale.y * 0.5f) > Scene::topBound + topOffset) {
		Scene::leftPaddle.transform.position.y = (Scene::topBound - Scene::leftPaddle.transform.scale.y * 0.5f) + topOffset;
		Scene::leftPaddle.transform.velocity = vec3(0.0f, 0.0f, 0.0f);
	}

}

void Scene::RunRightPaddlePositionConstraints() {
	float botOffset = 0.05f;
	if (Scene::rightPaddle.transform.position.y + (Scene::rightPaddle.transform.scale.y * 0.5f) < Scene::bottomBound + Scene::rightPaddle.transform.scale.y - botOffset) {
		Scene::rightPaddle.transform.position.y = (Scene::bottomBound + Scene::rightPaddle.transform.scale.y * 0.5f) - botOffset;
		Scene::rightPaddle.transform.velocity = vec3(0.0f, 0.0f, 0.0f);
	}

	float topOffset = 0.05f;
	if (Scene::rightPaddle.transform.position.y + (Scene::rightPaddle.transform.scale.y * 0.5f) > Scene::topBound + topOffset) {
		Scene::rightPaddle.transform.position.y = (Scene::topBound - Scene::rightPaddle.transform.scale.y * 0.5f) + topOffset;
		Scene::rightPaddle.transform.velocity = vec3(0.0f, 0.0f, 0.0f);
	}

}

void Scene::RunPaddlePositionConstraints() {
	Scene::RunLeftPaddlePositionConstraints();
	Scene::RunRightPaddlePositionConstraints();

}

void Scene::RunPaddleCollision() {
	Scene::RunLeftPaddleCollision();
	Scene::RunRightPaddleCollision();
}

void Scene::InitScene() {
	GLuint vertexArrayID = NULL;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	// Create and compile glsl from shaders.
	GameOptions::programID = Load::LoadShaders("BasicVertexShader.vertexshader", "BasicFragmentShader.fragmentshader");

	Matrix::MVPMatrixID = glGetUniformLocation(GameOptions::programID, "MVP");

	Matrix::projectionMatrix = perspective(FIELD_OF_VIEW, GameOptions::aspectRatio, Z_NEAR, Z_FAR);

	Scene::leftPaddle = Object(GameOptions::leftPaddlePosition, GameOptions::paddleScale, Load::LoadColor(vec3(1.0f, 1.0f, 1.0f)), Load::LoadQuad());
	Scene::rightPaddle = Object(GameOptions::rightPaddlePosition, GameOptions::paddleScale, Load::LoadColor(vec3(1.0f, 1.0f, 1.0f)), Load::LoadQuad());
	Scene::ball = Object(GameOptions::ballPosition, GameOptions::ballScale, Load::LoadColor(vec3(1.0f, 1.0f, 1.0f)), Load::LoadQuad());

}

int Scene::InitializePong() {
	if (GL_Init::InitWindow() | GL_Init::InitGlew()) {
		return EXIT_WITH_ERROR;
	}
	Scene::InitScene();
	//Scene::ball.transform.velocity = GameOptions::startingBallVelocity;
	/*Scene::leftPaddle.transform.position = vec3(-2.0f, 0.0, 0.0f);
	Scene::rightPaddle.transform.position = vec3(2.0f, 0.0, 0.0f);*/
}

void Scene::RunBallBehavior() {
	if (Scene::isGameRunning && !Scene::ballVelocityInitialized) {
		//Scene::ball.transform.velocity = GameOptions::startingBallVelocity;
		Scene::ball.transform.velocity = DecideStartingBallDirection();
		Scene::ballVelocityInitialized = true;
	}
	else if (!Scene::isGameRunning) {
		Scene::ball.transform.position = GameOptions::startingPos;
		Scene::ball.transform.velocity = vec3(0.0f, 0.0f, 0.0f);
		GameOptions::currentBallBounceStrength = 0.0f;

	}
}

int Scene::MainLoop() {
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//fprintf(stdout, "Delta Time: %f", getDeltaTime()); 
		GameOptions::deltaTime = Utility::getDeltaTime();

		if (!Scene::initializedPong) {
			if (Scene::InitializePong() == EXIT_WITH_ERROR) return EXIT_WITH_ERROR;
			Scene::initializedPong = true;
		}

		glUseProgram(GameOptions::programID);

		// camera matrix
		Matrix::viewMatrix = glm::lookAt(
			vec3(0, 0, 3),		// position
			vec3(0, 0, 0),		// look at
			vec3(0, 1, 0)		// up
			);

		Keyboard::RunKeyboardKeys();

		Scene::RunGameTimer();
		Scene::RunBallBehavior();
		Scene::ball.Run();
		Scene::leftPaddle.Run();
		Scene::rightPaddle.Run();
		Scene::RunBallConstraints();
		Scene::RunPaddleCollision();
		Scene::RunPaddleControls();
		Scene::RunPaddlePositionConstraints();

		//Update();
		//Render();
		glfwSwapBuffers(GameOptions::window);
		glfwPollEvents();

	} while (glfwGetKey(GameOptions::window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(GameOptions::window) == 0);
}