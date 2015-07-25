// CORE.Render.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "../Application.h"
#include "../CORE/CORE.BufferObject.h"
#include "CORE.GameObject.h"
#include "CORE.Mesh.h"

///////////////////////////////////////////////////////////////////////////////
// Render
class Render {
public:
	static glm::mat4 RenderVertex(GLuint vertexBuffer, Transform& transform);

	static void RenderColor(GLuint vertexBuffer);

	//static void RenderTriangle(GLuint vertexBuffer, GLuint colorBuffer);

	//static glm::mat4 Render::RenderQuad(BufferObject* bufferObject, const vec3& position, const vec3& scaleVec, const GLuint& textureID);
	static glm::mat4 Render::RenderQuad(Mesh* mesh);

	static void Render::RenderUVs(GLuint vertexBuffer);

};