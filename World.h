#pragma once
#include "Cube.h"
#include <vector>
#include "TextureManager.h"
#include "Chunk.h"
#include "CameraController.h" 
#include "GLWindow.h"
#include "Skybox.h"
//for older generation
#define XSIZE 20
#define ZSIZE 20
#define HEIGHT 7

class World
{
private:
	TextureManager textureManager; 
	vector<Chunk*> chunks;
	Skybox* skybox;
public: 
	CameraController camera;
	vector<Cube*> dirtCubes;
	vector<Cube*> cloudCubes;
	vector<Cube*> waterCubes;

	void HandleInput(float dt);
	void Update(float dt); 
	void RenderWorld();
	World();
};
