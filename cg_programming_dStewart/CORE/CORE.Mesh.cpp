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
	
}

Mesh::Mesh() {

	this->objFilePath = NULL;
	this->material = NULL;
	this->verticesBufferID = NULL;
	this->uvsBufferID = NULL;
	this->normalsBufferID = NULL;
}

void Mesh::Run(Camera* camera) {
	if (!this->initialized) {
		this->Init();
		this->initialized = true;
	}

	//this->MVPMatrix = camera->projectionMatrix * camera->viewMatrix * Render::RenderQuad(&this->bufferObject, this->transform.position, this->transform.scale, this->textureID);
	this->MVPMatrix = camera->projectionMatrix * camera->viewMatrix * Render::RenderQuad(this);
	glUniformMatrix4fv(camera->MVPMatrixID, 1, GL_FALSE, &this->MVPMatrix[0][0]);

	this->transform.position += this->transform.velocity * DataCore::deltaTime;
	//this->transform.angle += this->transform.rotationSpeed * DataCore::deltaTime;

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
	mesh->transform = transform;
	Scene::listOfObjects.push_back(mesh);
	return mesh;
}