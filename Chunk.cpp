
#include "Chunk.h"

void Chunk::SetVisibility()
{
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 256; y++)
		{
			for (int z = 0; z < 16; z++)
			{
  				if (cubes[x][y][z] == NULL) continue; //extend this only activate the sides that need to, maybe a bool array or sth 
				//this can be used later for destroying blocks and activating neighboring blocks
				if (x <= 0)	 continue;
				if (y <= 0)	 continue;
				if (z <= 0)	 continue;
				if (x >= 15)	 continue;
				if (y >= 255) continue;
				if (z >= 15)	 continue;
				cubes[x][y][z]->SetVisibilty(3, cubes[x - 1][y][z] == NULL);
				cubes[x][y][z]->SetVisibilty(5, cubes[x][y - 1][z] == NULL);
				cubes[x][y][z]->SetVisibilty(2, cubes[x][y][z - 1] == NULL);
				cubes[x][y][z]->SetVisibilty(1, cubes[x + 1][y][z] == NULL);
				cubes[x][y][z]->SetVisibilty(4, cubes[x][y + 1][z] == NULL);
				cubes[x][y][z]->SetVisibilty(0, cubes[x][y][z + 1] == NULL);
				//if (cubes[x - 1][y][z] == NULL) continue;
				//if (cubes[x][y - 1][z] == NULL) continue;
				//if (cubes[x][y][z - 1] == NULL) continue;
				//if (cubes[x + 1][y][z] == NULL) continue;
				//if (cubes[x][y + 1][z] == NULL) continue;
				//if (cubes[x][y][z + 1] == NULL) continue;
				//cubes[x][y][z]->visible = false;
			}
		}
	}
}

void Chunk::Render(TextureManager& textureManager)
{
	//grass
	textureManager.BindTexture(textureManager.grassTexture);
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			cubes[x][heightMap[x][z]][z]->Render();
		}
	}

	//stone
	textureManager.BindTexture(textureManager.stoneTexture);
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			for (int y = 0; y < heightMap[x][z] - DIRT_THICKNESS; y++)
			{
				if (cubes[x][y][z] != NULL) cubes[x][y][z]->Render();
			}
		}
	}

	//dirt
	textureManager.BindTexture(textureManager.dirtTexture);
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			for (int y = heightMap[x][z] - DIRT_THICKNESS; y < heightMap[x][z]; y++)
			{
				if (cubes[x][y][z] != NULL) cubes[x][y][z]->Render();
			}
		}
	}
}
