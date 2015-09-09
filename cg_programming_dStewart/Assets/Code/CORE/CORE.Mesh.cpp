// CORE.Mesh.cpp
/////////////////////////////////////////////////////////////

#include "CORE.Mesh.h"
#include "CORE.Render.h"
#include "..\APP\APP.DataCore.h"
#include "CORE.Load.h"
#include "CORE.Material.h"
#include "CORE.Transform.h"
#include "..\APP\APP.Scene.h"
#include "CORE.OBJ_Loader.h"

Mesh::Mesh(const char* objFilePath, Material material) {
	this->objFilePath = objFilePath;
	this->material = material;
	this->verticesBufferID = NULL;
	this->uvsBufferID = NULL;
	this->normalsBufferID = NULL;
	this->positionMatrix = mat4(1.0f);
}

Mesh::Mesh() {

	this->objFilePath = NULL;
	this->material = NULL;
	this->verticesBufferID = NULL;
	this->uvsBufferID = NULL;
	this->normalsBufferID = NULL;
	this->positionMatrix = mat4(1.0f);
}

void Mesh::SendMVPMatrixToShader(Camera* camera) {
	////////////////////////////////////////////////////
	// MVP_MATRIX
	this->MVP_MatrixID = glGetUniformLocation(this->material.shaderID, "MVP");
	this->MVPMatrix = camera->projectionMatrix * camera->viewMatrix * this->positionMatrix;
	glUniformMatrix4fv(this->MVP_MatrixID, 1, GL_FALSE, &this->MVPMatrix[0][0]);

	///////////////////////////////////////////////////
	// M_MATRIX
	mat4 M_Matrix = this->positionMatrix;
	//GLuint MV_Matrix_ID = glGetUniformLocation(DataCore::programID, "MV");
	GLuint M_Matrix_ID = glGetUniformLocation(this->material.shaderID, "M_Matrix");
	glUniformMatrix4fv(M_Matrix_ID, 1, GL_FALSE, &M_Matrix[0][0]);

	///////////////////////////////////////////////////
	// V_MATRIX
	mat4 V_Matrix = camera->viewMatrix;
	//GLuint MV_Matrix_ID = glGetUniformLocation(DataCore::programID, "MV");
	GLuint V_Matrix_ID = glGetUniformLocation(this->material.shaderID, "V_Matrix");
	glUniformMatrix4fv(V_Matrix_ID, 1, GL_FALSE, &V_Matrix[0][0]);

	////////////////////////////////////////////////////
	// P_MATRIX
	mat4 P_Matrix = camera->projectionMatrix;
	GLuint P_Matrix_ID = glGetUniformLocation(this->material.shaderID, "P_Matrix");
	glUniformMatrix4fv(P_Matrix_ID, 1, GL_FALSE, &P_Matrix[0][0]);

}

void Mesh::Init() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
}

void Mesh::Run(Camera* camera) {
	if (!this->initialized) {
		this->Init();
		this->initialized = true;
	}
	
	glUseProgram(this->material.shaderID);

	this->transform.ApplyVelocity();
	this->CalculateMVPMatrix();
	this->SendLayoutsAndUniformsToShader(camera);
	this->RenderMesh();
}

Mesh* Mesh::CreateMeshObjectDontPush(const char* objFilePath, Material material, Transform transform) {
	Mesh* mesh = new Mesh(objFilePath, material);

	bool success = OBJ_Loader::LoadOBJ(objFilePath, mesh->verticesBuffer, mesh->uvsBuffer, mesh->normalsBuffer);

	if(success) {
		//glUseProgram(material.shaderID);
		mesh->numIndices = mesh->verticesBuffer.size();
		mesh->transform = transform;

		if(mesh->verticesBuffer.size() > 0) {
			mesh->verticesBufferID = Load::_LoadVertsMesh(mesh->verticesBuffer);
		} else {
			printf("Mesh doesn't have any vertices.\n");
		}

		if(mesh->uvsBuffer.size() > 0) {
			mesh->uvsBufferID = Load::_LoadUVsMesh(mesh->uvsBuffer);
		} else {
			printf("Mesh doesn't have any UV's.\n");
		}

		if(mesh->normalsBuffer.size() > 0) {
			mesh->normalsBufferID = Load::_LoadNormalsMesh(mesh->normalsBuffer);
		} else {
			printf("Mesh doesn't have any normals.\n");
		}
		
		//Scene::listOfObjects.push_back(mesh);

		return mesh;
	} else {
		printf("obj didn't load properly.\n");
		return NULL;
	}
}

Mesh* Mesh::CreateMeshObject(const char* objFilePath, Material material, Transform transform) {
	Mesh* mesh = Mesh::CreateMeshObjectDontPush(objFilePath, material, transform);
	DataCore::listOfObjects.push_back(mesh);
	return mesh;
}

void Mesh::CalculateMVPMatrix() {
	mat4 modelToWorldMatrix = mat4(1.0f);

	mat4 identityMatrix = mat4(1.0f);
	mat4 scaleMatrix = glm::scale(identityMatrix, this->transform.scale);
	mat4 translateMatrix = glm::translate(identityMatrix, this->transform.position);
	mat4 rotationMatrix = glm::rotate(identityMatrix, this->transform.rotationAmount, this->transform.rotationAxis);
	
	if (this->transform.rotateAroundAxis) {
		modelToWorldMatrix = rotationMatrix * translateMatrix * scaleMatrix * identityMatrix;
	}
	else {
		modelToWorldMatrix = translateMatrix * rotationMatrix * scaleMatrix * identityMatrix;
	}

	this->positionMatrix = modelToWorldMatrix;
}

void Mesh::SendMeshToShader() {
	// get the position location
	GLint posLoc = glGetUniformLocationARB(this->material.shaderID, "position");
	// send the position to the Shader
	glUniform3fARB(posLoc, this->transform.position.x, this->transform.position.y, this->transform.position.z);

	if (this->verticesBufferID != NULL) {
		Render::RenderVertex(this->verticesBufferID);
	}

	if (this->uvsBufferID != NULL) {
		Render::RenderUVs(this->uvsBufferID);
	}

	if (this->normalsBufferID != NULL) {
		Render::RenderNormals(this->normalsBufferID);
	}
}

void Mesh::SendLayoutsAndUniformsToShader(Camera* camera) {
	glUseProgram(this->material.shaderID);
	this->SendMeshToShader();
	this->material.SendTexturesToShader();
	this->material.SendTextureTilingToShader();
	this->SendMVPMatrixToShader(camera);
	camera->SendCameraVariablesToShader(this->material.shaderID);
}

void Mesh::RenderMesh() {
	
	// draw the mesh in tri's
	glDrawArrays(GL_TRIANGLES, 0, this->numIndices);

	// disable layout locations
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}