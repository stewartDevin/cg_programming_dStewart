// CORE.Render.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "../Application.h"

///////////////////////////////////////////////////////////////////////////////
// Render
static class Render {
public:
	static glm::mat4 RenderVertex(GLuint vertexBuffer, const vec3& position, const vec3& scaleVec);

	static void RenderColor(GLuint vertexBuffer);

	//static void RenderTriangle(GLuint vertexBuffer, GLuint colorBuffer);

	static glm::mat4 RenderQuad(GLuint vertexBuffer, const vec3& position, GLuint colorBuffer, const vec3& scaleVec);

	static glm::mat4 RenderQuad(GLuint vertexBuffer, const vec3& position, const vec3& scaleVec);

};