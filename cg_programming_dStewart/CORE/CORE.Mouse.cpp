// CORE.Mouse.cpp
///////////////////////////////////////////////

#include "CORE.Mouse.h"
#include "..\APP\APP.DataCore.h"

/////////////////////////////////////////////////
// static variables
double Mouse::X = 0.0;
double Mouse::Y = 0.0;

double Mouse::xScroll = 0.0;
double Mouse::yScroll = 0.0;

bool Mouse::LEFT_BUTTON_DOWN = false;

float Mouse::sensitivity = 0.05f;

/////////////////////////////////////////////////
// static functions

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Mouse::xScroll = xoffset;
	Mouse::yScroll = yoffset;
}


void Mouse::InitMouse() {
	glfwSetScrollCallback(DataCore::window, scroll_callback);
	glfwSetInputMode(DataCore::window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

// get mouse position
vec2 Mouse::GetMousePosition() {
	if (DataCore::window != NULL) {

		glfwGetCursorPos(DataCore::window, &Mouse::X, &Mouse::Y);
		//fprintf(stdout, "Mouse Position: %f %f \r\n", Mouse::X, Mouse::Y);
		return vec2(Mouse::X, Mouse::Y);
	}
	else {
		fprintf(stderr, "Can't get mouse position.");

	}
	
}

void Mouse::LockMousePosition() {
	// Reset mouse position for next frame
	glfwSetCursorPos(DataCore::window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);


}

void Mouse::RunFPSMouseMovement(Camera* camera) {
	// Compute new orientation
	camera->horizontalAngle += Mouse::sensitivity * DataCore::deltaTime * float(SCREEN_WIDTH / 2 - Mouse::X);
	camera->verticalAngle += Mouse::sensitivity * DataCore::deltaTime * float(SCREEN_HEIGHT / 2 - Mouse::Y);

}

void Mouse::RunFPSMouse() {
	// get the mouse position
	Mouse::GetMousePosition();
	Mouse::LockMousePosition();
	Mouse::RunFPSMouseMovement(&DataCore::camera);
}
