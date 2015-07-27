// CORE.Mouse.h
////////////////////////////////////////////////////////
#pragma once

#include "../Application.h"

class Mouse {
public:
	// static variables
	static double X;
	static double Y;
	static bool LEFT_BUTTON_DOWN;

	// static functions
	static vec2 GetMousePosition();
	
};