#include "TerrainGenerator.h"

void TerrainGenerator::Generate(World& world)
{
	// Create and configure FastNoise object
	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	// Gather noise data
	//basically we create an array of the size of the world and 
	//fill that with a value from the noise object multipied by a constant height multiplicator 
	//since the noise is from -1 to 1 I scale it to 0 to 1
	
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			heightData[x][z] = round((noise.GetNoise((float)x * NOISE_XMUL, (float)z * NOISE_ZMUL) * 0.5f + 0.5f)*HEIGHT);
		}
	}
	//add cubes to world
	int cubeCount = 0;
	for (int z = 0; z < XSIZE; z++)
	{
		for (int x = 0; x < ZSIZE; x++)
		{
			//check for minheight of this position taking neighbors into account, to prevent holes
			int minHeight = heightData[x][z];
			if ( x < XSIZE - 1 && minHeight - 1 > heightData[x + 1][z]) minHeight = heightData[x + 1][z];
			if ( x > 0 && minHeight - 1 > heightData[x - 1][z]) minHeight = heightData[x - 1][z];
			if ( z < ZSIZE - 1 && minHeight - 1 > heightData[x][z + 1]) minHeight = heightData[x][z + 1];
			if ( z > 0 && minHeight - 1 > heightData[x][z - 1]) minHeight = heightData[x][z - 1];
			//start from minHeight, to prevent additional blocks, that are not visible from the top
			for (int y = minHeight; y <= heightData[x][z]; y++) {
				Cube* cube = new Cube(x - XSIZE / 2.0f, y, z - ZSIZE / 2.0f);
				world.dirtCubes.push_back(cube);
			}
		}
	}
	//GenerateWrongWorlds(world);
}

void TerrainGenerator::GenerateWrongWorlds(World& world)
{
	//full spawn
	for (int z = 0; z < XSIZE; z++)
	{
		for (int x = 0; x < ZSIZE; x++)
		{
			for (int y = 0; y <= heightData[x][z]; y++) {
				Cube* cube = new Cube(XSIZE + 3 + x - XSIZE / 2.0f, y, z - ZSIZE / 2.0f);
				world.dirtCubes.push_back(cube);
			}
		}
	}

	//only top layer
	for (int z = 0; z < XSIZE; z++)
	{
		for (int x = 0; x < ZSIZE; x++)
		{
			Cube* cube = new Cube(-XSIZE - 3 + x - XSIZE / 2.0f, heightData[x][z], z - ZSIZE / 2.0f);
			world.dirtCubes.push_back(cube);
		}
	}
}

Chunk* TerrainGenerator::GenerateChunk(int gridPosX, int gridPosZ)
{
	Chunk* newChunk = new Chunk();
	newChunk->gridPosX = gridPosX;
	newChunk->gridPosZ = gridPosZ;
	//create noise object
	FastNoiseLite noise;
	noise.SetSeed(222);
	noise.SetFractalOctaves(2);
	//noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			//calculate height of the current position in the chunk
			int height = round(Easing::EaseOut((noise.GetNoise((float)(x + gridPosX * 16) * NOISE_XMUL, 
											   (float)(z + gridPosZ * 16) * NOISE_ZMUL) * 0.5f + 0.5f)) * NOISE_SCALE + MIN_HEIGHT);
			newChunk->heightMap[x][z] = height;
			//fill position with dirt cubes till height is reached
			for (int i = 0; i <= height; i++) {
				int worldX = x + gridPosX * 16;
				int worldZ = z + gridPosZ * 16;
				if (i < MIN_HEIGHT) {
					if (!worm->IsCaveAt(Vector3(worldX, i, worldZ))) {
						Cube* cube = new Cube(gridPosX * 16 + x, i, gridPosZ * 16 + z);
						newChunk->cubes[x][i][z] = cube;
					}
					else {
						newChunk->cubes[x][i][z] = NULL;
					}
				}
				else 
				{
					Cube* cube = new Cube(gridPosX * 16 + x, i, gridPosZ * 16 + z);
					newChunk->cubes[x][i][z] = cube;
				}
			}
		}
	}
	//generate caves
	return newChunk;
}

void TerrainGenerator::GenerateWorms()
{
	worm = new PerlinWorm();
}
