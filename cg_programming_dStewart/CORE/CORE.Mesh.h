// CORE.Mesh.h
////////////////////////////////////////////////////////////////
#pragma once
#include "../Application.h"
#include "CORE.GameObject.h"

class Mesh : GameObject {
public:
	// variables
	const char* objFilePath;
	std::vector < glm::vec3 > & verticesBuffer;
	std::vector < glm::vec2 > & uvsBuffer;
	std::vector < glm::vec3 > & normalsBuffer;

	// constructor functions
	Mesh::Mesh(const char* objFilePath);

	// member functions
	void Run(Camera* camera);

};