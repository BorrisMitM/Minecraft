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

	GLWindow* window;
public:
	static Vector3 center;
	static Vector3 mousePos;
	static Vector3 lastMousePos;
	const Vector3& getPosition() { return position; }
	void setPosition(const Vector3& pos) { position = pos; }
	const Vector3& getLookAt() { return position + forward; }
	const Vector3& getUp() { return up; }

	void Setup(GLWindow* window);
	void HandleInput(float dt);
	void Update(float dt);
	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	CameraController();

};

