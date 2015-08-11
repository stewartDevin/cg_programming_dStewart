// CORE.OBJ_Loader.cpp
//////////////////////////////////////////////////////////////

#include "CORE.OBJ_Loader.h"

bool OBJ_Loader::LoadOBJ(
	const char * path,
	std::vector < glm::vec3 > & out_vertices,
	std::vector < glm::vec2 > & out_uvs,
	std::vector < glm::vec3 > & out_normals
	) 
{
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file !\n");
		return false;
	}

	char line[256];
	char lineHeader[128];

	while(fgets(line, sizeof(line), file)){
		sscanf(line, "%s", lineHeader);

		//// read the first word of the line
		//int res = fscanf(file, "%s", lineHeader);
		//if (res == EOF)
		//	break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if ( strcmp( lineHeader, "v" ) == 0 ) {
			glm::vec3 vertex;
			sscanf(line, "%*s %f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			//fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);

		} else if ( strcmp( lineHeader, "vt" ) == 0 ) {
			glm::vec2 uv;
			sscanf(line, "%*s %f %f\n", &uv.x, &uv.y );
			//fscanf(file, "%f %f\n", &uv.x, &uv.y );
			temp_uvs.push_back(uv);

		} else if ( strcmp( lineHeader, "vn" ) == 0 ) {
			glm::vec3 normal;
			//fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			sscanf(line, "%*s %f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);

		} else if ( strcmp( lineHeader, "f" ) == 0 ) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];

			//int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );

			//int matches = sscanf(line, "%*s %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n" );

			// look for quads.
			int matches = sscanf(line, "%*s %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1],
				&uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3] );

			bool quads = true;

			// if it's not in quads...
			if (matches != 12){
				// look for tri's.
				matches = sscanf(line, "%*s %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1],
					&uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
				quads = false;

				// if it's still wrong, it must not have UV's.
				if(matches != 9) {
					// check for quads on no UV obj.
					matches = sscanf(line, "%*s %d//%d %d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1],
						&normalIndex[1], &vertexIndex[2], &normalIndex[2], &vertexIndex[3], &normalIndex[3] );
					quads = true;

					if(matches != 8) {
						// no UV's tri's obj
						matches = sscanf(line, "%*s %d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1],
							&normalIndex[1], &vertexIndex[2], &normalIndex[2] );
						quads = false;

						if(matches != 6) {
							printf("File can't be read by our simple parser : (Try exporting with other options) \n");
							return false;
						}
					}
				}
			}

			/*vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);*/

			if(matches == 12) {
				// quad with uv's
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);

				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[2]);
				vertexIndices.push_back(vertexIndex[3]);

				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);

				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[2]);
				uvIndices.push_back(uvIndex[3]);

				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);

				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[2]);
				normalIndices.push_back(normalIndex[3]);

			} 

			else if(matches == 9) {
				// tri's with uv's
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);

				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);

				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			} 

			else if(matches == 8) {
				// quad no uv's
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);

				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[2]);
				vertexIndices.push_back(vertexIndex[3]);

				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);

				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[2]);
				normalIndices.push_back(normalIndex[3]);
			}

			else if(matches == 6) {
				// tri's no uv's
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);

				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}
	}

	// For each vertex of each triangle
	//for(unsigned int i = 0; i < vertexIndices.size(); i++){
	//	unsigned int vertexIndex = vertexIndices[i];
	//	glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
	//	out_vertices.push_back(vertex);
	//}

	//// For each uv of each triangle
	//for(unsigned int i = 0; i < uvIndices.size(); i++){
	//	unsigned int uvIndex = uvIndices[i];
	//	glm::vec2 uv = temp_uvs[ uvIndex-1 ];
	//	out_uvs.push_back(uv);
	//}

	//// For each normal of each triangle
	//for(unsigned int i = 0; i < normalIndices.size(); i++){
	//	unsigned int normalIndex = normalIndices[i];
	//	glm::vec3 normal = temp_normals[ normalIndex-1 ];
	//	out_normals.push_back(normal);
	//}

	// For each vertex of each triangle
	for(unsigned int i=0, uvSize = (unsigned int)uvIndices.size(),
		normSize = (unsigned int)normalIndices.size(); i < vertexIndices.size(); ++i){

			out_vertices.push_back(temp_vertices[vertexIndices[i] - 1]);

			if(uvSize > 0)
				out_uvs.push_back(temp_uvs[uvIndices[i] - 1]);

			if(normSize > 0)
				out_normals.push_back(temp_normals[normalIndices[i] - 1]);
	}

	return true;
}

