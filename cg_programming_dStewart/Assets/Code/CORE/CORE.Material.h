// CORE.Material.h
//////////////////////////////////////////////////////////////////
#pragma once

#include "../Application.h"

class Material {
public:

	// variables
	char* diffuseImageFilePath[MAX_TEXTURES];
	char* specularImageFilePath[MAX_TEXTURES];
	char* normalImageFilePath[MAX_TEXTURES];

	GLuint diffuseImageID[MAX_TEXTURES];
	GLuint specularImageID[MAX_TEXTURES];
	GLuint normalImageID[MAX_TEXTURES];

	GLuint shaderID;

	vec2 diffuseTiling;

	// constructor functions
	Material::Material(char* diffuseImageFilePath);
	Material::Material();

	// member functions
	void ApplyTiling();

	// static functions
	static Material* CreateMaterial(char* diffuseImageFilePath);

};