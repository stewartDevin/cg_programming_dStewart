// CORE.Render.cpp
//////////////////////////////////////////////////////////////////////////

#include "CORE.Render.h"
#include "CORE.BufferObject.h"
#include "../APP/APP.DataCore.h"
#include "CORE.Mesh.h"
#include "CORE.Transform.h"

//float num = 0.0f;

///////////////////////////////////////////////////////////////////////////////
// Render
void Render::RenderVertex(GLuint vertexBuffer) {
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

	//num += 1.0f * DataCore::deltaTime;
	
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

void Render::RenderNormals(GLuint normalBuffer) {
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);

	glVertexAttribPointer(
		3,			// attribute layout
		3,			// how many elements in array? 
		GL_FLOAT,   // what datatype?
		GL_FALSE,   // normalized?
		0,			// stride...
		(void*)0	// array buffer offset...
		);
}

//glm::mat4 Render::RenderQuad(BufferObject* bufferObject, const vec3& position, const vec3& scaleVec, const GLuint& textureID) {
//	// Enable blending
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
//
//	mat4 positionMatrix = RenderVertex(bufferObject->vertexBuffer, position, scaleVec);
//
//	//RenderColor(colorBuffer);
//
//	if (bufferObject->vertexColorBuffer != NULL) {
//		RenderColor(bufferObject->vertexColorBuffer);
//	}
//	if (bufferObject->uvBuffer != NULL) {
//		RenderUVs(bufferObject->uvBuffer);
//	}
//
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	glCullFace(GL_BACK);
//
//	GLuint gl_location = glGetUniformLocation(DataCore::programID, "diffuseTexture1");
//	glUniform1i(gl_location, 0);
//
//	glDrawArrays(GL_TRIANGLES, 0, 500000);
//	glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
//	glDisableVertexAttribArray(2);
//	
//	return positionMatrix;
//}

void Render::RenderQuad(Mesh* mesh) {
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

	RenderVertex(mesh->verticesBufferID);

	//RenderColor(colorBuffer);

	/*if (gameObj->bufferObject.vertexColorBuffer != NULL) {
		RenderColor(gameObj->bufferObject.vertexColorBuffer);
		}*/
	if (mesh->uvsBufferID != NULL) {
		RenderUVs(mesh->uvsBufferID);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->material.diffuseImageID[0]);
	glCullFace(GL_BACK);

	//GLuint gl_location = glGetUniformLocation(DataCore::programID, "diffuseTexture1");
	//glUniform1i(gl_location, 0);

	/*glDrawArrays(GL_TRIANGLES, 0, mesh->numIndices);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);*/


}

