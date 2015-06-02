// CORE.Render.cpp
//////////////////////////////////////////////////////////////////////////

#include "CORE.Render.h"
#include "CORE.BufferObject.h"

///////////////////////////////////////////////////////////////////////////////
// Render
glm::mat4 Render::RenderVertex(GLuint vertexBuffer, const vec3& position, const vec3& scaleVec) {
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

void Render::RenderColor(GLuint colorBuffer) {
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);

	glVertexAttribPointer(
		1,			// attribute layout
		3,			// how many elements in array? 
		GL_FLOAT,   // what datatype?
		GL_FALSE,   // normalized?
		0,			// stride...
		(void*)0	// array buffer offset...
		);
}

void Render::RenderUVs(GLuint uvBuffer) {
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);

	glVertexAttribPointer(
		2,			// attribute layout
		2,			// how many elements in array? 
		GL_FLOAT,   // what datatype?
		GL_FALSE,   // normalized?
		0,			// stride...
		(void*)0	// array buffer offset...
		);
}

glm::mat4 Render::RenderQuad(BufferObject* bufferObject, const vec3& position, const vec3& scaleVec) {
	mat4 positionMatrix = RenderVertex(bufferObject->vertexBuffer, position, scaleVec);

	//RenderColor(colorBuffer);

	if (bufferObject->vertexColorBuffer != NULL) {
		RenderColor(bufferObject->vertexColorBuffer);
	}
	if (bufferObject->uvBuffer != NULL) {
		RenderUVs(bufferObject->uvBuffer);
	}

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	return positionMatrix;
}

