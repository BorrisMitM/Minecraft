#include "CameraController.h"
#include <iostream>
#include "Chunk.h"
#include "Raycast.h"

void CameraController::Setup(GLWindow* window)
{
	this->window = window;
	//don't show the cursor and lock it to the middle of the screen
	glfwSetInputMode(window->m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void CameraController::HandleInput(float dt, World& world)
{ 

	if (isFlying) {
		//if flying just set the position directly, since we dont have any collision checks
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
	}
	else {
		//project forward vector on the x,z-plane to set velocity indepentant of pitch
		Vector3 forwardXZ(forward.x, 0, forward.z);
		forwardXZ.Normalize();

		//reset horizontal velocity 
		velocity.x = 0;
		velocity.z = 0;

		//set velocity according to input
		SHORT key = ::GetAsyncKeyState(0x57) & 0x8000;//W
		if (key != 0) velocity += forwardXZ * velocityMagnitude * dt;

		key = ::GetAsyncKeyState(0x53) & 0x8000;//S
		if (key != 0) velocity -= forwardXZ * velocityMagnitude * dt;

		key = ::GetAsyncKeyState(0x44) & 0x8000;//D
		if (key != 0) velocity += side * velocityMagnitude * dt;

		key = ::GetAsyncKeyState(0x41) & 0x8000;//A
		if (key != 0) velocity -= side * velocityMagnitude * dt;

		key = ::GetAsyncKeyState(0x20) & 0x8000;//Space bar
		if (key != 0 && isGrounded) {
			//only jump if grounded
			velocity.y = 5;
		}
	}

	//toggle flight mode
	SHORT key = ::GetAsyncKeyState(0x0D) & 0x8000;//Enter
	if (key != 0) {
		if (!isFlyingPressed) {
			isFlyingPressed = true;
			isFlying = !isFlying;
			cout << "Flying: " << isFlying << endl;
		}
	}
	else isFlyingPressed = false;

	//get cursor movement
	double xpos, ypos;
	glfwGetCursorPos(window->m_Window, &xpos, &ypos);

	mousePos.x = xpos - lastMousePos.x;
	mousePos.y = ypos - lastMousePos.y;
	lastMousePos.x = xpos;
	lastMousePos.y = ypos;

	//modify pitch and yaw depending on cursor input
	pitch -= turnSpeed * dt * mousePos.y;
	yaw += turnSpeed * dt * mousePos.x;

	//clamp values
	if (yaw < 0) yaw += 360.f;
	if (yaw > 360) yaw -= 360.f;
	
	if (pitch < -85) pitch = -85;
	if (pitch > 85) pitch = 85;
	
	if (roll < 0) roll += 360.f;
	if (roll > 360) roll -= 360.f;
	

	//destroy cubes
	
	int mouseButton = glfwGetMouseButton(window->m_Window, 0);
	
	if (mouseButton == GLFW_PRESS) {
		if (!mousePressed) {
			mousePressed = true;
			//check if cube in range gets hit by raycast and delete it
			Cube* hitCube = Raycast::Cast(position, forward, 3, world);
			if (hitCube != NULL)
				hitCube->Delete();
		}
	}
	else mousePressed = false;

	
}

void CameraController::Update(float dt, World &world)
{
	//physics
	if (!isFlying) {
		// apply gravity to y
		velocity.y -= gravity * dt;
		if (velocity.y * dt >= 0.5) {
			velocity.y = 0.9 / dt;
		}

		// raycast cylinder
		vector<Raycast::CollisionInfo> collisionInfo;
		bool collided = Raycast::CylinderCast(position + velocity * dt, 0.2f, 1.4f, 0.3f, world, collisionInfo);

		// check if grounded from raycast info

		isGrounded = false;
		if (collided) {

			//ground checking
			int groundY = -1; //yvalue of the ground collision 
			if (velocity.y <= 0) {
				Vector3 up(0, 1, 0);
				for (int i = 0; i < collisionInfo.size(); i++)
				{
					if (collisionInfo[i].normal == up) {
						isGrounded = true;
						velocity.y = 0;
						groundY = collisionInfo[i].cube->position.y;
					}
				}
			}
			//top checking
			if (velocity.y > 0) {
				Vector3 down(0, -1, 0);
				for (int i = 0; i < collisionInfo.size(); i++)
				{
					if (collisionInfo[i].normal == down) {
						velocity.y = 0;
					}
				}
			}
			//side checking

			for (int i = 0; i < collisionInfo.size(); i++)
			{
				//ignore side collision for cubes we are standing on
				if (collisionInfo[i].cube->position.y == groundY) continue;
				if (collisionInfo[i].normal.x != 0) {
					velocity.x = 0;
				}
				if (collisionInfo[i].normal.z != 0) {
					velocity.z = 0;
				}
			}
		}
		position += velocity * dt;
	}


	// Camera rotation
	//pre calculate cos and sin values
	float cosPitch = cosf(pitch * 3.1415 / 180);
	float cosYaw = cosf(yaw * 3.1415 / 180);
	float cosRoll = cosf(roll * 3.1415 / 180);

	float sinPitch = sinf(pitch * 3.1415 / 180);
	float sinYaw = sinf(yaw * 3.1415 / 180);
	float sinRoll = sinf(roll * 3.1415 / 180);

	//calculate forward vector
	forward.x = sinYaw * cosPitch;
	forward.y = sinPitch;
	forward.z = cosPitch * -cosYaw;

	//calculate up vector
	up.x = -cosYaw * sinRoll - sinYaw * sinPitch * cosRoll;
	up.y = cosPitch * cosRoll;
	up.z = -sinYaw * sinRoll - sinPitch * cosRoll * -cosYaw;

	side = forward.cross(up);
	
}

CameraController::CameraController()
{
	position.x = 0.f,
	position.y = 100.f,
	position.z = 0.f;
	pitch = 0.f;
	yaw = 180.f;
	roll = 0.f;
	velocityMagnitude = 200.f;
	turnSpeed = 2.f;
}
