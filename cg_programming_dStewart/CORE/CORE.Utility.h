// CORE.Utility.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "../Application.h"

///////////////////////////////////////////////////////////////////////////////
// Utility
static class Utility {
public:
	static float& getDeltaTime();

	static vec3 NormalizeVector3(vec3 vector);

	static vec3 CalculateReflectionVector(vec3 vector, vec3 normal);

	static int GetRandomInt(int from, int to);

};