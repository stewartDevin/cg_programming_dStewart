// CORE.Mesh.h
////////////////////////////////////////////////////////////////
#pragma once
#include "../Application.h"
#include "CORE.GameObject.h"
#include "CORE.Material.h"
#include "CORE.Transform.h"
#include "CORE.Camera.h"

class Mesh : public GameObject {
public:
	// variables
	const char* objFilePath;
	Material material;
	std::vector < glm::vec3 > verticesBuffer;
	std::vector < glm::vec2 > uvsBuffer;
	std::vector < glm::vec3 > normalsBuffer;
	GLuint verticesBufferID;
	GLuint uvsBufferID;
	GLuint normalsBufferID;

	// constructor functions
	Mesh::Mesh(const char* objFilePath, Material material);
	Mesh::Mesh();

	// member functions
	void Mesh::Run(Camera* camera);
	void Mesh::Init();
	void Mesh::CalculateMVPMatrix();
	void Mesh::SendMVPMatrixToShader(Camera* camera);
	void Mesh::SendMeshToShader();
	void Mesh::SendLayoutsAndUniformsToShader(Camera* camera);
	static Mesh* Mesh::CreateMeshObject(const char* objFilePath, Material material, Transform transform);
	static Mesh* Mesh::CreateMeshObjectDontPush(const char* objFilePath, Material material, Transform transform);
	
	void Mesh::RenderMesh();
};