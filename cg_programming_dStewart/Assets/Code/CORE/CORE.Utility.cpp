// CORE.Utility.cpp
//////////////////////////////////////////////////////////////////////////

#include "CORE.Utility.h"

///////////////////////////////////////////////////////////////////////////////
// Utility
float Utility::getDeltaTime() {
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

float Utility::GetRandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void Utility::FluctuateValueUpAndDown(float min, float max, float& value, float speed, bool startByGoingUp) {
	static bool directionDecided = false;
	static int direction = 1;
	if (!directionDecided) {
		if (!startByGoingUp) direction = -1;
		directionDecided = true;
	}

	if (value >= max) {
		value = max;
		direction = -1;
	}
	else if (value <= min) {
		value = min;
		direction = 1;
	}

	value += speed * direction;
}

float Utility::Clamp(float value, float from, float to) {
	if(value > to) {
		return to;
	} 
	else if(value < from) {
		return from;
	}
	return value;
}

vec3 Utility::Clamp(vec3 vector3, float from, float to) {
	// clamp x
	if(vector3.x > to) {
		vector3.x = to;
	} 
	else if(vector3.x < from) {
		vector3.x = from;
	}

	// clamp y
	if(vector3.y > to) {
		vector3.y = to;
	} 
	else if(vector3.y < from) {
		vector3.y = from;
	}

	// clamp z
	if(vector3.z > to) {
		vector3.z = to;
	}
	else if(vector3.z < from) {
		vector3.z = from;
	}
	
	// return the clamped vector.
	return vector3;
}