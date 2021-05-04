#include "Chunk.h"

void Chunk::SetVisibility()
{
	bool isVisible = true;
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 256; y++)
		{
			for (int z = 0; z < 16; z++)
			{
				if (cubes[x][y][z] == NULL) continue;
				//this can be used later for destroying blocks and activating neighboring blocks
				//if(x > 0)
				//	cubes[x][y][z]->SetVisibilty(3, cubes[x - 1][y][z] == NULL);
				//else cubes[x][y][z]->SetVisibilty(3, true);
				//if(y > 0)
				//	cubes[x][y][z]->SetVisibilty(5, cubes[x][y - 1][z] == NULL);
				//else cubes[x][y][z]->SetVisibilty(5, false);
				//if(z > 0)
				//	cubes[x][y][z]->SetVisibilty(2, cubes[x][y][z - 1] == NULL);
				//else cubes[x][y][z]->SetVisibilty(2, false);
				//if(x < 15)
				//	cubes[x][y][z]->SetVisibilty(1, cubes[x + 1][y][z] == NULL);
				//else cubes[x][y][z]->SetVisibilty(1, false);
				//if(y < 255)
				//	cubes[x][y][z]->SetVisibilty(4, cubes[x][y + 1][z] == NULL);
				//else cubes[x][y][z]->SetVisibilty(4, false);
				//if(z < 15)
				//	cubes[x][y][z]->SetVisibilty(0, cubes[x][y][z + 1] == NULL);
				//else cubes[x][y][z]->SetVisibilty(0, false);

				if (x > 0) {
					isVisible = cubes[x - 1][y][z] == NULL || cubes[x - 1][y][z]->GetTransparency();
					cubes[x][y][z]->SetVisibilty(3, isVisible);
				}
				else if (neighbors[3] != nullptr) {
					isVisible = neighbors[3]->cubes[15][y][z] == NULL || neighbors[3]->cubes[15][y][z]->GetTransparency();
					cubes[x][y][z]->SetVisibilty(3, isVisible); // checking in left neighbor
				}
				else {
					cubes[x][y][z]->SetVisibilty(3, true);
				}

				if (x < 15) {
					isVisible = cubes[x + 1][y][z] == NULL || cubes[x + 1][y][z]->GetTransparency();
					cubes[x][y][z]->SetVisibilty(1, isVisible);
				}
				else if (neighbors[1] != nullptr) {
					isVisible = neighbors[1]->cubes[0][y][z] == NULL || neighbors[1]->cubes[0][y][z]->GetTransparency();
					cubes[x][y][z]->SetVisibilty(1, isVisible); // checking in right neighbor
				}
				else {
					cubes[x][y][z]->SetVisibilty(1, true);
				}

				if (z > 0) {
					isVisible = cubes[x][y][z - 1] == NULL || cubes[x][y][z - 1]->GetTransparency();
					cubes[x][y][z]->SetVisibilty(2, isVisible);
				}
				else if (neighbors[2] != nullptr) {
					isVisible = neighbors[2]->cubes[x][y][15] == NULL || neighbors[2]->cubes[x][y][15]->GetTransparency();
					cubes[x][y][z]->SetVisibilty(2, isVisible); // checking in back neighbor
				}
				else {
					cubes[x][y][z]->SetVisibilty(2, true);
				}

				if (z < 15) {
					isVisible = cubes[x][y][z + 1] == NULL || cubes[x][y][z + 1]->GetTransparency();
					cubes[x][y][z]->SetVisibilty(0, isVisible);
				}
				else if (neighbors[0] != nullptr) {
					isVisible = neighbors[0]->cubes[x][y][0] == NULL || neighbors[0]->cubes[x][y][0]->GetTransparency();
					cubes[x][y][z]->SetVisibilty(0, isVisible); // checking in top neighbor
				}
				else {
					cubes[x][y][z]->SetVisibilty(0, true);
				}


				if (y > 0) {
					isVisible = cubes[x][y - 1][z] == NULL || cubes[x][y - 1][z]->GetTransparency();
					cubes[x][y][z]->SetVisibilty(5, isVisible);
				}
				else {
					cubes[x][y][z]->SetVisibilty(5, false);
				}

				if (y < 255) {
					isVisible = cubes[x][y + 1][z] == NULL || cubes[x][y + 1][z]->GetTransparency();
					cubes[x][y][z]->SetVisibilty(4, isVisible);
				}
				else {
					cubes[x][y][z]->SetVisibilty(4, false);
				}
			}
		}
	}
}

void Chunk::SetTransparency()
{
	// Iteration looking for water cubes
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			for (int y = heightMap[x][z] - DIRT_THICKNESS - 5; y < heightMap[x][z] - DIRT_THICKNESS; y++)
			{
				if (cubes[x][y][z] != NULL) cubes[x][y][z]->SetTransparency(true);
			}
		}
	}
}


void Chunk::FillDirtArrays(std::vector<Cube::Vertex>& arrayOfDirtVertices, std::vector<unsigned int>& arrayOfDirtIndices)
{
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			for (int y = heightMap[x][z] - DIRT_THICKNESS; y < heightMap[x][z]; y++)
			{
				if (cubes[x][y][z] != NULL) {
					cubes[x][y][z]->AddToBufferArrays(arrayOfDirtVertices, arrayOfDirtIndices);
				}
			}
		}
	}
}

void Chunk::FillGrassArrays(std::vector<Cube::Vertex>& arrayOfGrassVertices, std::vector<unsigned int>& arrayOfGrassIndices)
{
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			if (cubes[x][heightMap[x][z]][z] != NULL)
				cubes[x][heightMap[x][z]][z]->AddToBufferArrays(arrayOfGrassVertices, arrayOfGrassIndices);
		}
	}
}

void Chunk::FillStoneArrays(std::vector<Cube::Vertex>& arrayOfStoneVertices, std::vector<unsigned int>& arrayOfStoneIndices)
{
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			for (int y = 0; y < heightMap[x][z] - DIRT_THICKNESS - 5; y++)
			{
				if (cubes[x][y][z] != NULL) cubes[x][y][z]->AddToBufferArrays(arrayOfStoneVertices, arrayOfStoneIndices);
			}
		}
	}
}

void Chunk::FillWaterArrays(std::vector<Cube::Vertex>& arrayOfWaterVertices, std::vector<unsigned int>& arrayOfWaterIndices)
{
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			for (int y = heightMap[x][z] - DIRT_THICKNESS - 5; y < heightMap[x][z] - DIRT_THICKNESS; y++)
			{
				if (cubes[x][y][z] != NULL) cubes[x][y][z]->AddToBufferArrays(arrayOfWaterVertices, arrayOfWaterIndices);
			}
		}
	}
}


Chunk::~Chunk()
{
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			for (int y = 0; y < 256; y++)
			{
				//if (cubes[x][y][z] != NULL) delete(cubes[x][y][z]);
			}
		}
	}
}


void Chunk::Render(TextureManager& textureManager)
{
	//grass
	// injected vbo (not created here)
	// injected ibo (not created here)
	// iterate to find grass
		// cube->addToVertexBuffer(&buffer)
		// cube->addToIndexBuffer(&buffer)

	// bind texture
	// send buffer to gpu



	//grass
	//textureManager.BindTexture(textureManager.grassTexture);
	//for (int x = 0; x < 16; x++)
	//{
	//	for (int z = 0; z < 16; z++)
	//	{
	//		if(cubes[x][heightMap[x][z]][z] != NULL)
	//			cubes[x][heightMap[x][z]][z]->Render();
	//	}
	//}

	////stone
	//textureManager.BindTexture(textureManager.stoneTexture);
	//for (int x = 0; x < 16; x++)
	//{
	//	for (int z = 0; z < 16; z++)
	//	{
	//		for (int y = 0; y < heightMap[x][z] - DIRT_THICKNESS; y++)
	//		{
	//			if (cubes[x][y][z] != NULL) cubes[x][y][z]->Render();
	//		}
	//	}
	//}

	////dirt
	//textureManager.BindTexture(textureManager.dirtTexture);
	//for (int x = 0; x < 16; x++)
	//{
	//	for (int z = 0; z < 16; z++)
	//	{
	//		for (int y = heightMap[x][z] - DIRT_THICKNESS; y < heightMap[x][z]; y++)
	//		{
	//			if (cubes[x][y][z] != NULL) cubes[x][y][z]->Render();
	//		}
	//	}
	//}
}
