#include "Chunk.h"

#define BUFFER_OFFSET(i) ((void*)(i))
void Chunk::SetVisibility(int x, int y, int z)
{
	if (cubes[x][y][z] == NULL) return;

	//always render just the top layer of water blocks
	if (cubes[x][y][z]->type == Cube::BlockType::Water) {
		cubes[x][y][z]->SetVisibilty(0, false);
		cubes[x][y][z]->SetVisibilty(1, false);
		cubes[x][y][z]->SetVisibilty(2, false);
		cubes[x][y][z]->SetVisibilty(3, false);
		cubes[x][y][z]->SetVisibilty(4, true);
		cubes[x][y][z]->SetVisibilty(5, true);
		return;
	}

	bool isVisible = true;
	//check for neighbor cubes and set visibility accordingly
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

void Chunk::SetTransparency()
{
	// Iteration looking for water cubes
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			for (int y = MIN_HEIGHT; y <= WATER_LEVEL; y++)
			{
				if (cubes[x][y][z] != NULL && cubes[x][y][z]->type == Cube::BlockType::Water) cubes[x][y][z]->SetTransparency(true);
			}
		}
	}
}


void Chunk::CreateAndFillBuffer()
{
	//refill arrays
	vertices.clear();
	indices.clear();
	FillDirtArrays();
	FillGrassArrays();
	FillStoneArrays();

	//send arrays to OpenGL
	if (vertices.size() == 0) return;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::Vertex) * vertices.size(), &vertices[0].x, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices.front(), GL_DYNAMIC_DRAW);

	//do the same for water
	FillWaterArrays();

	if (waterVertices.size() > 0) {
		glGenBuffers(1, &waterVbo);
		glBindBuffer(GL_ARRAY_BUFFER, waterVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::Vertex) * waterVertices.size(), &waterVertices[0].x, GL_DYNAMIC_DRAW);

		glGenBuffers(1, &waterIbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, waterIbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * waterIndices.size(), &waterIndices.front(), GL_DYNAMIC_DRAW);
	}
}


void Chunk::FillDirtArrays()
{
	//for simplifications sake: every cube that is DIRT_THICKNESS below the heightmap is a dirt block
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			for (int y = heightMap[x][z] - DIRT_THICKNESS; y < heightMap[x][z]; y++)
			{
				if (cubes[x][y][z] != NULL) {
					cubes[x][y][z]->type = Cube::BlockType::Dirt;
					SetVisibility(x, y, z);
					cubes[x][y][z]->AddToBufferArrays(vertices, indices);
				}
			}
		}
	}
}

void Chunk::FillGrassArrays()
{
	//every cube on the top is a grass block
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			if (cubes[x][heightMap[x][z]][z] != NULL) {
				cubes[x][heightMap[x][z]][z]->type = Cube::BlockType::Grass;
				SetVisibility(x, heightMap[x][z], z);
				cubes[x][heightMap[x][z]][z]->AddToBufferArrays(vertices, indices);
			}
		}
	}
}

void Chunk::FillStoneArrays()
{
	//everything below DIRT_THICKNESS is a stone block
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			for (int y = 0; y < heightMap[x][z] - DIRT_THICKNESS; y++)
			{
				if (cubes[x][y][z] != NULL) {
					cubes[x][y][z]->type = Cube::BlockType::Stone;
					SetVisibility(x, y, z);
					cubes[x][y][z]->AddToBufferArrays(vertices, indices);
				}
			}
		}
	}
}

void Chunk::FillWaterArrays()
{
	//water type gets set in the generation already so we only have to check for water type
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			for (int y = MIN_HEIGHT; y <= WATER_LEVEL; y++)
			{
				if (cubes[x][y][z] != NULL && cubes[x][y][z]->type == Cube::BlockType::Water) {
					SetVisibility(x, y, z);
					cubes[x][y][z]->AddToBufferArrays(waterVertices, waterIndices);
				}
			}
		}
	}
}


void Chunk::Render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(0)); // The starting point of the VBO, for the vertices

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(12)); // The starting point of normals, 12 bytes away

	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(24)); // The starting point of texcoords, 24 bytes away
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
}

void Chunk::RenderWater() {
	glBindBuffer(GL_ARRAY_BUFFER, waterVbo);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(0)); // The starting point of the VBO, for the vertices

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(12)); // The starting point of normals, 12 bytes away

	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(24)); // The starting point of texcoords, 24 bytes away
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, waterIbo);

	glDrawElements(GL_TRIANGLES, waterIndices.size(), GL_UNSIGNED_INT, (void*)0);
}

Chunk::~Chunk()
{
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			for (int y = 0; y < 256; y++)
			{
				if (cubes[x][y][z] != NULL) delete(cubes[x][y][z]);
			}
		}
	}
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}
