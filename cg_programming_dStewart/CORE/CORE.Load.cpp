// CORE.Load.cpp
//////////////////////////////////////////////////////////////////////////
#include "CORE.Load.h"
#include "../APP/APP.DataCore.h"
#include "../APP/APP.Scene.h"

///////////////////////////////////////////////////////////////////////////////
// Load

unsigned char Load::FindChar(const char* buffer, const char& c) {
	// TODO: Search for char c, if found, return true.
	char* value = (char*)buffer;
	unsigned char length = 0;

	while (*value != '\0') {
		++length;

		if (*value == c) {
			return length;
		}
		value++;
	}

	return length = 0;
}

static u16 GetNumCharCount(u8 *src) {
	u16 count = 0;
	while (IS_NUMBER(*src)) {
		++count;
		++src;
	}

	return count;
}

void Load::_LoadTexture(GLuint* texture, char* path){
	if (texture == NULL) return;
	GLuint n = SOIL_load_OGL_texture(path,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
		);
	*texture = n;
	if (*texture == NULL) {
		printf("[Texture loader] \"%s\" failed to load!\n", path);
	}
}

void Load::__LoadTexture(char* filePath) {
	GLuint textureID = NULL;
	Load::_LoadTexture(&textureID, filePath);
	DataCore::listOfTextures.push_back(textureID);
}

void Load::LoadFile(char* str) {
	static const u8 MAX_BUFFER_SIZE = 64;
	static const u8 MAX_PATH_SIZE = 32;

	char* levelBuffer = NULL;
	char* textureBuffer = NULL;
	u8 numTextures, levelWidth, levelHeight;

	//load world...
	ifstream myfile(str);

	char buffer[MAX_BUFFER_SIZE];
	memset(buffer, 0, sizeof buffer);

	char path[MAX_PATH_SIZE];
	memset(path, 0, sizeof path);

	if (myfile.is_open())
	{
		string line;
		unsigned char len = 0;

		bool loadLevelData = true;

		while (getline(myfile, line))
		{
			len = line.length();
			line.copy(buffer, len);
			buffer[len] = '\0';

			if (IS_EMPTY_LINE(buffer[0])){
				continue;
			}
			else if (LOAD_TEXTURE(buffer[0])){
				//Setting buffer size...
				// this is being handled by the amount of textures that get loaded...
				// continue...
				loadLevelData = false;
				continue;

				//numTextures = buffer[1] - ASCII_ZERO;
				//textureBuffer = (char*)malloc((sizeof (char)) * MAX_PATH_SIZE * numTextures);
				//memset(textureBuffer, 0, sizeof textureBuffer);
				//continue;
			}
			else if (LOAD_LEVELDATA(buffer[0])){
				//Setting buffer size...
				u8 widthCount = GetNumCharCount((u8*)&buffer[1]) + 1;

				levelWidth = std::stoi(&buffer[1]);
				levelHeight = std::stoi(&buffer[1 + widthCount]);

				DataCore::xAmountOfTiles = levelWidth;
				DataCore::yAmountOfTiles = levelHeight;

				levelBuffer = (char*)malloc(levelWidth * levelHeight);
				memset(levelBuffer, 0, sizeof levelBuffer);

				loadLevelData = true;
				continue;
			}
			else if (loadLevelData){
				//TODO: Load level data here...

				static int levelIndex = 0;
				static int xIndex = 1;
				static int yIndex = 1;
				static int textureIndexCounter = 0;
				u8 count = 0;

				for (int n = 0; count < levelWidth; ++n) {
					if (IS_NUMBER(buffer[n])) {
						levelBuffer[levelIndex++] = buffer[n];

						BufferObject bufferObj;
						bufferObj.vertexBuffer = Load::LoadQuad();
						bufferObj.uvBuffer = Load::LoadUVs();

						textureIndexCounter = levelIndex - 1;
						//if (textureIndexCounter < 0) textureIndexCounter = 0;
						int textureIndex = std::stoi(&levelBuffer[textureIndexCounter]);

						GameObject::CreateObject(
							vec3(DataCore::xTilePos + (xIndex * (DataCore::tileScale + DataCore::tileSpacing)), DataCore::yTilePos - (yIndex * (DataCore::tileScale + DataCore::tileSpacing)), 0.0f),
							vec3(DataCore::tileScale, DataCore::tileScale, 1.0f),
							bufferObj,
							DataCore::listOfTextures[textureIndex]);
						++count;
						++xIndex;
						if (xIndex == levelWidth) {
							xIndex = 0;
							yIndex++;
						}
						//continue;
					}

				}

			}

			unsigned char commaLen = FindChar(buffer, ',');


			//Found textures...
			if (commaLen > 0){
				strcpy_s(path, buffer);
				path[commaLen - 1] = '\0';

				char assetsFolder[256];
				memset(assetsFolder, 0, sizeof assetsFolder);
				strcat(assetsFolder, IMAGES_FOLDER_FILE_PATH);
				strcat(assetsFolder, path);

				__LoadTexture(assetsFolder);

				continue;
			}
		}

		free(textureBuffer);
		free(levelBuffer);
		myfile.close();
	}
	else cout << "Unable to open file";
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

GLuint Load::LoadUVs() {

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

GLuint Load::LoadCubeUVs() {

	static const GLfloat g_uv_buffer_data[] = {
    0.000059f, 1.0f-0.000004f,
    0.000103f, 1.0f-0.336048f,
    0.335973f, 1.0f-0.335903f,
    1.000023f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.336024f, 1.0f-0.671877f,
    0.667969f, 1.0f-0.671889f,
    1.000023f, 1.0f-0.000013f,
    0.668104f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.000059f, 1.0f-0.000004f,
    0.335973f, 1.0f-0.335903f,
    0.336098f, 1.0f-0.000071f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.336024f, 1.0f-0.671877f,
    1.000004f, 1.0f-0.671847f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.668104f, 1.0f-0.000013f,
    0.335973f, 1.0f-0.335903f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.668104f, 1.0f-0.000013f,
    0.336098f, 1.0f-0.000071f,
    0.000103f, 1.0f-0.336048f,
    0.000004f, 1.0f-0.671870f,
    0.336024f, 1.0f-0.671877f,
    0.000103f, 1.0f-0.336048f,
    0.336024f, 1.0f-0.671877f,
    0.335973f, 1.0f-0.335903f,
    0.667969f, 1.0f-0.671889f,
    1.000004f, 1.0f-0.671847f,
    0.667979f, 1.0f-0.335851f
};

	GLuint uvbuffer = 0;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	return uvbuffer;
}

GLuint Load::LoadQuad() {
	float offset = 0.5f;

	static GLfloat g_vertex_buffer_data[] = {
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

GLuint Load::LoadCube() {
	float offset = 0.5f;

	/*GLfloat g_vertex_buffer_data[] = {
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,

	0.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f
	};*/

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	/*for (int n = 0, size = 108; n < size; n++) {
		float &f = g_vertex_buffer_data[n];
		f -= offset;
		continue;
	}*/

	GLuint vertexBuffer = 0;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	return vertexBuffer;
}

GLuint Load::LoadTriangle() {
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

GLuint Load::LoadColor(vec3 rgb_color) {
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