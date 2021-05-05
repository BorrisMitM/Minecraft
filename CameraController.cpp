#include "CameraController.h"
#include <iostream>


void CameraController::Setup(GLWindow* window)
{
	this->window = window;
	//glfwSetCursorPosCallback(window->m_Window, CursorPositionCallback);
	glfwSetInputMode(window->m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void CameraController::HandleInput(float dt)
{ 

	SHORT key = ::GetAsyncKeyState(0x57) & 0x8000;//W
	if (key != 0) position += forward * velocityMagnitude * dt;

	key = ::GetAsyncKeyState(0x53) & 0x8000;//S
	if (key != 0) position -= forward * velocityMagnitude * dt;
	
	key = ::GetAsyncKeyState(0x44) & 0x8000;//D
	if (key != 0) position += side * velocityMagnitude * dt;

	key = ::GetAsyncKeyState(0x41) & 0x8000;//A
	if (key != 0) position -= side * velocityMagnitude * dt;
		
	key = ::GetAsyncKeyState(0x45) & 0x8000;//E
	if (key != 0) 
		position += up * velocityMagnitude * dt;

	key = ::GetAsyncKeyState(0x51) & 0x8000;//Q
	if (key != 0) 
		position -= up * velocityMagnitude * dt;
	

	double xpos, ypos;
	glfwGetCursorPos(window->m_Window, &xpos, &ypos);

	mousePos.x = xpos - lastMousePos.x;
	mousePos.y = ypos - lastMousePos.y;
	lastMousePos.x = xpos;
	lastMousePos.y = ypos;

	pitch -= turnSpeed * dt * mousePos.y;
	yaw += turnSpeed * dt * mousePos.x;

	if (yaw < 0) yaw += 360.f;
	if (yaw > 360) yaw -= 360.f;
	
	if (pitch < -85) pitch = -85;
	if (pitch > 85) pitch = 85;
	
	if (roll < 0) roll += 360.f;
	if (roll > 360) roll -= 360.f;
	
	
}

void CameraController::Update(float dt)
{
	float cosPitch = cosf(pitch * 3.1415 / 180);
	float cosYaw = cosf(yaw * 3.1415 / 180);
	float cosRoll = cosf(roll * 3.1415 / 180);

	float sinPitch = sinf(pitch * 3.1415 / 180);
	float sinYaw = sinf(yaw * 3.1415 / 180);
	float sinRoll = sinf(roll * 3.1415 / 180);

	forward.x = sinYaw * cosPitch;
	forward.y = sinPitch;
	forward.z = cosPitch * -cosYaw;

	up.x = -cosYaw * sinRoll - sinYaw * sinPitch * cosRoll;
	up.y = cosPitch * cosRoll;
	up.z = -sinYaw * sinRoll - sinPitch * cosRoll * -cosYaw;

	side = forward.cross(up);

}

CameraController::CameraController()
{
	position.x = 0.f,
	position.y = 0.f,
	position.z = 0.f;
	pitch = 0.f;
	yaw = 180.f;
	roll = 0.f;
	velocityMagnitude = 50.f;
	turnSpeed = 2.f;
}
