#pragma once
#include "Vector3.h"
#include "GLWindow.h"

class CameraController
{
	Vector3 position;
	Vector3 velocity;

	Vector3 forward, up, side;

	float pitch, yaw, roll;
	float velocityMagnitude, turnSpeed;

public:

	const Vector3& getPosition() { return position; }
	void setPosition(const Vector3& pos) { position = pos; }
	const Vector3& getLookAt() { return position + forward; }
	const Vector3& getUp() { return up; }

	void HandleInput(float dt);
	void Update(float dt);
	CameraController() { position.x = 0.f, position.y = 0.f, position.z = 0.f; pitch = 0.f; yaw = 180.f; roll = 0.f; velocityMagnitude = 50.f; turnSpeed = 50.f; }
};

