#include "TerrainGenerator.h"

TerrainGenerator::TerrainGenerator()
{
	noise.SetSeed(0);
	noise.SetFractalOctaves(2);
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	wormNoise.SetSeed(0*3);
	wormNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);


	worms.push_back(new PerlinWorm(Vector3(), 1000, 5));
}

Chunk* TerrainGenerator::GenerateChunk(int gridPosX, int gridPosZ)
{
	Chunk* newChunk = new Chunk();
	newChunk->gridPosX = gridPosX;
	newChunk->gridPosZ = gridPosZ;
	//create noise object

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
					if (!IsCaveAt(Vector3(worldX, i, worldZ))) {
						Cube* cube = new Cube(gridPosX * 16 + x, i, gridPosZ * 16 + z);
						newChunk->cubes[x][i][z] = cube;
						cube->chunk = newChunk;
					}
					else {
						newChunk->cubes[x][i][z] = NULL;
					}
				}
				else 
				{
					Cube* cube = new Cube(gridPosX * 16 + x, i, gridPosZ * 16 + z);
					newChunk->cubes[x][i][z] = cube;
					cube->chunk = newChunk;
				}
			}

			// fill lower crates with water
			for (int y = height; y <= WATER_LEVEL ; y++) {
				Cube* cube = new Cube(gridPosX * 16 + x, y, gridPosZ * 16 + z);
				newChunk->cubes[x][y][z] = cube;
				cube->chunk = newChunk;
				cube->type = Cube::BlockType::Water;
			}
		}
	}


	//generate caves
	return newChunk;
}

void TerrainGenerator::CheckForWorm(int gridX, int gridZ)
{
	float value = wormNoise.GetNoise((float)gridX, (float)gridZ);
	if (value > 0.9f) {
		int wormAmount = (wormNoise.GetNoise((float)gridX * gridZ, 0.0f) * 0.5f + 0.5f) * 4 + 1;
		worms.push_back(new PerlinWorm(Vector3(gridX * 16, 0, gridZ * 16), 1000, wormAmount));
	}
}

bool TerrainGenerator::IsCaveAt(Vector3 position)
{
	for (int i = 0; i < worms.size(); i++)
	{
		if (worms[i]->IsCaveAt(position)) return true;
	}
	return false;
}
