#pragma once
#include "Cube.h"
#include <vector>
#include "TextureManager.h"
#include "Chunk.h"
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
	TerrainGenerator terrainGenerator;
	unsigned int vboDirt;
	unsigned int iboDirt;
	unsigned int vboGrass;
	unsigned int iboGrass;
	unsigned int vboStone;
	unsigned int iboStone;
	unsigned int vboWater;
	unsigned int iboWater;

	std::vector<Cube::Vertex> dirtVertices;
	std::vector<unsigned int> dirtIndices;	
	std::vector<Cube::Vertex> grassVertices;
	std::vector<unsigned int> grassIndices;	
	std::vector<Cube::Vertex> stoneVertices;
	std::vector<unsigned int> stoneIndices;
	std::vector<Cube::Vertex> waterVertices;
	std::vector<unsigned int> waterIndices;

	void CreateBuffers();
	void UpdateBuffers();
	void CalculateNeighbors();
	void GetBufferDataFromChunks();
	void BindBuffer(unsigned int vbo, unsigned int ibo, unsigned int texture);

	Vector3 playerPosition;
	Chunk* currentChunk;
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
