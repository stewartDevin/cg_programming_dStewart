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

void Mesh::Run(Camera* camera) {
	if (!this->initialized) {
		this->Init();
		this->initialized = true;
	}
	
	//glUseProgram(DataCore::programID);
	glUseProgram(this->material.shaderID);
	camera->SendVariablesToShader(this->material.shaderID);

	this->transform.position += this->transform.velocity * DataCore::deltaTime;
	//this->transform.angle += this->transform.rotationSpeed * DataCore::deltaTime;

	this->RenderMesh();

	mat4 M_Matrix = this->positionMatrix;
	//GLuint MV_Matrix_ID = glGetUniformLocation(DataCore::programID, "MV");
	GLuint M_Matrix_ID = glGetUniformLocation(this->material.shaderID, "M_Matrix");
	glUniformMatrix4fv(M_Matrix_ID, 1, GL_FALSE, &M_Matrix[0][0]);

	this->MVP_MatrixID = glGetUniformLocation(this->material.shaderID, "MVP");
	this->MVPMatrix = camera->projectionMatrix * camera->viewMatrix * this->positionMatrix;
	glUniformMatrix4fv(this->MVP_MatrixID, 1, GL_FALSE, &this->MVPMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, this->numIndices);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}

void Mesh::LoadMesh() {

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
		//printf("Mesh didn't load properly.\n");
		return NULL;
	}
}

Mesh* Mesh::CreateMeshObject(const char* objFilePath, Material material, Transform transform) {
	Mesh* mesh = Mesh::CreateMeshObjectDontPush(objFilePath, material, transform);
	DataCore::listOfObjects.push_back(mesh);
	return mesh;
}

glm::mat4 Mesh::RenderMesh() {

	glUseProgram(this->material.shaderID);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

	//mat4 positionMatrix = Render::RenderVertex(this->verticesBufferID, this->transform);
	this->positionMatrix = Render::RenderVertex(this->verticesBufferID, this->transform);

	this->material.SendTexturesToVideoCard();
	this->material.ApplyTiling();

	if (this->uvsBufferID != NULL) {
		Render::RenderUVs(this->uvsBufferID);
	}

	if (this->normalsBufferID != NULL) {
		Render::RenderNormals(this->normalsBufferID);
	}

	//return positionMatrix;
	return this->positionMatrix;


}