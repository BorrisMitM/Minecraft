#pragma once
#include "Cube.h"
#include <vector>
#include "TextureManager.h"
#include "Chunk.h"
#include "CameraController.h" 
//for older generation
#define XSIZE 20
#define ZSIZE 20
#define HEIGHT 7

class World
{
private:
	TextureManager textureManager; 
	vector<Chunk*> chunks;
	CameraController camera;

public: 
	vector<Cube*> dirtCubes;
	vector<Cube*> cloudCubes;
	vector<Cube*> waterCubes;

	void HandleInput();
	void Update(); // nothing yet
	void RenderWorld();
	World();
};

//somehow do chunks I guess