#pragma once
//#include "World.h"
#include "FastNoiseLite.h"
#include <math.h>
#include "Chunk.h"
#include "PerlinWorm.h"
#include "Easing.h"
#include "Vector3i.h"

// Responsible for generating the chunks of the world.
// Also tracks and manages existing PerlinWorms.

class TerrainGenerator
{
private:
	vector<PerlinWorm*> worms;
public:

	//--------------------old generation
	//float heightData[XSIZE][ZSIZE] = { 0.0f };
	//takes world reference to be able to add cubes to it
	//void Generate(World& world);
	//dont use this this is only for presentation purposes
	//void GenerateWrongWorlds(World& world);


	//--------------------Chunk generation
	//Returns a newly generated chunk at the corresponding grid position
	//middle would be (0,0) the one right to it (1,0)
	TerrainGenerator();
	FastNoiseLite noise;
	FastNoiseLite wormNoise;
	Chunk* GenerateChunk(int gridPosX, int gridPosZ, float timeSinceStart); // Generate and returns a chunk based on perlin noise.
	void CheckForWorm(int gridX, int gridZ); // Checks wormNoise map for existance of worms on chunk at (gridX, gridZ) and add them to worms vector.
	void UpdateWorms(int gridX, int gridZ, Vector3i dir); // update the worm array with a new middle points (gridX, gridZ) and a direction we are coming from.
	bool IsCaveAt(Vector3 position); // Verifies whether there's a cave at given position.
};

