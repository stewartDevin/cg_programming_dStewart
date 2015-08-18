// CORE.Keyboard.cpp
//////////////////////////////////////////////////////////////////////////

#include "CORE.Keyboard.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Main.h"
#include "../APP/Pong/Pong.Options.h"
#include "../APP/APP.DataCore.h"

bool Keyboard::Escape = false;

bool Keyboard::A = false;
bool Keyboard::B = false;
bool Keyboard::C = false;
bool Keyboard::D = false;
bool Keyboard::E = false;
bool Keyboard::F = false;
bool Keyboard::G = false;
bool Keyboard::H = false;
bool Keyboard::I = false;
bool Keyboard::J = false;
bool Keyboard::K = false;
bool Keyboard::L = false;
bool Keyboard::M = false;
bool Keyboard::N = false;
bool Keyboard::O = false;
bool Keyboard::P = false;
bool Keyboard::Q = false;
bool Keyboard::R = false;
bool Keyboard::S = false;
bool Keyboard::T = false;
bool Keyboard::U = false;
bool Keyboard::V = false;
bool Keyboard::W = false;
bool Keyboard::X = false;
bool Keyboard::Y = false;
bool Keyboard::Z = false;

bool Keyboard::UpArrow = false;
bool Keyboard::LeftArrow = false;
bool Keyboard::RightArrow = false;
bool Keyboard::DownArrow = false;
bool Keyboard::SpaceBar = false;

Keyboard::Keyboard() {
	
}



void Keyboard::RunKeyboardKeys() {
	if (glfwGetKey(DataCore::window, GLFW_KEY_A) == GLFW_PRESS) {
		Keyboard::A = true;
	}
	else {
		Keyboard::A = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_B) == GLFW_PRESS) {
		Keyboard::B = true;
	}
	else {
		Keyboard::B = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_C) == GLFW_PRESS) {
		Keyboard::C = true;
	}
	else {
		Keyboard::C = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_D) == GLFW_PRESS) {
		Keyboard::D = true;
	}
	else {
		Keyboard::D = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_E) == GLFW_PRESS) {
		Keyboard::E = true;
	}
	else {
		Keyboard::E = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_F) == GLFW_PRESS) {
		Keyboard::F = true;
	}
	else {
		Keyboard::F = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_G) == GLFW_PRESS) {
		Keyboard::G = true;
	}
	else {
		Keyboard::G = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_H) == GLFW_PRESS) {
		Keyboard::H = true;
	}
	else {
		Keyboard::H = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_I) == GLFW_PRESS) {
		Keyboard::I = true;
	}
	else {
		Keyboard::I = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_J) == GLFW_PRESS) {
		Keyboard::J = true;
	}
	else {
		Keyboard::J = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_K) == GLFW_PRESS) {
		Keyboard::K = true;
	}
	else {
		Keyboard::K = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_L) == GLFW_PRESS) {
		Keyboard::L = true;
	}
	else {
		Keyboard::L = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_M) == GLFW_PRESS) {
		Keyboard::M = true;
	}
	else {
		Keyboard::M = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_N) == GLFW_PRESS) {
		Keyboard::N = true;
	}
	else {
		Keyboard::N = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_O) == GLFW_PRESS) {
		Keyboard::O = true;
	}
	else {
		Keyboard::O = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_P) == GLFW_PRESS) {
		Keyboard::P = true;
	}
	else {
		Keyboard::P = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_Q) == GLFW_PRESS) {
		Keyboard::Q = true;
	}
	else {
		Keyboard::Q = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_R) == GLFW_PRESS) {
		Keyboard::R = true;
	}
	else {
		Keyboard::R = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_S) == GLFW_PRESS) {
		Keyboard::S = true;
	}
	else {
		Keyboard::S = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_T) == GLFW_PRESS) {
		Keyboard::T = true;
	}
	else {
		Keyboard::T = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_U) == GLFW_PRESS) {
		Keyboard::U = true;
	}
	else {
		Keyboard::U = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_V) == GLFW_PRESS) {
		Keyboard::V = true;
	}
	else {
		Keyboard::V = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_W) == GLFW_PRESS) {
		Keyboard::W = true;
	}
	else {
		Keyboard::W = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_X) == GLFW_PRESS) {
		Keyboard::X = true;
	}
	else {
		Keyboard::X = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_Y) == GLFW_PRESS) {
		Keyboard::Y = true;
	}
	else {
		Keyboard::Y = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_Z) == GLFW_PRESS) {
		Keyboard::Z = true;
	}
	else {
		Keyboard::Z = false;
	}

	/////////////////////////

	if (glfwGetKey(DataCore::window, GLFW_KEY_UP) == GLFW_PRESS) {
		Keyboard::UpArrow = true;
	}
	else {
		Keyboard::UpArrow = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		Keyboard::LeftArrow = true;
	}
	else {
		Keyboard::LeftArrow = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		Keyboard::DownArrow = true;
	}
	else {
		Keyboard::DownArrow = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		Keyboard::RightArrow = true;
	}
	else {
		Keyboard::RightArrow = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		Keyboard::Escape = true;
	}
	else {
		Keyboard::Escape = false;
	}

	if (glfwGetKey(DataCore::window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		Keyboard::SpaceBar = true;
	}
	else {
		Keyboard::SpaceBar = false;
	}
}