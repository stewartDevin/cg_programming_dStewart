// CORE.Material.cpp
//////////////////////////////////////////////////////////////

#include "CORE.Material.h"
#include "CORE.Load.h"

Material::Material() {
	this->diffuseImageFilePath = NULL;
	this->specularImageFilePath = NULL;
	this->normalImageFilePath = NULL;

	this->diffuseImageID = NULL;
	this->specularImageID = NULL;
	this->normalImageID = NULL;
	this->shaderID = NULL;

	this->diffuseTiling = vec2(1.0f, 1.0f);
}

Material::Material(char* diffuseImageFilePath) {
	this->diffuseImageFilePath = diffuseImageFilePath;
	this->specularImageFilePath = NULL;
	this->normalImageFilePath = NULL;

	this->diffuseImageID = NULL;
	this->specularImageID = NULL;
	this->normalImageID = NULL;
	this->shaderID = NULL;

	this->diffuseTiling = vec2(1.0f, 1.0f);

	
}

Material* Material::CreateMaterial(char* diffuseImageFilePath) {
	Material* material = new Material(diffuseImageFilePath);
	Load::_LoadTexture(&material->diffuseImageID, material->diffuseImageFilePath);
	return material;
}

void Material::ApplyTiling() {
	GLint diffuseTextureTilingLocation = glGetUniformLocationARB(this->shaderID, "diffuseTiling");
	glUniform2fARB(diffuseTextureTilingLocation, this->diffuseTiling.x, this->diffuseTiling.y);

}


