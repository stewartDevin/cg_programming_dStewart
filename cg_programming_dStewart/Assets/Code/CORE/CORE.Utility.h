// CORE.Utility.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "../Application.h"

///////////////////////////////////////////////////////////////////////////////
// Utility
class Utility {
public:
	/////////////////////////////////////////////////////////////////////
	// vectors
	static vec3 NormalizeVector3(vec3 vector);
	static vec3 CalculateReflectionVector(vec3 vector, vec3 normal);

	///////////////////////////////////////////////////////////
	// -- Clamp: 
	// Takes a vector3, 
	// if x, y, or z is less than from, set them equal to from, 
	// if x, y, or z is greater than to, set them equal to to, 
	// else, return the value you gave it. 
	static vec3 Clamp(vec3 vector3, float from, float to);

	/////////////////////////////////////////////////////////////////////
	// int
	static int GetRandomInt(int from, int to);

	/////////////////////////////////////////////////////////////////////
	// float
	static float getDeltaTime();
	static float GetRandomFloat(float a, float b);
	static void FluctuateValueUpAndDown(float min, float max, float& value, float speed, bool startByGoingUp);

	///////////////////////////////////////////////////////////
	// -- Clamp: 
	// Takes a float value, 
	// if it's less than from, set it equal to from, 
	// if it's greater than to, set it equal to to,
	// else, return the value you gave it. 
	static float Clamp(float value, float from, float to);
};