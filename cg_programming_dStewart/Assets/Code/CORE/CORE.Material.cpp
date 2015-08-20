// CORE.Material.cpp
//////////////////////////////////////////////////////////////

#include "CORE.Material.h"
#include "CORE.Load.h"

Material::Material() {
	for(int n = 0; n < MAX_TEXTURES; n++) this->diffuseImageFilePath[n] = NULL;
	for(int n = 0; n < MAX_TEXTURES; n++) this->specularImageFilePath[n] = NULL;
	for(int n = 0; n < MAX_TEXTURES; n++) this->normalImageFilePath[n] = NULL;

	for(int n = 0; n < MAX_TEXTURES; n++) this->diffuseImageID[n] = NULL;
	for(int n = 0; n < MAX_TEXTURES; n++) this->specularImageID[n] = NULL;
	for(int n = 0; n < MAX_TEXTURES; n++) this->normalImageID[n] = NULL;
	this->shaderID = NULL;

	this->diffuseTiling = vec2(1.0f, 1.0f);
}

Material::Material(char* diffuseImageFilePath) {
	this->diffuseImageFilePath[0] = diffuseImageFilePath;
	for(int n = 1; n < MAX_TEXTURES; n++) this->diffuseImageFilePath[n] = NULL;
	for(int n = 0; n < MAX_TEXTURES; n++) this->specularImageFilePath[n] = NULL;
	for(int n = 0; n < MAX_TEXTURES; n++) this->normalImageFilePath[n] = NULL;

	for(int n = 0; n < MAX_TEXTURES; n++) this->diffuseImageID[n] = NULL;
	for(int n = 0; n < MAX_TEXTURES; n++) this->specularImageID[n] = NULL;
	for(int n = 0; n < MAX_TEXTURES; n++) this->normalImageID[n] = NULL;

	this->shaderID = NULL;

	this->diffuseTiling = vec2(1.0f, 1.0f);

}

Material* Material::CreateMaterial(char* diffuseImageFilePath) {
	Material* material = new Material(diffuseImageFilePath);
	Load::_LoadTexture(&material->diffuseImageID[0], material->diffuseImageFilePath[0]);
	return material;
}

void Material::ApplyTiling() {
	glUseProgram(this->shaderID);
	GLint diffuseTextureTilingLocation = glGetUniformLocationARB(this->shaderID, "diffuseTiling");
	glUniform2fARB(diffuseTextureTilingLocation, this->diffuseTiling.x, this->diffuseTiling.y);

}


