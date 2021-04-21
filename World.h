#pragma once
#include "Cube.h"
#include <vector>
#include "TextureManager.h"
#include "Chunk.h"
#include "CameraController.h" 
#include "GLWindow.h"
//for older generation
#define XSIZE 20
#define ZSIZE 20
#define HEIGHT 7

class World
{
private:
	TextureManager textureManager; 
	vector<Chunk*> chunks;

public: 
	CameraController camera;
	vector<Cube*> dirtCubes;
	vector<Cube*> cloudCubes;
	vector<Cube*> waterCubes;

	void HandleInput(float dt);
	void Update(float dt); // nothing yet
	void RenderWorld();
	World();
};

//somehow do chunks I guess