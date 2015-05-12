// CORE.Render.cpp
//////////////////////////////////////////////////////////////////////////

#include "CORE.Render.h"

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

	void Render::RenderColor(GLuint vertexBuffer) {
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

	//void Render::RenderTriangle(GLuint vertexBuffer, GLuint colorBuffer) {
	//	RenderVertex(vertexBuffer);
	//	RenderColor(colorBuffer);
	//
	//	glDrawArrays(GL_TRIANGLES, 0, 3);
	//	glDisableVertexAttribArray(0);
	//	glDisableVertexAttribArray(1);
	//}

	glm::mat4 Render::RenderQuad(GLuint vertexBuffer, const vec3& position, GLuint colorBuffer, const vec3& scaleVec) {
		mat4 positionMatrix = RenderVertex(vertexBuffer, position, scaleVec);

		RenderColor(colorBuffer);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(0);
		return positionMatrix;
	}

	glm::mat4 Render::RenderQuad(GLuint vertexBuffer, const vec3& position, const vec3& scaleVec) {
		mat4 positionMatrix = RenderVertex(vertexBuffer, position, scaleVec);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(0);
		return positionMatrix;
	}