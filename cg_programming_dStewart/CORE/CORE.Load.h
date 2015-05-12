// CORE.Load.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "../Application.h"

///////////////////////////////////////////////////////////////////////////////
// Load
static class Load {
public:
	static GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

	static GLuint& LoadQuad();

	static GLuint& LoadTriangle();

	static GLuint& LoadColor(vec3 rgb_color);

};