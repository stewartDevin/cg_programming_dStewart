// CORE.Load.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "../Application.h"

///////////////////////////////////////////////////////////////////////////////
// Load
class Load {
public:
	static GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
	static GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path, const char* geometry_file_path);
	static void LoadFile(char* str);

	static GLuint LoadQuad();
	static GLuint LoadCube();
	static GLuint LoadUVs();
	static GLuint LoadCubeUVs();

	static GLuint LoadTriangle();

	static GLuint LoadColor(vec3 rgb_color);
	static unsigned char FindChar(const char* buffer, const char& c);

	static void _LoadTexture(GLuint* texture, char* path);
	static void __LoadTexture(char* filePath);

	static GLuint _LoadVertsMesh(std::vector < glm::vec3 >& verticesBuffer);
	static GLuint _LoadUVsMesh(std::vector < glm::vec2 >& uvBuffer);
	static GLuint _LoadNormalsMesh(std::vector < glm::vec3 >& normalBuffer);

};