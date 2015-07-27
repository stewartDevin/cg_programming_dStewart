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

	this->transform.position += this->transform.velocity * DataCore::deltaTime;
	//this->transform.angle += this->transform.rotationSpeed * DataCore::deltaTime;

	this->RenderMesh();

	this->MVPMatrix = camera->projectionMatrix * camera->viewMatrix * this->positionMatrix;

	glUniformMatrix4fv(camera->MVPMatrixID, 1, GL_FALSE, &this->MVPMatrix[0][0]);

}

void Mesh::LoadMesh() {

}

Mesh* Mesh::CreateMeshObject(const char* objFilePath, Material material, Transform transform) {
	//Load::_LoadTexture(&material.diffuseImageID, material.diffuseImageFilePath);
	Mesh* mesh = new Mesh(objFilePath, material);

	OBJ_Loader::LoadOBJ(objFilePath, mesh->verticesBuffer, mesh->uvsBuffer, mesh->normalsBuffer);
	mesh->numIndices = mesh->verticesBuffer.size();
	mesh->verticesBufferID = Load::_LoadVertsMesh(mesh->verticesBuffer);
	mesh->uvsBufferID = Load::_LoadUVsMesh(mesh->uvsBuffer);
	mesh->normalsBufferID = Load::_LoadNormalsMesh(mesh->normalsBuffer);
	mesh->transform = transform;
	Scene::listOfObjects.push_back(mesh);

	return mesh;
}

Mesh* Mesh::CreateMeshObjectDontPush(const char* objFilePath, Material material, Transform transform) {
	//Load::_LoadTexture(&material.diffuseImageID, material.diffuseImageFilePath);
	Mesh* mesh = new Mesh(objFilePath, material);

	OBJ_Loader::LoadOBJ(objFilePath, mesh->verticesBuffer, mesh->uvsBuffer, mesh->normalsBuffer);
	mesh->numIndices = mesh->verticesBuffer.size();
	mesh->verticesBufferID = Load::_LoadVertsMesh(mesh->verticesBuffer);
	mesh->uvsBufferID = Load::_LoadUVsMesh(mesh->uvsBuffer);
	mesh->normalsBufferID = Load::_LoadNormalsMesh(mesh->normalsBuffer);
	mesh->transform = transform;
	//Scene::listOfObjects.push_back(mesh);

	return mesh;
}

glm::mat4 Mesh::RenderMesh() {
	
		// Enable blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

		//mat4 positionMatrix = Render::RenderVertex(this->verticesBufferID, this->transform);
		this->positionMatrix = Render::RenderVertex(this->verticesBufferID, this->transform);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->material.diffuseImageID);
		glCullFace(GL_BACK);

		if (this->uvsBufferID != NULL) {
			Render::RenderUVs(this->uvsBufferID);
		}

		if (this->normalsBufferID != NULL) {
			Render::RenderNormals(this->normalsBufferID);
		}

		GLuint gl_location = glGetUniformLocation(DataCore::programID, "myTextureSampler");
		glUniform1i(gl_location, 0);

		glDrawArrays(GL_TRIANGLES, 0, this->numIndices);
		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);

		//return positionMatrix;
		return this->positionMatrix;
	

}