#pragma once
#include "GLWindow.h"
#include "TextureManager.h"
#include "Vector3.h"

// Holds all information to render the skybox
class Skybox
{

private:
	Vector3 position;

protected:
	// Arrays holding the values that define our skybox and how to texture it
	float vert[24] = { -0.5,-0.5,0.5, 0.5,-0.5,0.5f, 0.5,0.5,0.5, -0.5,0.5,0.5, -0.5,-0.5,-0.5, 0.5,-0.5,-0.5f, 0.5,0.5,-0.5, -0.5,0.5,-0.5 };
	float uv[48] = { 0.0,0.33, 0.25,0.33, 0.25,0.66, 0.0,0.66, 0.25,0.33, 0.5,0.33, 0.5,0.66, 0.25,0.66, 0.5,0.33, 0.75,0.33, 0.75,0.66, 0.5,0.66, 0.75,0.33, 1.0,0.33, 1.0,0.66, 0.75,0.66, 0.25,1.0, 0.25,0.66, 0.5,0.66, 0.5,1.0, 0.26,0.0, 0.5,0.0, 0.5,0.33, 0.26,0.33 };
	int	  index[24] = { 0,1,2,3, 1,5,6,2, 5,4,7,6, 4,0,3,7, 3,2,6,7, 1,0,4,5 }; // back, right, front, left, up, down

public:

	// getter and setter
	void SetPosition(Vector3 position);
	Vector3 getPosition();

	const float scale;
	void Render(TextureManager& textureManager);
	Skybox(float scale) : scale(scale) { };
};

