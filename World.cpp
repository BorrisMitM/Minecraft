#include "World.h"
#include "TerrainGenerator.h"

#define BUFFER_OFFSET(i) ((void*)(i))

void World::HandleInput(float dt)
{
	camera.HandleInput(dt);
}

void World::Update(float dt)
{
	camera.Update(dt);
	skybox->SetPosition(camera.getPosition());
}

void World::RenderWorld()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(
		camera.getPosition().x, camera.getPosition().y, camera.getPosition().z,
		camera.getLookAt().x, camera.getLookAt().y, camera.getLookAt().z,
		camera.getUp().x, camera.getUp().y, camera.getUp().z
	);

	skybox->Render(textureManager);


	textureManager.BindTexture(textureManager.dirtTexture);
	glBindBuffer(GL_ARRAY_BUFFER, vboDirt);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(0)); // The starting point of the VBO, for the vertices
	
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(12)); // The starting point of normals, 12 bytes away
	
	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(24)); // The starting point of texcoords, 24 bytes away
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboDirt);
	glDrawElements(GL_TRIANGLES, dirtIndices.size(), GL_UNSIGNED_INT, (void*) 0);

	textureManager.BindTexture(textureManager.grassTexture);
	glBindBuffer(GL_ARRAY_BUFFER, vboGrass); // this does nothing?
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(0)); // The starting point of the VBO, for the vertices
	
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(12)); // The starting point of normals, 12 bytes away
	
	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(24)); // The starting point of texcoords, 24 bytes away
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboGrass); // this does nothing?
	glDrawElements(GL_TRIANGLES, grassIndices.size(), GL_UNSIGNED_INT, (void*)0);

	textureManager.BindTexture(textureManager.stoneTexture);
	glBindBuffer(GL_ARRAY_BUFFER, vboStone);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(0)); // The starting point of the VBO, for the vertices
	
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(12)); // The starting point of normals, 12 bytes away
	
	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(24)); // The starting point of texcoords, 24 bytes away
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboStone);
	glDrawElements(GL_TRIANGLES, stoneIndices.size(), GL_UNSIGNED_INT, (void*)0);

}

World::World()
{
	textureManager.LoadTextures();

	skybox = new Skybox(10.0f);

	TerrainGenerator terrainGenerator;
	terrainGenerator.GenerateWorms();
	for (int x = -CHUNK_DISTANCE; x <= CHUNK_DISTANCE; x++) {
		for (int z = -CHUNK_DISTANCE; z <= CHUNK_DISTANCE; z++) {
			Chunk* newChunk = terrainGenerator.GenerateChunk(x, z);
			newChunk->SetVisibility();
			chunks.push_back(newChunk);

			// filling in buffer arrays
			newChunk->FillDirtArrays(dirtVertices, dirtIndices);
			newChunk->FillGrassArrays(grassVertices, grassIndices);
			newChunk->FillStoneArrays(stoneVertices, stoneIndices);
		}
	}
	CreateBuffers();
}

World::~World()
{
	for (int i = chunks.size() - 1; i >= 0; i--)
	{
		delete(chunks[i]);
	}
}


void World::CreateBuffers()
{
	//grass
	glGenBuffers(1, &vboGrass);
	glBindBuffer(GL_ARRAY_BUFFER, vboGrass);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::Vertex) * grassVertices.size(), &grassVertices[0].x, GL_STATIC_DRAW);

	glGenBuffers(1, &iboGrass);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboGrass);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * grassIndices.size(), &grassIndices.front(), GL_STATIC_DRAW);


	//stone
	glGenBuffers(1, &vboStone);
	glBindBuffer(GL_ARRAY_BUFFER, vboStone);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::Vertex) * stoneVertices.size(), &stoneVertices[0].x, GL_STATIC_DRAW);

	glGenBuffers(1, &iboStone);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboStone);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * stoneIndices.size(), &stoneIndices.front(), GL_STATIC_DRAW);

	//dirt
	glGenBuffers(1, &vboDirt);
	glBindBuffer(GL_ARRAY_BUFFER, vboDirt);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::Vertex) * dirtVertices.size(), &dirtVertices[0].x, GL_STATIC_DRAW);
	glGenBuffers(1, &iboDirt);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboDirt);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * dirtIndices.size(), &dirtIndices.front(), GL_STATIC_DRAW);
}