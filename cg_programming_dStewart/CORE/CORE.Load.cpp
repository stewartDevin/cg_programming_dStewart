// CORE.Load.cpp
//////////////////////////////////////////////////////////////////////////
#include "CORE.Load.h"
#include "../APP/APP.DataCore.h"

///////////////////////////////////////////////////////////////////////////////
// Load

unsigned char Load::FindChar(const char* buffer, const char& c) {
	// TODO: Search for char c, if found, return true.
	char* value = (char*)buffer;
	unsigned char length = 0;

	while(*value != '\0') {
		++length;
		
		if(*value == c) {
			return length;
		}
		value++;
	}

	return length = 0;
}

string Load::LoadFile(char* str) {
	string line;
	ifstream myfile (str);
	char* path = NULL;

	unsigned char len = 0;
	if (myfile.is_open())
	{
		char buffer[256];
		char path[256];

		while (getline(myfile, line))
		{
			line.copy(buffer, len = line.length());
			buffer[len] = '\0';

			unsigned char commaLength = FindChar(buffer, ',');

			if(buffer[0] > 47 && buffer[0] < 58) {
				// TODO: add level data...
				continue;
			}

			if(buffer[0] == 32 || buffer[0] == '\0') {
				// empty space
				continue;
			}

			if(buffer[0] == 35) {
				// TODO: get next count
				continue;
			}

			if(commaLength > 0) {
				strcpy(path, buffer);
				path[commaLength - 1] = '\0';

				continue;
				// TODO: Add texture data...
			}

			// load textures...
			cout << line << '\n';
		}
		myfile.close();
	} else cout << "Unable to open file";

	return line;
}

GLuint Load::LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {
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

GLuint& Load::LoadUVs() {

	GLfloat g_UV_buffer_data[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	GLuint uvbuffer = 0;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_UV_buffer_data), g_UV_buffer_data, GL_STATIC_DRAW);

	return uvbuffer;
}

GLuint& Load::LoadQuad() {
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

GLuint& Load::LoadTriangle() {
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

GLuint& Load::LoadColor(vec3 rgb_color) {
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