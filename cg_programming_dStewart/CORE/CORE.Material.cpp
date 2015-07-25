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

}

Material::Material(char* diffuseImageFilePath) {
	this->diffuseImageFilePath = diffuseImageFilePath;
	this->specularImageFilePath = NULL;
	this->normalImageFilePath = NULL;

	this->diffuseImageID = NULL;
	this->specularImageID = NULL;
	this->normalImageID = NULL;
}

Material* Material::CreateMaterial(char* diffuseImageFilePath) {
	Material* material = new Material(diffuseImageFilePath);
	Load::_LoadTexture(&material->diffuseImageID, material->diffuseImageFilePath);
	return material;
}