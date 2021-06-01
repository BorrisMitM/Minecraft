#pragma once
#include "Cube.h"
#include "TextureManager.h"
#include "Cloud.h"
//A chunk contains a 3d array of cubes, which can be loaded and unloaded
//It collects all vertices of the cubes inside of it and sends them to OpenGL
//for chunk generation
#define NOISE_SCALE 32 // multiplies with the value of the noise -> changes height of mountains
#define MIN_HEIGHT 50 // gets added to the noise -> height of the lowest layer(height has this value if the noise is 0)
#define NOISE_XMUL 3.17f // defines the used section of our perlin noise, higher numbers -> higher frequency of hills
#define NOISE_ZMUL 3.17f
#define CHUNK_DISTANCE 7 // how many chuncks are generated in each direction(dont know minecraft does it like this)
#define DIRT_THICKNESS 10 // should not be bigger than MIN_HEIGHT
#define WATER_LEVEL 77 // from heightmap until WATER_LEVEL, we fill every empty space with water
class Chunk
{
	//vertex and index array infos
	unsigned int vbo;
	unsigned int ibo;
	std::vector<Cube::Vertex> vertices;
	std::vector<unsigned int> indices;

	void FillDirtArrays();
	void FillGrassArrays();
	void FillStoneArrays();
	void FillWaterArrays();
public:
	Cloud* cloud;
	int gridPosX, gridPosZ; // position of the chunk ( in chonk grid)
	Cube* cubes[16][256][16];
	Chunk* neighbors[4]; // up, right, down, left
	int heightMap[16][16]; //hight map of the original generated chunk, used for determining cube type
	void SetVisibility(int x, int y, int z); //Sets the visibility of a cube in local space
	void SetTransparency();

	void CreateAndFillBuffer();

	void Update(float dt);
	void CreateCloud();

	void Render();
	~Chunk();
};
