#include "CameraController.h"
#include <iostream>

void CameraController::HandleInput()
{
	//check input
	//set speed
	//displace position
	// This is a Windows function to check for multiple keystrokes at the same time.
		// If the highest bit is set the requested key is pressed.

	// translate controls OLD
	//SHORT key = ::GetAsyncKeyState(0x57) & 0x8000;//W
	//if (key != 0) velocity.z = -velocityMagnitude;
	//else {
	//	key = ::GetAsyncKeyState(0x53) & 0x8000;//S
	//	if (key != 0) velocity.z = velocityMagnitude;
	//	else velocity.z = 0;
	//}
	//key = ::GetAsyncKeyState(0x44) & 0x8000;//D
	//if (key != 0) velocity.x = velocityMagnitude;
	//else {
	//	key = ::GetAsyncKeyState(0x41) & 0x8000;//A
	//	if (key != 0) velocity.x = -velocityMagnitude;
	//	else velocity.x = 0;
	//}
	//key = ::GetAsyncKeyState(0x45) & 0x8000;//E
	//if (key != 0) velocity.y = -velocityMagnitude;
	//else {
	//	key = ::GetAsyncKeyState(0x51) & 0x8000;//Q
	//	if (key != 0) velocity.y = velocityMagnitude;
	//	else velocity.y = 0;
	//}

	SHORT key = ::GetAsyncKeyState(0x57) & 0x8000;//W
	if (key != 0) position += forward * velocityMagnitude;

	key = ::GetAsyncKeyState(0x53) & 0x8000;//S
	if (key != 0) position -= forward * velocityMagnitude;
	
	key = ::GetAsyncKeyState(0x44) & 0x8000;//D
	if (key != 0) position += side * velocityMagnitude;

	key = ::GetAsyncKeyState(0x41) & 0x8000;//A
	if (key != 0) position -= side * velocityMagnitude;
		
	key = ::GetAsyncKeyState(0x45) & 0x8000;//E
	if (key != 0) 
		position += up * velocityMagnitude;

	key = ::GetAsyncKeyState(0x51) & 0x8000;//Q
	if (key != 0) 
		position -= up * velocityMagnitude;
	

	//rotate controls OLD
	//key = ::GetAsyncKeyState(VK_UP) & 0x8000;//uparrow
	//if (key != 0) pitch = turnSpeed;
	//else {
	//	key = ::GetAsyncKeyState(VK_DOWN) & 0x8000;//downarro
	//	if (key != 0) pitch = -turnSpeed;
	//	else pitch = 0;
	//}
	//key = ::GetAsyncKeyState(VK_LEFT) & 0x8000;//uparrow
	//if (key != 0) yaw = turnSpeed;
	//else {
	//	key = ::GetAsyncKeyState(VK_RIGHT) & 0x8000;//downarro
	//	if (key != 0) yaw = -turnSpeed;
	//	else yaw = 0;
	//}

	key = ::GetAsyncKeyState(VK_UP) & 0x8000;//up arrow
	if (key != 0) pitch += turnSpeed;

	key = ::GetAsyncKeyState(VK_DOWN) & 0x8000;//down arrow
	if (key != 0) pitch -= turnSpeed;
	
	key = ::GetAsyncKeyState(VK_LEFT) & 0x8000;//left arrow
	if (key != 0) yaw -= turnSpeed;
	
	key = ::GetAsyncKeyState(VK_RIGHT) & 0x8000;//right arrow
	if (key != 0) yaw += turnSpeed;


	if (yaw < 0) yaw += 360.f;
	if (yaw > 360) yaw -= 360.f;

	if (pitch < 0) pitch += 360.f;
	if (pitch > 360) pitch -= 360.f;

	if (roll < 0) roll += 360.f;
	if (roll > 360) roll -= 360.f;
	
	
}

void CameraController::Update()
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

	//cout << "position: " << position.x << " " << position.y << " " << position.z << endl;
	//cout << "Up: " << up.x << " " << up.y << " " << up.z << endl;
	//cout << "lookAt: " << position.x + forward.x << " " << position.y + forward.y << " " << position.z + forward.z << endl;
	//cout << "angles: " << yaw << " " << pitch << " " << roll << endl;


	//CAMERA MOVEMENT OLD
	/*Vector3 up;
	Vector3 forward;

	forward.z = cos(pitch) * cos(yaw);
	forward.y = sin(pitch);
	forward.x = sin(yaw) * cos(pitch);
	forward.Normalize();
	up.x = -sin(yaw) * sin(pitch);
	up.y = cos(pitch);
	up.z = sin(pitch) * cos(yaw);
	up.Normalize();
	forward.Print();

	gluLookAt(velocity.x, velocity.y, velocity.z, -forward.x, -forward.y, -forward.z, up.x, up.y, up.z);*/
}
