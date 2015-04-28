// MyShader.cpp
//////////////////////////////////////////////////////////////////////////

#include "MyShader.h"

class MyShader {
public:

	static GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {
		GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		//Read in shader code here.
		string vertexShaderCode = "";
		ifstream vertexShaderStream(vertex_file_path, ios::in);

		if(vertexShaderStream.is_open()) {
			string line = "";
			while(getline(vertexShaderStream, line)) {
				vertexShaderCode += "\n" + line;
			}

			vertexShaderStream.close();
		}

		string fragmentShaderCode = "";
		ifstream fragmentShaderStream(fragment_file_path, ios::in);

		if(fragmentShaderStream.is_open()) {
			string line = "";
			while(getline(fragmentShaderStream, line)) {
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

	GLuint& LoadQuad() {
		float offset = 0.5f;

		static GLfloat g_vertex_buffer_data[] = {
			0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f,

			0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		};

		for(int n = 0, size = 18; n < size;n++) {
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
			0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 0.0f
		};

		GLuint vertexBuffer = 0;
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

		return vertexBuffer;
	}

	static mat4 RenderVertex(GLuint vertexBuffer,  const vec3& position, const vec3& scaleVec) {
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

	mat4 RenderQuad(GLuint vertexBuffer, const vec3& position, GLuint colorBuffer, const vec3& scaleVec) {
		mat4 positionMatrix = RenderVertex(vertexBuffer, position, scaleVec);

		//positionMatrix *= identity;

		//RenderVertex(vertexBuffer);
		RenderColor(colorBuffer);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(0);
		return positionMatrix;
	}
};