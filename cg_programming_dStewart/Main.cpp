// Main.cpp
////////////////////////////////////////////////////////////////////////

#include "Application.h"

///////////////////////////////////////////////////////////////////////////////
// GameOptions
static class GameOptions {
public:
	float aspectRatio;
	GLuint programID;
	vec3 paddleScale;
	vec3 ballScale;
	GLFWwindow* window;
	float deltaTime;
	vec3 ballPosition;
	vec3 leftPaddlePosition;
	vec3 rightPaddlePosition;
	vec3 startingPos;
	float ballVelocity;
	vec3 startingBallVelocity;
	float paddleWidth;
	float gameTimer;

	float maxPaddleVelocity;
	float paddleAcceleration;

	GameOptions::GameOptions() {
		this->aspectRatio = SCREEN_WIDTH / (float)SCREEN_HEIGHT;
		//this->programID = glCreateProgram();
		this->paddleScale = vec3(0.1f, 1.0f, 1.0f);
		this->ballScale = vec3(0.1f, 0.1f, 1.0f);

		this->window = NULL;
		this->deltaTime = 0.0f;
		this->ballPosition = vec3(0.0f, 0.0f, 0.0f);
		this->leftPaddlePosition = vec3(-2.5f, 0.0f, 0.0f);
		this->rightPaddlePosition = vec3(2.5f, 0.0f, 0.0f);

		this->startingPos = vec3(0.0f, 0.0f, 0.0f);
		this->ballVelocity = 2.5f;
		this->startingBallVelocity = vec3(2.0f, 0.0f, 0.0f);
		this->paddleWidth = 5.0f;

		this->gameTimer = 0.0f;

		this->maxPaddleVelocity = 1.4f;
		this->paddleAcceleration = 10.0f;
	}

}gameOptions;

///////////////////////////////////////////////////////////////////////////////
// GL_Init
static class GL_Init {
public:
	static int InitGlew() {
		glfwMakeContextCurrent(gameOptions.window); // Initialize GLEW
		glewExperimental = true; // has to do with core profile. 
		if (glewInit() != GLEW_OK) {
			fprintf(stderr, "Failed to initialize GLEW.");
			return EXIT_WITH_ERROR;
		}

		return EXIT_WITH_SUCCESS;
	}

	static int InitWindow() {
		if (!glfwInit()) {
			fprintf(stderr, "Failed to initialize GLFW.");
			return EXIT_WITH_ERROR;
		}

		glfwWindowHint(GLFW_SAMPLES, ANTIALIASING);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPEN_GL_VERSION);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPEN_GL_VERSION);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // get mac up and running.
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // we don't want the old openGL, gives the new one.

		gameOptions.window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME, NULL, NULL);

		if (gameOptions.window == NULL) {
			fprintf(stderr, "Failed to initialize window.");
			glfwTerminate();
			return EXIT_WITH_ERROR;
		}

		// Ensure we can capture the escape key being pressed below
		glfwSetInputMode(gameOptions.window, GLFW_STICKY_KEYS, GL_TRUE);

		return EXIT_WITH_SUCCESS;
	}

};

///////////////////////////////////////////////////////////////////////////////
// Utility
static class Utility {
public:
	static float& getDeltaTime() {
		static float lastTime = glfwGetTime();

		float now = glfwGetTime();
		float deltaTime = now - lastTime;

		lastTime = now;
		return deltaTime;
	}

	static vec3 NormalizeVector3(vec3 vector) {
		float length = sqrt((vector.x*vector.x) + (vector.y*vector.y) + (vector.z*vector.z));
		vec3 n = vec3((vector.x / length), (vector.y / length), (vector.z / length));

		return n;
	}

	static vec3 CalculateReflectionVector(vec3 vector, vec3 normal) {
		//R = V - 2 * N * dot(V, N)
		vec3 r;

		r.x = vector.x - (2.0f * normal.x * dot(vector, normal));
		r.y = vector.y - (2.0f * normal.y * dot(vector, normal));
		r.z = 0.0f;

		return r;
	}

	static int GetRandomInt(int from, int to) {
		return rand() % to + from;

	}

};

///////////////////////////////////////////////////////////////////////////////
// Keyboard
static class Keyboard {
public:
	bool W;
	bool A;
	bool S;
	bool D;
	bool UpArrow;
	bool LeftArrow;
	bool RightArrow;
	bool DownArrow;

	Keyboard::Keyboard() {
		this->W = false;
		this->A = false;
		this->S = false;
		this->D = false;
		this->UpArrow = false;
		this->LeftArrow = false;
		this->RightArrow = false;
		this->DownArrow = false;
	}

	static void RunKeyboardKeys() {
		if (glfwGetKey(gameOptions.window, GLFW_KEY_W) == GLFW_PRESS) {
			keyboard.W = true;
		}
		else {
			keyboard.W = false;
		}

		if (glfwGetKey(gameOptions.window, GLFW_KEY_A) == GLFW_PRESS) {
			keyboard.A = true;
		}
		else {
			keyboard.A = false;
		}

		if (glfwGetKey(gameOptions.window, GLFW_KEY_S) == GLFW_PRESS) {
			keyboard.S = true;
		}
		else {
			keyboard.S = false;
		}

		if (glfwGetKey(gameOptions.window, GLFW_KEY_D) == GLFW_PRESS) {
			keyboard.D = true;
		}
		else {
			keyboard.D = false;
		}

		if (glfwGetKey(gameOptions.window, GLFW_KEY_UP) == GLFW_PRESS) {
			keyboard.UpArrow = true;
		}
		else {
			keyboard.UpArrow = false;
		}

		if (glfwGetKey(gameOptions.window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			keyboard.LeftArrow = true;
		}
		else {
			keyboard.LeftArrow = false;
		}

		if (glfwGetKey(gameOptions.window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			keyboard.DownArrow = true;
		}
		else {
			keyboard.DownArrow = false;
		}

		if (glfwGetKey(gameOptions.window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			keyboard.RightArrow = true;
		}
		else {
			keyboard.RightArrow = false;
		}
	}

} keyboard;

///////////////////////////////////////////////////////////////////////////////
// Transform
class Transform {
public:
	vec3 position;
	vec3 scale;
	vec3 rotation;
	vec3 velocity;

	Transform::Transform() {
		this->position = vec3(0.0f, 0.0f, 0.0f);
		this->scale = vec3(1.0f, 1.0f, 1.0f);
		this->rotation = vec3(0.0f, 0.0f, 0.0f);
		vec3 velocity = vec3(0.0f, 0.0f, 0.0f);
	}
	Transform::Transform(vec3 position, vec3 scale, vec3 rotation, vec3 velocity) {
		this->position = position;
		this->scale = scale;
		this->rotation = rotation;
		this->velocity = velocity;
	}
};

///////////////////////////////////////////////////////////////////////////////
// GameObject
class GameObject {
public:
	Transform transform;
	GLuint objectID;
	GLuint colorID;
	mat4 MVPMatrix;
	bool initialized;

	GameObject::GameObject() {

	}

	virtual void Init() = 0;
	virtual void Run() = 0;
};

///////////////////////////////////////////////////////////////////////////////
// Matrix
static class Matrix {
public:
	mat4 projectionMatrix;
	mat4 viewMatrix;
	GLuint MVPMatrixID;

	Matrix::Matrix() {
		this->projectionMatrix = perspective(FIELD_OF_VIEW, gameOptions.aspectRatio, Z_NEAR, Z_FAR);
		this->viewMatrix = glm::lookAt(
			vec3(0, 0, 3),		// position
			vec3(0, 0, 0),		// look at
			vec3(0, 1, 0)		// up
			);
		//this->MVPMatrixID = glGetUniformLocation(gameOptions.programID, "MVP");
	}

} matrix;

///////////////////////////////////////////////////////////////////////////////
// Render
static class Render {
public:
	static glm::mat4 RenderVertex(GLuint vertexBuffer, const vec3& position, const vec3& scaleVec) {
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

		glVertexAttribPointer(
			0,			// attribute layout
			3,			// how many elements in array? 
			GL_FLOAT,   // what datatype?
			GL_FALSE,   // normalized?
			0,			// stride...
			(void*)0	// array buffer offset...
			);

		mat4 identityMatrix = mat4(1.0f);
		mat4 positionMatrix = translate(identityMatrix, position);
		mat4 scaleMatrix = scale(positionMatrix, scaleVec);
		return scaleMatrix;
	}

	static void RenderColor(GLuint vertexBuffer) {
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

		glVertexAttribPointer(
			1,			// attribute layout
			3,			// how many elements in array? 
			GL_FLOAT,   // what datatype?
			GL_FALSE,   // normalized?
			0,			// stride...
			(void*)0	// array buffer offset...
			);
	}

	//static void RenderTriangle(GLuint vertexBuffer, GLuint colorBuffer) {
	//	RenderVertex(vertexBuffer);
	//	RenderColor(colorBuffer);
	//
	//	glDrawArrays(GL_TRIANGLES, 0, 3);
	//	glDisableVertexAttribArray(0);
	//	glDisableVertexAttribArray(1);
	//}

	static glm::mat4 RenderQuad(GLuint vertexBuffer, const vec3& position, GLuint colorBuffer, const vec3& scaleVec) {
		mat4 positionMatrix = RenderVertex(vertexBuffer, position, scaleVec);

		RenderColor(colorBuffer);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(0);
		return positionMatrix;
	}

	static glm::mat4 RenderQuad(GLuint vertexBuffer, const vec3& position, const vec3& scaleVec) {
		mat4 positionMatrix = RenderVertex(vertexBuffer, position, scaleVec);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(0);
		return positionMatrix;
	}

};

///////////////////////////////////////////////////////////////////////////////
// Object
class Object : public GameObject {
public:

	Object::Object(vec3 position, vec3 scale, GLuint colorID, GLuint objectID) {
		this->transform.position = position;
		this->transform.scale = scale;
		this->objectID = objectID;
		this->colorID = colorID;
		this->initialized = false;
	}

	Object::Object() {
		this->objectID = NULL;
		this->colorID = NULL;
		this->initialized = false;
	}

	static Object* Object::CreateObject(vec3 position, vec3 scale, GLuint colorID, GLuint objectID) {
		Object* object = new Object(position, scale, colorID, objectID);
		return object;
	}
	static void Object::DeleteObject(Object* object) {
		delete(object);
	}
	void DeleteObject() {
		delete(this);
	}

	void Init() {

	}

	void Run() {
		if (!this->initialized) {
			this->Init();
			this->initialized = true;
		}

		this->MVPMatrix = matrix.projectionMatrix * matrix.viewMatrix * Render::RenderQuad(this->objectID, this->transform.position, this->colorID, this->transform.scale);
		glUniformMatrix4fv(matrix.MVPMatrixID, 1, GL_FALSE, &this->MVPMatrix[0][0]);

		this->transform.position += this->transform.velocity * gameOptions.deltaTime;
	}
};

///////////////////////////////////////////////////////////////////////////////
// Load
static class Load {
public:
	static GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {
		GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		//Read in shader code here.
		string vertexShaderCode = "";
		ifstream vertexShaderStream(vertex_file_path, ios::in);

		if (vertexShaderStream.is_open()) {
			string line = "";
			while (getline(vertexShaderStream, line)) {
				vertexShaderCode += "\n" + line;
			}

			vertexShaderStream.close();
		}

		string fragmentShaderCode = "";
		ifstream fragmentShaderStream(fragment_file_path, ios::in);

		if (fragmentShaderStream.is_open()) {
			string line = "";
			while (getline(fragmentShaderStream, line)) {
				fragmentShaderCode += "\n" + line;
			}

			fragmentShaderStream.close();
		}

		GLint result = GL_FALSE;
		int infoLogLength = NULL;

		// compile shaders here...
		printf("Compiling vertex shader: %s\n", vertex_file_path);
		char const* vertexSourcePointer = vertexShaderCode.c_str();
		glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
		glCompileShader(vertexShaderID);

		//Check vertex shader...
		glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
		glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

		char* vertexShaderErrorMessage = new char[infoLogLength];
		glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
		fprintf(stdout, "%s\n", &vertexShaderErrorMessage[0]);

		//Compile the fragment shader
		printf("Compiling fragment shader: %s\n", fragment_file_path);
		char const* fragmentSourcePointer = fragmentShaderCode.c_str();
		glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
		glCompileShader(fragmentShaderID);

		//Check vertex shader...
		glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
		glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

		char* fragmentShaderErrorMessage = new char[infoLogLength];
		glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		fprintf(stdout, "%s\n", &fragmentShaderErrorMessage[0]);

		// Link program...
		fprintf(stdout, "Linking program.\n");

		GLuint programID = glCreateProgram();
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);
		glLinkProgram(programID);

		//Check the program...
		glGetProgramiv(programID, GL_LINK_STATUS, &result);
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* programErrorMessage = new char[glm::max(infoLogLength, int(1))];
		glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
		fprintf(stdout, "%s\n", &programErrorMessage[0]);

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);

		delete(programErrorMessage);
		programErrorMessage = NULL;

		delete(fragmentShaderErrorMessage);
		fragmentShaderErrorMessage = NULL;

		delete(vertexShaderErrorMessage);
		vertexShaderErrorMessage = NULL;

		return programID;
	}

	static GLuint& LoadQuad() {
		float offset = 0.5f;

		GLfloat g_vertex_buffer_data[] = {
			0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f,

			0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		};

		for (int n = 0, size = 18; n < size; n++) {
			float &f = g_vertex_buffer_data[n];
			f -= offset;
			continue;
		}

		GLuint vertexBuffer = 0;
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

		return vertexBuffer;
	}

	static GLuint& LoadTriangle() {
		static const GLfloat g_vertex_buffer_data[] = {
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		};

		GLuint vertexBuffer = 0;
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

		return vertexBuffer;
	}

	static GLuint& LoadColor(vec3 rgb_color) {
		static const GLfloat g_color_buffer_data[] = {
			rgb_color.x, rgb_color.y, rgb_color.z,
			rgb_color.x, rgb_color.y, rgb_color.z,
			rgb_color.x, rgb_color.y, rgb_color.z,
			rgb_color.x, rgb_color.y, rgb_color.z,
			rgb_color.x, rgb_color.y, rgb_color.z,
			rgb_color.x, rgb_color.y, rgb_color.z
		};

		GLuint vertexBuffer = 0;
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

		return vertexBuffer;
	}

};

///////////////////////////////////////////////////////////////////////////////
// Scene
static class Scene {
public:
	bool initializedPong;
	Object leftPaddle;
	Object rightPaddle;
	Object ball;

	float gameTimer;
	bool isTimerRunning;
	bool isGameRunning;
	bool ballVelocityInitialized;

	float leftBound;
	float rightBound;
	float topBound;
	float bottomBound;
	Scene::Scene() {
		this->initializedPong = false;
		this->gameTimer = 0.0f;
		this->isTimerRunning = true;
		this->isGameRunning = false;
		this->ballVelocityInitialized = false;
		this->leftBound = -2.6f;
		this->rightBound = 2.6f;
		this->topBound = 1.9f;
		this->bottomBound = -1.9f;
	}

	vec3 DecideStartingBallDirection() {
		int randInt = Utility::GetRandomInt(1, 2);
		if (randInt == 1) {
			return vec3(-gameOptions.ballVelocity, 0.0f, 0.0f);
		}
		else {
			return vec3(gameOptions.ballVelocity, 0.0f, 0.0f);
		}
	}

	void Scene::RunGameTimer() {
		if (scene.isTimerRunning) scene.gameTimer += 1.0f * gameOptions.deltaTime;

		if (scene.gameTimer > 2.0f) {
			scene.gameTimer = 0.0f;
			scene.isTimerRunning = false;
			scene.isGameRunning = true;
			scene.ballVelocityInitialized = false;
		}
	}

	void Scene::RunBallConstraints() {

		if (scene.ball.transform.position.x <= scene.leftBound) {
			scene.ball.transform.position.x = scene.leftBound;
			scene.isGameRunning = false;
			scene.isTimerRunning = true;
			//scene.ball.transform.velocity = Utility::CalculateReflectionVector(scene.ball.transform.velocity, vec3(1.0f, 0.0f, 0.0f));
		}
		if (scene.ball.transform.position.x >= scene.rightBound) {
			scene.ball.transform.position.x = scene.rightBound;
			scene.isGameRunning = false;
			scene.isTimerRunning = true;
			//scene.ball.transform.velocity = Utility::CalculateReflectionVector(scene.ball.transform.velocity, vec3(-1.0f, 0.0f, 0.0f));
		}
		if (scene.ball.transform.position.y >= scene.topBound) {
			scene.ball.transform.position.y = scene.topBound;
			scene.ball.transform.velocity = Utility::CalculateReflectionVector(scene.ball.transform.velocity, vec3(0.0f, -1.0f, 0.0f));

		}
		if (scene.ball.transform.position.y <= scene.bottomBound) {
			scene.ball.transform.position.y = scene.bottomBound;
			scene.ball.transform.velocity = Utility::CalculateReflectionVector(scene.ball.transform.velocity, vec3(0.0f, 1.0f, 0.0f));

		}
	}

	void Scene::RunLeftPaddleControls() {
		if (keyboard.W) {
			scene.leftPaddle.transform.velocity.y += gameOptions.paddleAcceleration * gameOptions.deltaTime;
		}
		else {
			if (scene.leftPaddle.transform.velocity.y > 0.0f) {
				scene.leftPaddle.transform.velocity.y -= gameOptions.paddleAcceleration * gameOptions.deltaTime;
			}
		}

		if (keyboard.S) {
			scene.leftPaddle.transform.velocity.y -= gameOptions.paddleAcceleration * gameOptions.deltaTime;
		}
		else {
			if (scene.leftPaddle.transform.velocity.y < 0.0f) {
				scene.leftPaddle.transform.velocity.y += gameOptions.paddleAcceleration * gameOptions.deltaTime;
			}
		}
	}

	void Scene::RunRightPaddleControls() {
		if (keyboard.UpArrow) {
			scene.rightPaddle.transform.velocity.y += gameOptions.paddleAcceleration * gameOptions.deltaTime;
		}
		else {
			if (scene.rightPaddle.transform.velocity.y > 0.0f) {
				scene.rightPaddle.transform.velocity.y -= gameOptions.paddleAcceleration * gameOptions.deltaTime;
			}
		}

		if (keyboard.DownArrow) {
			scene.rightPaddle.transform.velocity.y -= gameOptions.paddleAcceleration * gameOptions.deltaTime;
		}
		else {
			if (scene.rightPaddle.transform.velocity.y < 0.0f) {
				scene.rightPaddle.transform.velocity.y += gameOptions.paddleAcceleration * gameOptions.deltaTime;
			}
		}
	}

	void Scene::RunPaddleVelocityConstraints() {
		// left
		if (scene.leftPaddle.transform.velocity.y >= gameOptions.maxPaddleVelocity) {
			scene.leftPaddle.transform.velocity.y = gameOptions.maxPaddleVelocity;
		}
		if (scene.leftPaddle.transform.velocity.y <= -gameOptions.maxPaddleVelocity) {
			scene.leftPaddle.transform.velocity.y = -gameOptions.maxPaddleVelocity;
		}

		// right
		if (scene.rightPaddle.transform.velocity.y >= gameOptions.maxPaddleVelocity) {
			scene.rightPaddle.transform.velocity.y = gameOptions.maxPaddleVelocity;
		}
		if (scene.rightPaddle.transform.velocity.y <= -gameOptions.maxPaddleVelocity) {
			scene.rightPaddle.transform.velocity.y = -gameOptions.maxPaddleVelocity;
		}
	}

	void Scene::KillLowVelocity() {
		float tolerance = 0.1f;
		if ((!keyboard.W && !keyboard.S) && (scene.leftPaddle.transform.velocity.y <= tolerance && scene.leftPaddle.transform.velocity.y > 0.0f)) {
			scene.leftPaddle.transform.velocity.y = 0.0f;
		}
		if ((!keyboard.W && !keyboard.S) && (scene.leftPaddle.transform.velocity.y >= -tolerance && scene.leftPaddle.transform.velocity.y < 0.0f)) {
			scene.leftPaddle.transform.velocity.y = 0.0f;
		}

		if ((!keyboard.UpArrow && !keyboard.DownArrow) && (scene.rightPaddle.transform.velocity.y <= tolerance && scene.rightPaddle.transform.velocity.y > 0.0f)) {
			scene.rightPaddle.transform.velocity.y = 0.0f;
		}
		if ((!keyboard.UpArrow && !keyboard.DownArrow) && (scene.rightPaddle.transform.velocity.y >= -tolerance && scene.rightPaddle.transform.velocity.y < 0.0f)) {
			scene.rightPaddle.transform.velocity.y = 0.0f;
		}
	}

	void Scene::RunPaddleControls() {
		scene.KillLowVelocity();
		scene.RunLeftPaddleControls();
		scene.RunRightPaddleControls();
		scene.RunPaddleVelocityConstraints();
	}

	void Scene::RunLeftPaddleCollision() {
		float offset = 0.05;
		bool leftMet = (scene.ball.transform.position.x <= ((scene.leftPaddle.transform.position.x) + (scene.ball.transform.scale.x * 0.5f) + offset));
		bool belowTopMet = ((scene.ball.transform.position.y <= scene.leftPaddle.transform.position.y + ((scene.leftPaddle.transform.scale.y * 0.5f) + scene.ball.transform.scale.y * 0.5f)) && (scene.ball.transform.position.y >= scene.leftPaddle.transform.position.y));
		bool aboveBottomMet = ((scene.ball.transform.position.y >= scene.leftPaddle.transform.position.y - ((scene.leftPaddle.transform.scale.y * 0.5f) + scene.ball.transform.scale.y * 0.5f)) && (scene.ball.transform.position.y <= scene.leftPaddle.transform.position.y));
		bool tooFarToTheLeft = (scene.ball.transform.position.x + scene.ball.transform.scale.x * 0.5f) <= (scene.leftPaddle.transform.position.x + scene.leftPaddle.transform.scale.x * 0.5f);

		if ((leftMet && belowTopMet && !tooFarToTheLeft) || (leftMet && aboveBottomMet && !tooFarToTheLeft))
		{
			scene.ball.transform.position.x = scene.leftPaddle.transform.position.x + (scene.ball.transform.scale.x * 0.5f) + offset;
			scene.ball.transform.velocity = Utility::CalculateReflectionVector(scene.ball.transform.velocity + scene.leftPaddle.transform.velocity, vec3(1.0f, 0.0f, 0.0f));
		}
	}

	void Scene::RunRightPaddleCollision() {
		float offset = 0.05;
		bool rightMet = (scene.ball.transform.position.x >= ((scene.rightPaddle.transform.position.x) - (scene.ball.transform.scale.x * 0.5f) - offset));
		bool belowTopMet = ((scene.ball.transform.position.y <= scene.rightPaddle.transform.position.y + ((scene.rightPaddle.transform.scale.y * 0.5f) + scene.ball.transform.scale.y * 0.5f)) && (scene.ball.transform.position.y >= scene.rightPaddle.transform.position.y));
		bool aboveBottomMet = ((scene.ball.transform.position.y >= scene.rightPaddle.transform.position.y - ((scene.rightPaddle.transform.scale.y * 0.5f) + scene.ball.transform.scale.y * 0.5f)) && (scene.ball.transform.position.y <= scene.rightPaddle.transform.position.y));
		bool tooFarToTheRight = (scene.ball.transform.position.x + scene.ball.transform.scale.x * 0.5f) >= (scene.rightPaddle.transform.position.x + scene.rightPaddle.transform.scale.x * 0.5f);

		if ((rightMet && belowTopMet && !tooFarToTheRight) || (rightMet && aboveBottomMet && !tooFarToTheRight))
		{
			scene.ball.transform.position.x = scene.rightPaddle.transform.position.x - (scene.ball.transform.scale.x * 0.5f) - offset;
			scene.ball.transform.velocity = Utility::CalculateReflectionVector(scene.ball.transform.velocity + scene.rightPaddle.transform.velocity, vec3(-1.0f, 0.0f, 0.0f));
		}
	}

	void Scene::RunLeftPaddlePositionConstraints() {
		float botOffset = 0.05f;
		if (scene.leftPaddle.transform.position.y + (scene.leftPaddle.transform.scale.y * 0.5f) < scene.bottomBound + scene.leftPaddle.transform.scale.y - botOffset) {
			scene.leftPaddle.transform.position.y = (scene.bottomBound + scene.leftPaddle.transform.scale.y * 0.5f) - botOffset;
			scene.leftPaddle.transform.velocity = vec3(0.0f, 0.0f, 0.0f);
		}

		float topOffset = 0.05f;
		if (scene.leftPaddle.transform.position.y + (scene.leftPaddle.transform.scale.y * 0.5f) > scene.topBound + topOffset) {
			scene.leftPaddle.transform.position.y = (scene.topBound - scene.leftPaddle.transform.scale.y * 0.5f) + topOffset;
			scene.leftPaddle.transform.velocity = vec3(0.0f, 0.0f, 0.0f);
		}

	}

	void Scene::RunRightPaddlePositionConstraints() {
		float botOffset = 0.05f;
		if (scene.rightPaddle.transform.position.y + (scene.rightPaddle.transform.scale.y * 0.5f) < scene.bottomBound + scene.rightPaddle.transform.scale.y - botOffset) {
			scene.rightPaddle.transform.position.y = (scene.bottomBound + scene.rightPaddle.transform.scale.y * 0.5f) - botOffset;
			scene.rightPaddle.transform.velocity = vec3(0.0f, 0.0f, 0.0f);
		}

		float topOffset = 0.05f;
		if (scene.rightPaddle.transform.position.y + (scene.rightPaddle.transform.scale.y * 0.5f) > scene.topBound + topOffset) {
			scene.rightPaddle.transform.position.y = (scene.topBound - scene.rightPaddle.transform.scale.y * 0.5f) + topOffset;
			scene.rightPaddle.transform.velocity = vec3(0.0f, 0.0f, 0.0f);
		}

	}

	void Scene::RunPaddlePositionConstraints() {
		scene.RunLeftPaddlePositionConstraints();
		scene.RunRightPaddlePositionConstraints();

	}

	void Scene::RunPaddleCollision() {
		scene.RunLeftPaddleCollision();
		scene.RunRightPaddleCollision();
	}

	void Scene::InitScene() {
		GLuint vertexArrayID = NULL;
		glGenVertexArrays(1, &vertexArrayID);
		glBindVertexArray(vertexArrayID);

		// Create and compile glsl from shaders.
		gameOptions.programID = Load::LoadShaders("BasicVertexShader.vertexshader", "BasicFragmentShader.fragmentshader");

		matrix.MVPMatrixID = glGetUniformLocation(gameOptions.programID, "MVP");

		matrix.projectionMatrix = perspective(FIELD_OF_VIEW, gameOptions.aspectRatio, Z_NEAR, Z_FAR);

		scene.leftPaddle = Object(gameOptions.leftPaddlePosition, gameOptions.paddleScale, Load::LoadColor(vec3(1.0f, 1.0f, 1.0f)), Load::LoadQuad());
		scene.rightPaddle = Object(gameOptions.rightPaddlePosition, gameOptions.paddleScale, Load::LoadColor(vec3(1.0f, 1.0f, 1.0f)), Load::LoadQuad());
		scene.ball = Object(gameOptions.ballPosition, gameOptions.ballScale, Load::LoadColor(vec3(1.0f, 1.0f, 1.0f)), Load::LoadQuad());

	}

	int Scene::InitializePong() {
		if (GL_Init::InitWindow() | GL_Init::InitGlew()) {
			return EXIT_WITH_ERROR;
		}
		scene.InitScene();
		//scene.ball.transform.velocity = gameOptions.startingBallVelocity;
		/*scene.leftPaddle.transform.position = vec3(-2.0f, 0.0, 0.0f);
		scene.rightPaddle.transform.position = vec3(2.0f, 0.0, 0.0f);*/
	}

	void Scene::RunBallBehavior() {
		if (scene.isGameRunning && !scene.ballVelocityInitialized) {
			//scene.ball.transform.velocity = gameOptions.startingBallVelocity;
			scene.ball.transform.velocity = DecideStartingBallDirection();
			scene.ballVelocityInitialized = true;
		}
		else if (!scene.isGameRunning) {
			scene.ball.transform.position = gameOptions.startingPos;
			scene.ball.transform.velocity = vec3(0.0f, 0.0f, 0.0f);

		}
	}

	int Scene::MainLoop() {
		do {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//fprintf(stdout, "Delta Time: %f", getDeltaTime()); 
			gameOptions.deltaTime = Utility::getDeltaTime();

			if (!scene.initializedPong) {
				if (scene.InitializePong() == EXIT_WITH_ERROR) return EXIT_WITH_ERROR;
				scene.initializedPong = true;
			}

			glUseProgram(gameOptions.programID);

			// camera matrix
			matrix.viewMatrix = glm::lookAt(
				vec3(0, 0, 3),		// position
				vec3(0, 0, 0),		// look at
				vec3(0, 1, 0)		// up
				);

			keyboard.RunKeyboardKeys();

			scene.RunGameTimer();
			scene.RunBallBehavior();
			scene.ball.Run();
			scene.leftPaddle.Run();
			scene.rightPaddle.Run();
			scene.RunBallConstraints();
			scene.RunPaddleCollision();
			scene.RunPaddleControls();
			scene.RunPaddlePositionConstraints();

			//Update();
			//Render();
			glfwSwapBuffers(gameOptions.window);
			glfwPollEvents();

		} while (glfwGetKey(gameOptions.window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(gameOptions.window) == 0);
	}
}scene;

///////////////////////////////////////////////////////////////////////////////
// main
int main() {
	srand(time(NULL));
	if (scene.MainLoop() == EXIT_WITH_ERROR) return EXIT_WITH_ERROR;

	return EXIT_WITH_SUCCESS;
}