// CORE.Utility.cpp
//////////////////////////////////////////////////////////////////////////

#include "CORE.Utility.h"

///////////////////////////////////////////////////////////////////////////////
// Utility
float& Utility::getDeltaTime() {
	static float lastTime = glfwGetTime();

	float now = glfwGetTime();
	float deltaTime = now - lastTime;

	lastTime = now;
	return deltaTime;
}

vec3 Utility::NormalizeVector3(vec3 vector) {
	float length = sqrt((vector.x*vector.x) + (vector.y*vector.y) + (vector.z*vector.z));
	vec3 n = vec3((vector.x / length), (vector.y / length), (vector.z / length));

	return n;
}

vec3 Utility::CalculateReflectionVector(vec3 vector, vec3 normal) {
	//R = V - 2 * N * dot(V, N)
	vec3 r;

	r.x = vector.x - (2.0f * normal.x * dot(vector, normal));
	r.y = vector.y - (2.0f * normal.y * dot(vector, normal));
	r.z = 0.0f;

	return r;
}

int Utility::GetRandomInt(int from, int to) {
	return rand() % to + from;

}