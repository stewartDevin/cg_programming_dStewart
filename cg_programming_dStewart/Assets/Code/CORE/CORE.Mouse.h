// CORE.Mouse.h
////////////////////////////////////////////////////////
#pragma once

#include "../Application.h"
#include "CORE.Camera.h"

class Mouse {
public:
	// static variables
	static double X;
	static double Y;
	static bool LEFT_BUTTON_DOWN;
	static float sensitivity;
	static double xScroll;
	static double yScroll;

	// static functions
	static vec2 GetMousePosition();
	static void Mouse::LockMousePosition();
	static void Mouse::RunFPSMouse();
	static void Mouse::RunFPSMouseMovement(Camera* camera);
	static void Mouse::InitMouse();
};