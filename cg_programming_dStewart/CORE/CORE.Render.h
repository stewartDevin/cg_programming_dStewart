// CORE.Render.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "../Application.h"
#include "../CORE/CORE.BufferObject.h"
#include "CORE.GameObject.h"

///////////////////////////////////////////////////////////////////////////////
// Render
class Render {
public:
	static glm::mat4 RenderVertex(GLuint vertexBuffer, const vec3& position, const vec3& scaleVec);

	static void RenderColor(GLuint vertexBuffer);

	//static void RenderTriangle(GLuint vertexBuffer, GLuint colorBuffer);

	static glm::mat4 Render::RenderQuad(BufferObject* bufferObject, const vec3& position, const vec3& scaleVec, const GLuint& textureID);
	static glm::mat4 Render::RenderQuad(GameObject* gameObj);

	static void Render::RenderUVs(GLuint vertexBuffer);

};