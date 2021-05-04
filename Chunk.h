#pragma once
#include "Cube.h"
#include "TextureManager.h"


//for chunk generation
#define NOISE_SCALE 32 // multiplies with the value of the noise -> changes height of mountains
#define MIN_HEIGHT 30 // gets added to the noise -> height of the lowest layer(height has this value if the noise is 0)
#define NOISE_XMUL 3.17f // defines the used section of our perlin noise, higher numbers -> higher frequency of hills
#define NOISE_ZMUL 3.17f
#define CHUNK_DISTANCE 3 // how many chuncks are generated in each direction(dont know minecraft does it like this)
#define DIRT_THICKNESS 10 // should not be bigger than MIN_HEIGHT
class Chunk
{
public:
	int gridPosX, gridPosZ;
	Cube* cubes[16][256][16];
	Chunk* neighbors[4]; // up, right, down, left
	int heightMap[16][16];
	void SetVisibility();
	void Render(TextureManager &textureManager);

	void FillDirtArrays(std::vector<Cube::Vertex>& arrayOfDirtVertices, std::vector<unsigned int>& arrayOfDirtIndices);
	void FillGrassArrays(std::vector<Cube::Vertex>& arrayOfGrassVertices, std::vector<unsigned int>& arrayOfGrassIndices);
	void FillStoneArrays(std::vector<Cube::Vertex>& arrayOfStoneVertices, std::vector<unsigned int>& arrayOfStoneIndices);
	~Chunk();
};
