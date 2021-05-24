#pragma once
#include "Cube.h"
#include "TextureManager.h"


//for chunk generation
#define NOISE_SCALE 32 // multiplies with the value of the noise -> changes height of mountains
#define MIN_HEIGHT 50 // gets added to the noise -> height of the lowest layer(height has this value if the noise is 0)
#define NOISE_XMUL 3.17f // defines the used section of our perlin noise, higher numbers -> higher frequency of hills
#define NOISE_ZMUL 3.17f
#define CHUNK_DISTANCE 7 // how many chuncks are generated in each direction(dont know minecraft does it like this)
#define DIRT_THICKNESS 10 // should not be bigger than MIN_HEIGHT
#define WATER_LEVEL 57 // from heightmap until WATER_LEVEL, we fill every empty space with water
class Chunk
{
	unsigned int vbo;
	unsigned int ibo;
	unsigned int waterVbo;
	unsigned int waterIbo;
	std::vector<Cube::Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Cube::Vertex> waterVertices;
	std::vector<unsigned int> waterIndices;

	void FillDirtArrays();
	void FillGrassArrays();
	void FillStoneArrays();
	void FillWaterArrays();
public:
	int gridPosX, gridPosZ; // position of the chunk ( in chonk space)
	Cube* cubes[16][256][16];
	Chunk* neighbors[4]; // up, right, down, left
	int heightMap[16][16];
	void SetVisibility(int x, int y, int z);
	void SetTransparency();

	void CreateAndFillBuffer();

	void Render();
	void RenderWater();
	~Chunk();
};
