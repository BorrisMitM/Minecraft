#pragma once
#include "Vector3.h"
#include "GLWindow.h"


//CameraController
//controls camera position
//Has 2 Modes:
//Default: usual WASD controls, SPACE: Jump
//Fly: WASDQE controls with q translating down and e translating up
//In both modes you can destroy blocks with a left mouse button click, in a certain distance
class World;
class CameraController
{
	//physics 
	Vector3 position;
	Vector3 velocity;

	float gravity = 9.81f;
	float velocityMagnitude;

	bool isFlying;
	bool isGrounded;
	//rotation
	Vector3 forward, up, side;

	float pitch, yaw, roll;
	float turnSpeed;

	Vector3 mousePos;
	Vector3 lastMousePos;
	//toggles for getting keydown events only once
	bool mousePressed = false;
	bool isFlyingPressed = false;

	GLWindow* window;
public:
	//getter/setter
	const Vector3& getPosition() { return position; }
	void setPosition(const Vector3& pos) { position = pos; }
	const Vector3& getLookAt() { return position + forward; }
	const Vector3& getUp() { return up; }

	
	void Setup(GLWindow* window);
	void HandleInput(float dt, World& world);//Takes care of setting position/velocity depending on the mode, also takes care of raycasting for blocks to destroy
	void Update(float dt, World& world);//contains a physicsstep and rotates the camera

	CameraController();

};

