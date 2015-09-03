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

//void Material::LoadTexture(char* diffuseImageFilePath, char* path) {
//	Load::_LoadTexture(&material->diffuseImageID[0], material->diffuseImageFilePath[0]);
//}

void Material::SendTextureTilingToShader() {
	glUseProgram(this->shaderID);
	GLint diffuseTextureTilingLocation = glGetUniformLocationARB(this->shaderID, "diffuseTiling");
	glUniform2fARB(diffuseTextureTilingLocation, this->diffuseTiling.x, this->diffuseTiling.y);

}

void Material::SendTexturesToShader() {

	for(int n = 0; n < 4; n++) {
		if(this->diffuseImageID[n] != NULL) {
			char buffer[32];
			memset(buffer, NULL, sizeof(buffer));
			strcpy (buffer,"diffuseTexture");
			std::string s = std::to_string(n);
			const char *cstr = s.c_str();
			strcat (buffer, cstr);

			GLuint gl_location = glGetUniformLocation(this->shaderID, buffer);
			glUniform1i(gl_location, n);

			glActiveTexture(GL_TEXTURE0 + n);
			glBindTexture(GL_TEXTURE_2D, this->diffuseImageID[n]);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}

		if(this->specularImageID[n] != NULL) {
			char buffer[32];
			memset(buffer, NULL, sizeof(buffer));
			strcpy (buffer,"specularTexture");
			std::string s = std::to_string(n);
			const char *cstr = s.c_str();
			strcat (buffer, cstr);
			GLuint gl_location = glGetUniformLocation(this->shaderID, buffer);
			glUniform1i(gl_location, n + 4);

			glActiveTexture(GL_TEXTURE0 + n + 4);
			glBindTexture(GL_TEXTURE_2D, this->specularImageID[n]);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}

		if(this->normalImageID[n] != NULL) {
			char buffer[32];
			memset(buffer, NULL, sizeof(buffer));
			strcpy (buffer,"normalTexture");
			std::string s = std::to_string(n);
			const char *cstr = s.c_str();
			strcat (buffer, cstr);
			GLuint gl_location = glGetUniformLocation(this->shaderID, buffer);
			glUniform1i(gl_location, n + 8);

			glActiveTexture(GL_TEXTURE0 + n + 8);
			glBindTexture(GL_TEXTURE_2D, this->normalImageID[n]);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}

		
	}

}


