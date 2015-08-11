// CORE.OBJ_Loader.h
//////////////////////////////////////////////////////////////////
#pragma once

#include "../Application.h"

class OBJ_Loader {
public:
	static bool LoadOBJ(
		const char * path,
		std::vector < glm::vec3 > & out_vertices,
		std::vector < glm::vec2 > & out_uvs,
		std::vector < glm::vec3 > & out_normals
		); 

	
};