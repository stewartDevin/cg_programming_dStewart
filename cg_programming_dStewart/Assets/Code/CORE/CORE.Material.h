// CORE.Material.h
//////////////////////////////////////////////////////////////////
#pragma once

#include "../Application.h"

class Material {
public:

	// variables
	char* diffuseImageFilePath;
	char* specularImageFilePath;
	char* normalImageFilePath;

	GLuint diffuseImageID;
	GLuint specularImageID;
	GLuint normalImageID;
	GLuint shaderID;

	// constructor functions
	Material::Material(char* diffuseImageFilePath);
	Material::Material();

	// member functions

	// static functions
	static Material* CreateMaterial(char* diffuseImageFilePath);

};