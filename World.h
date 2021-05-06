#pragma once
#include "Cube.h"
#include <vector>
#include "TextureManager.h"
#include "Chunk.h"
#include "Cloud.h"
#include "CameraController.h" 
#include "GLWindow.h"
#include "Skybox.h"
#include "Vector3i.h"
#include "TerrainGenerator.h"
//for older generation
//#define XSIZE 20
//#define ZSIZE 20
//#define HEIGHT 7

class World
{
private:
	TextureManager textureManager; 
	vector<Chunk*> chunks;
	Skybox* skybox;

	Cloud cloudGen;
	TerrainGenerator terrainGenerator;

	unsigned int vboCloud;
	unsigned int iboCloud;

	std::vector<Cube::Vertex> cloudVertices;
	std::vector<unsigned int> cloudIndices;

	void CreateCloudBuffers();
	void UpdateBuffers();
	void CalculateNeighbors();

	void BindBuffer(unsigned int vbo, unsigned int ibo, unsigned int texture);

	Vector3 playerPosition;
public: 
	Chunk* currentChunk;
	CameraController camera;

	void HandleInput(float dt);
	void Update(float dt); 
	void RenderWorld();
	World();
	~World();
};
