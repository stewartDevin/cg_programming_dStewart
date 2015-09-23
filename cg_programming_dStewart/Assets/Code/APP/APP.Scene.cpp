// APP.Scene.cpp
//////////////////////////////////////////////////////////////////////////

#include "../Application.h"
#include "../CORE/CORE.Utility.h"
#include "../CORE/CORE.Keyboard.h"
#include "../CORE/CORE.Matrix.h"
#include "../CORE/CORE.Load.h"
#include "../CORE/CORE.GL_Init.h"
#include "APP.Scene.h"
#include <vector>
#include "Pong\Pong.Options.h"
#include "Pong\Pong.Scene.h"
#include "APP.DataCore.h"
#include "..\CORE\CORE.Material.h"
#include "..\CORE\CORE.Mesh.h"
#include "..\CORE\CORE.Mouse.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Scene

bool Scene::sceneInitialized = false;

string Scene::loadedFile = "";
string Scene::loadedLevel = "";

//void LoadGrid() {
//	// load grid
//	/*float xPos = -2.4f;
//	float yPos = 1.8f;
//	float tileScale = 0.4f;
//	float tileSpacing = 0.0f;*/
//	int xTiles = 16;
//	int yTiles = 16;
//
//	int counter = 0;
//
//	for (int m = 0; m < yTiles; ++m) {
//		for (int n = 0; n < xTiles; ++n) {
//
//			BufferObject bufferObj;
//			bufferObj.vertexBuffer = Load::LoadQuad();
//			bufferObj.uvBuffer = Load::LoadUVs();
//
//			if (counter == 0) {
//				GameObject::CreateObject(
//					vec3(DataCore::xTilePos + (n * (DataCore::tileScale + DataCore::tileSpacing)), DataCore::yTilePos - (m * (DataCore::tileScale + DataCore::tileSpacing)), 0.0f),
//					vec3(DataCore::tileScale, DataCore::tileScale, 1.0f),
//					bufferObj,
//					DataCore::listOfTextures[0]);
//				counter = 1;
//				continue;
//			}
//
//			if (counter == 1) {
//				GameObject::CreateObject(
//					vec3(DataCore::xTilePos + (n * (DataCore::tileScale + DataCore::tileSpacing)), DataCore::yTilePos - (m * (DataCore::tileScale + DataCore::tileSpacing)), 0.0f),
//					vec3(DataCore::tileScale, DataCore::tileScale, 1.0f),
//					bufferObj,
//					DataCore::listOfTextures[1]);
//				counter = 0;
//				continue;
//			}
//
//
//		}
//	}
//
//}

void RunControls1(vec3& position, float const& speed) {
	if (Keyboard::Q) {
		position.z += speed * DataCore::deltaTime;
	}
	if (Keyboard::W) {
		position.y += speed * DataCore::deltaTime;
	}
	if (Keyboard::E) {
		position.z -= speed * DataCore::deltaTime;
	}
	if (Keyboard::S) {
		position.y -= speed * DataCore::deltaTime;
	}
	if (Keyboard::A) {
		position.x -= speed * DataCore::deltaTime;
	}
	if (Keyboard::D) {
		position.x += speed * DataCore::deltaTime;
	}
}

void RunControls2(vec3& position, float const& speed) {
	if (Keyboard::U) {
		position.z += speed * DataCore::deltaTime;
	}
	if (Keyboard::I) {
		position.y += speed * DataCore::deltaTime;
	}
	if (Keyboard::O) {
		position.z -= speed * DataCore::deltaTime;
	}
	if (Keyboard::J) {
		position.x -= speed * DataCore::deltaTime;
	}
	if (Keyboard::K) {
		position.y -= speed * DataCore::deltaTime;
	}
	if (Keyboard::L) {
		position.x += speed * DataCore::deltaTime;
	}
}

Material* sceneMaterial = NULL;
Material* landscapeMaterial = NULL;
Material* waterMaterial = NULL;
Material* lavaMaterial = NULL;

Material* toonBunnyMaterial = NULL;
Material* blinnBunnyMaterial = NULL;
Material* fadeInBunnyMaterial = NULL;
Material* geometryShaderMaterial = NULL;
Material* skyBoxMaterial = NULL;
Material* billboardMaterial = NULL;

Mesh* floorMesh = NULL;
Mesh* bunnyMesh1 = NULL;
Mesh* bunnyMesh2 = NULL;
Mesh* planeMesh = NULL;

Mesh* skyBox = NULL;
Mesh* landscapeMesh = NULL;

void LoadBunny() {
	/////////////////////////////
	// load toon material
	//toonBunnyMaterial = Material::CreateMaterial("./Assets/Images/soft-brown-fur-texture.png");
	//toonBunnyMaterial->shaderID = Load::LoadShaders("./Assets/Shaders/Toon.vertexshader", "./Assets/Shaders/Toon.fragmentshader");
	//toonBunnyMaterial->diffuseTiling = vec2(10.0f);

	/////////////////////////////
	// load blinn material
	blinnBunnyMaterial = Material::CreateMaterial("./Assets/Images/soft-brown-fur-texture.png");
	blinnBunnyMaterial->shaderID = Load::LoadShaders("./Assets/Shaders/BlinnFresnel.vertexshader", "./Assets/Shaders/BlinnFresnel.fragmentshader");
	blinnBunnyMaterial->diffuseTiling = vec2(10.0f);
	blinnBunnyMaterial->specularImageFilePath[0] = "./Assets/Images/brownFurSpecMap2.png";
	//blinnBunnyMaterial->specularImageFilePath[0] = "./Assets/Images/specMapTest.jpg";
	Load::_LoadTexture(&blinnBunnyMaterial->specularImageID[0], blinnBunnyMaterial->specularImageFilePath[0]);

	/////////////////////////////
	// load Fade-In material
	fadeInBunnyMaterial = Material::CreateMaterial("./Assets/Images/soft-brown-fur-texture.png");
	fadeInBunnyMaterial->shaderID = Load::LoadShaders("./Assets/Shaders/FadeInShaders/FadeIn.vertexshader", "./Assets/Shaders/FadeInShaders/FadeIn.fragmentshader");
	fadeInBunnyMaterial->diffuseTiling = vec2(10.0f);
	fadeInBunnyMaterial->specularImageFilePath[0] = "./Assets/Images/fadeIn_boxes_TopToBottom.png";
	Load::_LoadTexture(&fadeInBunnyMaterial->specularImageID[0], fadeInBunnyMaterial->specularImageFilePath[0]);

	////////////////////////////
	// billboard material
	//billboardMaterial = Material::CreateMaterial("./Assets/Images/soft-brown-fur-texture.png");
	//billboardMaterial->shaderID = Load::LoadShaders("./Assets/Shaders/FlattenTextureVertexShader.vertexshader", "./Assets/Shaders/FlattenTextureFragmentShader.fragmentshader");

	//////////////////////////////////
	// geo shader
	//geometryShaderMaterial = Material::CreateMaterial("./Assets/Images/dirt.jpg");
	//geometryShaderMaterial->shaderID = Load::LoadShaders("./Assets/Shaders/GeometryShaders/Geo.vertex", "./Assets/Shaders/GeometryShaders/Geo.frag", "./Assets/Shaders/GeometryShaders/Geo.geometry");

	//////////////////////////////
	// Load Meshes and set materials
	bunnyMesh1 = Mesh::CreateMeshObject("./Assets/Models/bunnyAveraged.obj", *fadeInBunnyMaterial, Transform(vec3(0.0f, 0.0f, 10.0f)));
	//planeMesh = Mesh::CreateMeshObject("./Assets/Models/plane.obj", *billboardMaterial, Transform(vec3(0.0f, 0.0f, 10.0f)));

	bunnyMesh2 = Mesh::CreateMeshObject("./Assets/Models/bunnyAveraged.obj", *blinnBunnyMaterial, Transform(vec3(2.0f, 0.0f, 12.0f)));
	//Mesh::CreateMeshObject("./Assets/Models/bunnyAveraged.obj", *geometryShaderMaterial, Transform(vec3(4.0f, 0.0f, 14.0f)));  

	glUseProgram(blinnBunnyMaterial->shaderID);

	// Directional light
    glUniform3f(glGetUniformLocation(blinnBunnyMaterial->shaderID, "dirLight.direction"), 1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(blinnBunnyMaterial->shaderID, "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
    glUniform3f(glGetUniformLocation(blinnBunnyMaterial->shaderID, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
    glUniform3f(glGetUniformLocation(blinnBunnyMaterial->shaderID, "dirLight.specular"), 0.5f, 0.5f, 0.5f);

	glm::vec3 pointLightPositions[] = {
		glm::vec3( 6.0f,  2.0f, 14.0f),
		glm::vec3( -2.0f,  2.0f, 8.0f),
		glm::vec3( -2.0f,  2.0f, 14.0f),
		glm::vec3( 6.0f,  2.0f, 8.0f)
	}; 

	glm::vec3 pointLightColors[] = {
		glm::vec3(0.0f, 0.75f, 0.75f),
		glm::vec3(0.75f, 0.0f, 0.75f),
		glm::vec3(0.75f, 0.75f, 0.0f),
		glm::vec3(0.75f, 0.75f, 0.75f)
	}; 

	for (GLuint i = 0; i < 4; i++)
	{
		string number = to_string(i);
		// Point Lights
		glUniform3f(glGetUniformLocation(blinnBunnyMaterial->shaderID, ("pointLights[" + number + "].position").c_str()), pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);
		glUniform3f(glGetUniformLocation(blinnBunnyMaterial->shaderID, ("pointLights[" + number + "].ambient").c_str()), pointLightColors[i].r * 0.15f, pointLightColors[i].g * 0.15f, pointLightColors[i].b * 0.15f);
		glUniform3f(glGetUniformLocation(blinnBunnyMaterial->shaderID, ("pointLights[" + number + "].diffuse").c_str()), pointLightColors[i].r, pointLightColors[i].g, pointLightColors[i].b);
		glUniform3f(glGetUniformLocation(blinnBunnyMaterial->shaderID, ("pointLights[" + number + "].specular").c_str()), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(blinnBunnyMaterial->shaderID, ("pointLights[" + number + "].constant").c_str()), 1.0f);
		glUniform1f(glGetUniformLocation(blinnBunnyMaterial->shaderID, ("pointLights[" + number + "].linear").c_str()), 0.08f);
		glUniform1f(glGetUniformLocation(blinnBunnyMaterial->shaderID, ("pointLights[" + number + "].quadratic").c_str()), 0.032f);
	}
}

void RunBunny() {
	//if (bunnyMesh1 != NULL) bunnyMesh1->transform.Rotate(0.4f * DataCore::deltaTime, vec3(0.0f, 1.0f, 0.0f), false);
	if (bunnyMesh2 != NULL) bunnyMesh2->transform.Rotate(0.4f * DataCore::deltaTime, vec3(0.0f, 1.0f, 0.0f), false);

	static GLfloat fadeInTimer = 0.0f;
	static float direction = 1.0f;
	if(fadeInBunnyMaterial != NULL) {

		glUseProgram(fadeInBunnyMaterial->shaderID);
		// get the timer variable on the video card
		GLint timeLoc = glGetUniformLocationARB(fadeInBunnyMaterial->shaderID, "fadeInTimer");
		// send the timer to the vertex Shader
		glUniform1fARB(timeLoc, fadeInTimer);

		fadeInTimer += 0.3f * direction * DataCore::deltaTime;

		if(fadeInTimer >= 1.0f) {
			fadeInTimer = 1.0f;
			direction = -1.0f;
		} 
		else if(fadeInTimer <= 0.0f) {
			fadeInTimer = 0.0f;
			direction = 1.0f;
		} 

		// geo shader stuff
		if (geometryShaderMaterial != NULL) {
			static float fBender = 0.1f;
			glUseProgram(geometryShaderMaterial->shaderID);
			// get the timer variable on the video card
			GLint fBenderLoc = glGetUniformLocationARB(geometryShaderMaterial->shaderID, "fBender");
			// send the timer to the vertex Shader
			glUniform1fARB(fBenderLoc, fBender);

			if (Keyboard::O) {
				fBender -= 0.1f * DataCore::deltaTime;
			}
			if (Keyboard::P) {
				fBender += 0.1f * DataCore::deltaTime;
			}
		}

	}
}

void RunLight() {

	//static vec3 lightDirection = vec3(0.0f, 1.0f, 0.1f);
	static vec3 lightDirection = vec3(-1.0f, 1.0f, 1.0f);

	//Utility::FluctuateValueUpAndDown(-1.0f, 1.0f, lightDirection.x, 0.25f * DataCore::deltaTime, true);

	//RunControls2(lightDirection, 25.0f * DataCore::deltaTime);

	lightDirection = Utility::Clamp(lightDirection, -1.0f, 1.0f);

	if (toonBunnyMaterial != NULL) {
		glUseProgram(toonBunnyMaterial->shaderID);
		GLint lightLocation = glGetUniformLocationARB(toonBunnyMaterial->shaderID, "lightDirection");
		glUniform3f(lightLocation, lightDirection.x, lightDirection.y, lightDirection.z);
	}

	if (sceneMaterial != NULL) {
		glUseProgram(sceneMaterial->shaderID);
		GLint lightLocation = glGetUniformLocationARB(sceneMaterial->shaderID, "lightDirection");
		glUniform3f(lightLocation, lightDirection.x, lightDirection.y, lightDirection.z);
	}

	if (landscapeMaterial != NULL) {
		glUseProgram(landscapeMaterial->shaderID);
		GLint lightLocation = glGetUniformLocationARB(landscapeMaterial->shaderID, "lightDirection");
		glUniform3f(lightLocation, lightDirection.x, lightDirection.y, lightDirection.z);
	}

	if (blinnBunnyMaterial != NULL) {
		glUseProgram(blinnBunnyMaterial->shaderID);
		GLint lightLocation = glGetUniformLocationARB(blinnBunnyMaterial->shaderID, "lightDirection");
		glUniform3f(lightLocation, lightDirection.x, lightDirection.y, lightDirection.z);
	}

	if (fadeInBunnyMaterial != NULL) {
		glUseProgram(fadeInBunnyMaterial->shaderID);
		GLint lightLocation = glGetUniformLocationARB(fadeInBunnyMaterial->shaderID, "lightDirection");
		glUniform3f(lightLocation, lightDirection.x, lightDirection.y, lightDirection.z);
	}

}

bool testLevelInitialized = false;
void LoadTestLevel() {
	LoadBunny();
	testLevelInitialized = true;
}

void RunTestLevel() {
	RunBunny();
	RunLight();

}

bool levelOneInitialized = false;
void Scene::LoadLevelOne() {
	sceneMaterial = Material::CreateMaterial("./Assets/Images/floorPillarStairs_Diffuse.png");
	landscapeMaterial = Material::CreateMaterial("./Assets/Images/dirt.jpg");

	skyBoxMaterial = Material::CreateMaterial("./Assets/Images/skyBox_texture.png");

	//sceneMaterial->shaderID = Load::LoadShaders("./Assets/Shaders/TextureVertexShader.vertexshader", "./Assets/Shaders/TextureFragmentShader.fragmentshader");
	sceneMaterial->shaderID = Load::LoadShaders("./Assets/Shaders/DiffuseTextureVertexShader.vertexshader", "./Assets/Shaders/DiffuseTextureFragmentShader.fragmentshader");

	skyBoxMaterial->shaderID = Load::LoadShaders("./Assets/Shaders/TextureVertexShader.vertexshader", "./Assets/Shaders/TextureFragmentShader.fragmentshader");
	landscapeMaterial->shaderID = Load::LoadShaders("./Assets/Shaders/DiffuseTextureVertexShader.vertexshader", "./Assets/Shaders/DiffuseTextureFragmentShader.fragmentshader");
	landscapeMaterial->diffuseTiling = vec2(10.0f, 10.0f);

	//landscapeMesh = Mesh::CreateMeshObject("./Assets/Models/landscape.obj", *bunnyMaterial, Transform(vec3(0.0f, -15.0f, 0.0f), vec3(5.0f)));


	///*
	skyBox = Mesh::CreateMeshObject("./Assets/Models/skyBox.obj", *skyBoxMaterial, Transform(vec3(0.0f, 4.0f, 0.0f), vec3(-60.0f)));
	//if (skyBox != NULL) skyBox->transform.Rotate(10.0f, vec3(0.0f, 0.0f, 1.0f), false);
	//Mesh::CreateMeshObject("./Assets/Models/candy.obj", *bunnyMaterial, Transform(vec3(6.0f, 0.0f, 0.0f)));
	Mesh::CreateMeshObject("./Assets/Models/head2.obj", *landscapeMaterial, Transform(vec3(0.0f, 4.0f, 0.0f), vec3(0.25f)));

	////floor
	floorMesh = Mesh::CreateMeshObject("./Assets/Models/floor1.obj", *sceneMaterial, Transform(vec3(0.0f, 0.0f, 0.0f)));
	//
	////stairs
	Mesh::CreateMeshObject("./Assets/Models/stairs1.obj", *sceneMaterial, Transform(vec3(0.0f, 0.0f, 0.0f)));
	//
	////// pillars
	////first row
	Mesh::CreateMeshObject("./Assets/Models/pillar.obj", *sceneMaterial, Transform(vec3(0.0f, 0.0f, 0.0f)));
	Mesh::CreateMeshObject("./Assets/Models/pillar.obj", *sceneMaterial, Transform(vec3(4.0f, 0.0f, 0.0f)));
	Mesh::CreateMeshObject("./Assets/Models/pillar.obj", *sceneMaterial, Transform(vec3(8.0f, 0.0f, 0.0f)));
	//second row
	Mesh::CreateMeshObject("./Assets/Models/pillar.obj", *sceneMaterial, Transform(vec3(0.0f, 0.0f, 5.8f)));
	Mesh::CreateMeshObject("./Assets/Models/pillar.obj", *sceneMaterial, Transform(vec3(4.0f, 0.0f, 5.8f)));
	Mesh::CreateMeshObject("./Assets/Models/pillar.obj", *sceneMaterial, Transform(vec3(8.0f, 0.0f, 5.8f)));

	// no uv's test
	//Mesh::CreateMeshObject("./Assets/Models/torus_NO_UVS.obj", *bunnyMaterial, Transform(vec3(-6.0f, 0.0f, 0.0f), vec3(0.25f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f)));
	//*/
	levelOneInitialized = true;
}

bool waterInitialized = false;
void LoadWater() {
	waterMaterial = Material::CreateMaterial("./Assets/Images/water.jpg");
	lavaMaterial = Material::CreateMaterial("./Assets/Images/lava.png");

	lavaMaterial->shaderID = Load::LoadShaders("./Assets/Shaders/Water.vertexshader", "./Assets/Shaders/Water.fragmentshader");
	waterMaterial->shaderID = lavaMaterial->shaderID;

	Mesh::CreateMeshObject("./Assets/Models/water.obj", *lavaMaterial, Transform(vec3(14.0f, -8.0f, 13.0f), vec3(0.31f)));
	waterInitialized = true;
}

bool levelTwoInitialized = false;
void LoadLevelTwo() {

	LoadWater();

	sceneMaterial = Material::CreateMaterial("./Assets/Images/floorPillarStairs_Diffuse.png");
	landscapeMaterial = Material::CreateMaterial("./Assets/Images/dirt.jpg");

	skyBoxMaterial = Material::CreateMaterial("./Assets/Images/skyBox_texture.png");
	geometryShaderMaterial = Material::CreateMaterial("./Assets/Images/dirt.jpg");

	sceneMaterial->shaderID = Load::LoadShaders("./Assets/Shaders/DiffuseTextureVertexShader.vertexshader", "./Assets/Shaders/DiffuseTextureFragmentShader.fragmentshader");

	geometryShaderMaterial->shaderID = Load::LoadShaders("./Assets/Shaders/GeometryShaders/Geo.vertex", "./Assets/Shaders/GeometryShaders/Geo.frag", "./Assets/Shaders/GeometryShaders/Geo.geometry");
	skyBoxMaterial->shaderID = Load::LoadShaders("./Assets/Shaders/TextureVertexShader.vertexshader", "./Assets/Shaders/TextureFragmentShader.fragmentshader");

	landscapeMaterial->shaderID = Load::LoadShaders("./Assets/Shaders/DiffuseTextureVertexShader.vertexshader", "./Assets/Shaders/DiffuseTextureFragmentShader.fragmentshader");
	landscapeMaterial->diffuseImageFilePath[1] = "./Assets/Images/sand.jpg";
	Load::_LoadTexture(&landscapeMaterial->diffuseImageID[1], landscapeMaterial->diffuseImageFilePath[1]);
	landscapeMaterial->diffuseTiling = vec2(10.0f, 10.0f);

	//landscapeMesh = Mesh::CreateMeshObject("./Assets/Models/landscape.obj", *landscapeMaterial, Transform(vec3(0.0f, -50.0f, 0.0f), vec3(50.0f)));
	landscapeMesh = Mesh::CreateMeshObject("./Assets/Models/landscape.obj", *landscapeMaterial, Transform(vec3(0.0f, -15.0f, 0.0f), vec3(5.0f)));

	skyBox = Mesh::CreateMeshObject("./Assets/Models/skyBox.obj", *skyBoxMaterial, Transform(vec3(0.0f, 4.0f, 0.0f), vec3(-70.0f)));

	LoadBunny();
	levelTwoInitialized = true;
}

void RunTimer() {
	// get random float
	//timer = Utility::GetRandomFloat(0.1f, 1.0f);

	//////////////////////////////////////////////////
	// timer
	///////////////////////////////////////////////////
	// create a timer
	static GLfloat timer = 0.0f;
	if (sceneMaterial != NULL) {
		glUseProgram(sceneMaterial->shaderID);
		// get the timer variable on the video card
		GLint timeLoc = glGetUniformLocationARB(sceneMaterial->shaderID, "timer");
		// send the timer to the vertex Shader
		glUniform1fARB(timeLoc, timer);
	}
	if (landscapeMaterial != NULL) {
		glUseProgram(landscapeMaterial->shaderID);
		// get the timer variable on the video card
		GLint timeLoc = glGetUniformLocationARB(landscapeMaterial->shaderID, "timer");
		// send the timer to the vertex Shader
		glUniform1fARB(timeLoc, timer);
	}
	if (billboardMaterial != NULL) {
		glUseProgram(billboardMaterial->shaderID);
		// get the timer variable on the video card
		GLint timeLoc = glGetUniformLocationARB(billboardMaterial->shaderID, "timer");
		// send the timer to the vertex Shader
		glUniform1fARB(timeLoc, timer);
	}
	//increment the timer
	timer += 2.0f * DataCore::deltaTime;
}

void RunLevelTwo() {
	if (sceneMaterial == NULL) return;
	glUseProgram(sceneMaterial->shaderID);
	// make the bunny mesh spin
	if (bunnyMesh1 != NULL) bunnyMesh1->transform.Rotate(0.75f * DataCore::deltaTime, vec3(0.0f, 1.0f, 0.0f), false);
	if (bunnyMesh2 != NULL) bunnyMesh2->transform.Rotate(0.75f * DataCore::deltaTime, vec3(0.0f, 1.0f, 0.0f), false);
	RunBunny();
	RunTimer();

	/////////////////////////////////////////////////////
	// lightDirection 
	/////////////////////////////////////////////////////
	RunLight();

	////////////////////////////////////
	//geo shader stuff
	//if (geometryShaderMaterial != NULL) {
	//	static float fBender = 0.1f;
	//	glUseProgram(geometryShaderMaterial->shaderID);
	//	// get the timer variable on the video card
	//	GLint fBenderLoc = glGetUniformLocationARB(geometryShaderMaterial->shaderID, "fBender");
	//	// send the timer to the vertex Shader
	//	glUniform1fARB(fBenderLoc, fBender);

	//	if (Keyboard::O) {
	//		fBender -= 0.1f * DataCore::deltaTime;
	//	}
	//	if (Keyboard::P) {
	//		fBender += 0.1f * DataCore::deltaTime;
	//	}
	//}

}

void RunLevelOne() {
	if (sceneMaterial == NULL) return;
	glUseProgram(sceneMaterial->shaderID);
	// make the bunny mesh spin
	//if (bunnyMesh1 != NULL) bunnyMesh1->transform.Rotate(1.5f * DataCore::deltaTime, vec3(0.0f, 1.0f, 0.0f), false);
	RunBunny();
	RunTimer();

	/////////////////////////////////////////////////////
	// lightDirection 
	/////////////////////////////////////////////////////
	RunLight();

}

void RunWater() {
	if (waterMaterial == NULL) return;
	glUseProgram(waterMaterial->shaderID);

	static float waveTime = 0.5f;

	static float waveWidth = 0.6f;
	static float waveHeight = 0.4f;

	static float waveFrequency = 0.3f;

	static float changeSpeed = 0.05f;
	static float direction = 1.0f;

	if (direction == 1.0f) {
		waveHeight += (changeSpeed * direction) * DataCore::deltaTime;
		//waveWidth += (changeSpeed * direction) * DataCore::deltaTime;
		if (waveHeight >= 0.5f) {
			waveHeight = 0.5f;
			direction = -1.0f;
		}
	}
	else if (direction == -1.0f) {
		waveHeight += (changeSpeed * direction) * DataCore::deltaTime;
		//waveWidth += (changeSpeed * direction) * DataCore::deltaTime;
		if (waveHeight <= 0.2f) {
			waveHeight = 0.2f;
			direction = 1.0f;
		}
	}

	GLint waveTimeLoc = glGetUniformLocationARB(lavaMaterial->shaderID, "waveTime");
	GLint waveWidthLoc = glGetUniformLocationARB(lavaMaterial->shaderID, "waveWidth");
	GLint waveHeightLoc = glGetUniformLocationARB(lavaMaterial->shaderID, "waveHeight");

	glUniform1fARB(waveTimeLoc, waveTime);
	glUniform1fARB(waveWidthLoc, waveWidth);
	glUniform1fARB(waveHeightLoc, waveHeight);

	// Update wave variable
	waveTime += waveFrequency * DataCore::deltaTime;

}

void Scene::InitializeScene() {
	if (!Scene::sceneInitialized) {

		GLuint vertexArrayID = NULL;
		glGenVertexArrays(1, &vertexArrayID);
		glBindVertexArray(vertexArrayID);

		// tell openGL to use our program...
		//glUseProgram(DataCore::programID);
		// enable the depth test for 3d
		glEnable(GL_DEPTH_TEST);
		// enable backface culling
		glEnable(GL_CULL_FACE);
		glShadeModel(GL_SMOOTH);
		// render lines...
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);

		// init the mouse
		Mouse::InitMouse();

		//Scene::LoadLevelOne();

		LoadLevelTwo();

		//LoadTestLevel();

		// init scene variable = true;
		Scene::sceneInitialized = true;

		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
	}
}

void DeleteAllObjectsTest() {

	if (Keyboard::SpaceBar) {
		//GameObject::DeleteAllObjects();
		GameObject::DeleteAllObjects();
		sceneMaterial = NULL;
		landscapeMaterial = NULL;
		waterMaterial = NULL;
		lavaMaterial = NULL;
		toonBunnyMaterial = NULL;
		skyBoxMaterial = NULL;
		floorMesh = NULL;
		bunnyMesh1 = NULL;
		bunnyMesh2 = NULL;
		skyBox = NULL;
		landscapeMesh = NULL;
	}
}

void Update() {
	//bunnyMesh->Run(&DataCore::camera);
	// clear the screen...
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// get the deltaTime...
	DataCore::deltaTime = Utility::getDeltaTime();
	// fprintf(stdout, "Delta Time: %f", getDeltaTime()); 
	// update the camera
	DataCore::camera.Update();
	// move with FPS controls
	DataCore::camera.MoveWithFPSControls();
	// Run FPS mouse look
	Mouse::RunFPSMouse();
	// Run Keyboard Input
	Keyboard::RunKeyboardKeys();

	// Run Objects
	GameObject::RunAllObjects();

	//DeleteAllObjectsTest();

	//level one
	if (levelOneInitialized) RunLevelOne();

	if (waterInitialized) RunWater();

	if (levelTwoInitialized) RunLevelTwo();

	if (testLevelInitialized) RunTestLevel();
}

int Scene::MainLoop() {

	Scene::InitializeScene();

	do {
		// Run OpenGL's Event Handler...
		glfwPollEvents();
		// update
		Update();
		// swap the screen buffers...
		glfwSwapBuffers(DataCore::window);

	} while (!Keyboard::Escape && glfwWindowShouldClose(DataCore::window) == 0);

	// save a screenshot
	SOIL_save_screenshot
		(
		"screenshot.bmp",
		SOIL_SAVE_TYPE_BMP,
		0, 0, 1200, 800
		);

	return EXIT_WITH_SUCCESS;
}