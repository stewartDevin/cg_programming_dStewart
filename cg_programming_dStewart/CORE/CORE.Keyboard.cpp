// CORE.Keyboard.cpp
//////////////////////////////////////////////////////////////////////////

#include "CORE.Keyboard.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Main.h"
#include "../APP/APP.GameOptions.h"

bool Keyboard::W = false;
bool Keyboard::A = false;
bool Keyboard::S = false;
bool Keyboard::D = false;
bool Keyboard::UpArrow = false;
bool Keyboard::LeftArrow = false;
bool Keyboard::RightArrow = false;
bool Keyboard::DownArrow = false;

Keyboard::Keyboard() {
	
}

void Keyboard::RunKeyboardKeys() {
	if (glfwGetKey(GameOptions::window, GLFW_KEY_W) == GLFW_PRESS) {
		Keyboard::W = true;
	}
	else {
		Keyboard::W = false;
	}

	if (glfwGetKey(GameOptions::window, GLFW_KEY_A) == GLFW_PRESS) {
		Keyboard::A = true;
	}
	else {
		Keyboard::A = false;
	}

	if (glfwGetKey(GameOptions::window, GLFW_KEY_S) == GLFW_PRESS) {
		Keyboard::S = true;
	}
	else {
		Keyboard::S = false;
	}

	if (glfwGetKey(GameOptions::window, GLFW_KEY_D) == GLFW_PRESS) {
		Keyboard::D = true;
	}
	else {
		Keyboard::D = false;
	}

	if (glfwGetKey(GameOptions::window, GLFW_KEY_UP) == GLFW_PRESS) {
		Keyboard::UpArrow = true;
	}
	else {
		Keyboard::UpArrow = false;
	}

	if (glfwGetKey(GameOptions::window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		Keyboard::LeftArrow = true;
	}
	else {
		Keyboard::LeftArrow = false;
	}

	if (glfwGetKey(GameOptions::window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		Keyboard::DownArrow = true;
	}
	else {
		Keyboard::DownArrow = false;
	}

	if (glfwGetKey(GameOptions::window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		Keyboard::RightArrow = true;
	}
	else {
		Keyboard::RightArrow = false;
	}
}