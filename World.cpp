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

	/*textureManager.BindTexture(textureManager.cloudTexture);
	for (int i = 0; i < cloudCubes.size(); i++) {
		cloudCubes[i]->Render();
	}
	textureManager.BindTexture(textureManager.dirtTexture);
	for (int i = 0; i < dirtCubes.size(); i++) {
		dirtCubes[i]->Render();
	}*/
	//for (int i = 0; i < chunks.size(); i++) {
	//	chunks[i]->Render(textureManager);
	//}

	textureManager.BindTexture(textureManager.dirtTexture);
	glDrawElements(GL_TRIANGLES, dirtIndices.size(), GL_UNSIGNED_INT, (void*) 0);

	//water still to come
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
			//newChunk->SetVisibility();
			chunks.push_back(newChunk);

			// filling in buffer arrays
			newChunk->FillDirtArrays(dirtVertices, dirtIndices);
		}
	}


	//Cube cube(Vector3(0, 10, 0));
	//cube.AddToBufferArrays(dirtVertices, dirtIndices);

	// create buffers
	glGenBuffers(1, &vboDirt);
	glBindBuffer(GL_ARRAY_BUFFER, vboDirt);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::Vertex) * dirtVertices.size(), &dirtVertices[0].x, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(0)); // The starting point of the VBO, for the vertices

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(12)); // The starting point of normals, 12 bytes away

	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(24)); // The starting point of texcoords, 24 bytes away


	glGenBuffers(1, &iboDirt);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboDirt);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * dirtIndices.size(), &dirtIndices.front(), GL_STATIC_DRAW);
}
