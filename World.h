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

	unsigned int vboDirt;
	unsigned int iboDirt;
	unsigned int vboGrass;
	unsigned int iboGrass;
	unsigned int vboStone;
	unsigned int iboStone;

	std::vector<Cube::Vertex> dirtVertices;
	std::vector<unsigned int> dirtIndices;	
	std::vector<Cube::Vertex> grassVertices;
	std::vector<unsigned int> grassIndices;	
	std::vector<Cube::Vertex> stoneVertices;
	std::vector<unsigned int> stoneIndices;

	void CreateBuffers();

public: 
	CameraController camera;
	vector<Cube*> dirtCubes;
	vector<Cube*> cloudCubes;
	vector<Cube*> waterCubes;

	void HandleInput(float dt);
	void Update(float dt); 
	void RenderWorld();
	World();
	~World();
};
