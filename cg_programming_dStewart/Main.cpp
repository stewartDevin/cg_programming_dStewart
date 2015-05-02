// Main.cpp
////////////////////////////////////////////////////////////////////////

#include "Application.h"

//glm::mat4 RenderQuad(GLuint vertexBuffer, const vec3& position, GLuint colorBuffer, const vec3& scaleVec);


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
	vec3 ballVelocity;
	vec3 startingBallVelocity;
	float paddleWidth;
	float gameTimer;

	GameOptions::GameOptions() {
		this->aspectRatio = SCREEN_WIDTH / (float)SCREEN_HEIGHT;
		//this->programID = glCreateProgram();
		this->paddleScale = vec3(0.1f, 1.0f, 1.0f);
		this->ballScale = vec3(0.1f, 0.1f, 1.0f);

		this->window = NULL;
		this->deltaTime = 0.0f;
		this->ballPosition = vec3(0.0f, 0.0f, 0.0f);
		this->leftPaddlePosition = vec3(-2.0f, 0.0f, 0.0f);
		this->rightPaddlePosition = vec3(2.0f, 0.0f, 0.0f);

		this->startingPos = vec3(0.0f, 0.0f, 0.0f);
		this->ballVelocity = vec3(0.0f, 0.0f, 0.0f);
		this->startingBallVelocity = vec3(1.0f, 0.0f, 0.0f);
		this->paddleWidth = 5.0f;

		this->gameTimer = 0.0f;
	}

}gameOptions;



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

};

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

} keyboard;

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

static class Scene {
public:
	bool initializedPong;
	Object leftPaddle;
	Object rightPaddle;
	Object ball;

	Scene::Scene() {
		this->initializedPong = false;
	}

	static void InitializePong() {

		scene.ball.transform.velocity = gameOptions.startingBallVelocity;
		scene.leftPaddle.transform.position = vec3(-2.0f, 0.0, 0.0f);
		scene.rightPaddle.transform.position = vec3(2.0f, 0.0, 0.0f);
	}

	static void RunBallConstraints() {

		float left = -2.6f;
		float right = 2.6f;
		float top = 1.9f;
		float bottom = -1.9f;

		if (scene.ball.transform.position.x <= left) {
			scene.ball.transform.position.x = left;
			scene.ball.transform.velocity = Utility::CalculateReflectionVector(Utility::NormalizeVector3(scene.ball.transform.velocity), vec3(1.0f, 0.0f, 0.0f));
			//ball.transform.velocity.x = -ball.transform.velocity.x;
		}
		if (scene.ball.transform.position.x >= right) {
			scene.ball.transform.position.x = right;
			scene.ball.transform.velocity = Utility::CalculateReflectionVector(Utility::NormalizeVector3(scene.ball.transform.velocity), vec3(-1.0f, 0.0f, 0.0f));
			//ball.transform.velocity.x = -ball.transform.velocity.x;
		}
		if (scene.ball.transform.position.y >= top) {
			scene.ball.transform.position.y = top;
			scene.ball.transform.velocity = Utility::CalculateReflectionVector(Utility::NormalizeVector3(scene.ball.transform.velocity), vec3(0.0f, -1.0f, 0.0f));

		}
		if (scene.ball.transform.position.y <= bottom) {
			scene.ball.transform.position.y = bottom;
			scene.ball.transform.velocity = Utility::CalculateReflectionVector(Utility::NormalizeVector3(scene.ball.transform.velocity), vec3(0.0f, 1.0f, 0.0f));

		}
	}

}scene;



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

	static GLuint& LoadColor() {
		static const GLfloat g_color_buffer_data[] = {
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f
		};

		GLuint vertexBuffer = 0;
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

		return vertexBuffer;
	}

};

int main() {
	if (GL_Init::InitWindow() | GL_Init::InitGlew()) {
		return EXIT_WITH_ERROR;
	}

	GLuint vertexArrayID = NULL;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	// Create and compile glsl from shaders.
	gameOptions.programID = Load::LoadShaders("BasicVertexShader.vertexshader", "BasicFragmentShader.fragmentshader");

	matrix.MVPMatrixID = glGetUniformLocation(gameOptions.programID, "MVP");

	//mat4 projectionMatrix = perspective(FIELD_OF_VIEW, gameOptions.aspectRatio, Z_NEAR, Z_FAR);
	matrix.projectionMatrix = perspective(FIELD_OF_VIEW, gameOptions.aspectRatio, Z_NEAR, Z_FAR);

	//GLuint triangleID = LoadTriangle();
	//GLuint ballID = LoadQuad();
	//GLuint colorID = LoadColor();
	scene.leftPaddle = Object(gameOptions.leftPaddlePosition, gameOptions.paddleScale, Load::LoadColor(), Load::LoadQuad());
	scene.rightPaddle = Object(gameOptions.rightPaddlePosition, gameOptions.paddleScale, Load::LoadColor(), Load::LoadQuad());
	scene.ball = Object(gameOptions.ballPosition, gameOptions.ballScale, Load::LoadColor(), Load::LoadQuad());
	

	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//fprintf(stdout, "Delta Time: %f", getDeltaTime()); 
		gameOptions.deltaTime = Utility::getDeltaTime();

		if (!scene.initializedPong) {
			scene.InitializePong();
			scene.initializedPong = true;
		}

		glUseProgram(gameOptions.programID);

		// camera matrix
		matrix.viewMatrix = glm::lookAt(
			vec3(0, 0, 3),		// position
			vec3(0, 0, 0),		// look at
			vec3(0, 1, 0)		// up
			);

		//RenderTriangle(triangleID, colorID);
		//RunBallMovement();

		scene.ball.Run();
		scene.leftPaddle.Run();
		scene.rightPaddle.Run();
		scene.RunBallConstraints();

		//Update();
		//Render();
		glfwSwapBuffers(gameOptions.window);
		glfwPollEvents();

	} while (glfwGetKey(gameOptions.window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(gameOptions.window) == 0);

	//Object::DeleteObject(&leftPaddle);
	//Object::DeleteObject(&rightPaddle);

	return EXIT_WITH_SUCCESS;
}















































//// Init GLFW
//if (!glfwInit()) {
//	fprintf(stderr, "Failed to init GLFW\n");
//	return -1;
//}

//glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

//// Open a window and create its OpenGL context 
//GLFWwindow* window; // (In the accompanying source code, this variable is global) 
//window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL); 
//if( window == NULL ){
//	fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
//	glfwTerminate();
//	return -1;
//}
//glfwMakeContextCurrent(window); // Initialize GLEW 
//glewExperimental=true; // Needed in core profile 
//if (glewInit() != GLEW_OK) {
//	fprintf(stderr, "Failed to initialize GLEW\n");
//	return -1;
//}

//// Ensure we can capture the escape key being pressed below
//glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

//GLuint VertexArrayID;
//glGenVertexArrays(1, &VertexArrayID);
//glBindVertexArray(VertexArrayID);

//// An array of 3 vectors which represents 3 vertices
//static const GLfloat g_vertex_buffer_data[] = {
//	-1.0f, -1.0f, 0.0f,
//	1.0f, -1.0f, 0.0f,
//	0.0f,  1.0f, 0.0f,
//};

//// This will identify our vertex buffer
//GLuint vertexbuffer;

//// Generate 1 buffer, put the resulting identifier in vertexbuffer
//glGenBuffers(1, &vertexbuffer);

//// The following commands will talk about our 'vertexbuffer' buffer
//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

//// Give our vertices to OpenGL.
//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


//// on frame
//do{
//	// Draw nothing, see you in tutorial 2 !
//	// 1rst attribute buffer : vertices
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//	glVertexAttribPointer(
//		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
//		3,                  // size
//		GL_FLOAT,           // type
//		GL_FALSE,           // normalized?
//		0,                  // stride
//		(void*)0            // array buffer offset
//		);

//	// Draw the triangle !
//	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

//	glDisableVertexAttribArray(0);
//	// Swap buffers
//	glfwSwapBuffers(window);
//	glfwPollEvents();

//} // Check if the ESC key was pressed or the window was closed
//while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
//	glfwWindowShouldClose(window) == 0 );

///////////////////////////////////////////////////////////////////////////////////////////////
