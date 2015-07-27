// CORE.Mouse.cpp
///////////////////////////////////////////////

#include "CORE.Mouse.h"
#include "..\APP\APP.DataCore.h"

/////////////////////////////////////////////////
// static variables
double Mouse::X = 0;
double Mouse::Y = 0;

bool Mouse::LEFT_BUTTON_DOWN = false;

/////////////////////////////////////////////////
// static functions

// get mouse position
vec2 Mouse::GetMousePosition() {
	if (DataCore::window != NULL) {

		glfwGetCursorPos(DataCore::window, &Mouse::X, &Mouse::Y);
		//fprintf(stdout, "Mouse Position: %f %f", Mouse::X, Mouse::Y);
		return vec2(Mouse::X, Mouse::Y);
	}
	else {
		fprintf(stderr, "Can't get mouse position.");

	}
	
}

