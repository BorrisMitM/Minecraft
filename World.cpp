#include "World.h"
#include "TerrainGenerator.h"

void World::HandleInput()
{
	camera.HandleInput();
}

void World::Update()
{
	camera.Update();
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


	textureManager.BindTexture(textureManager.cloudTexture);
	for (int i = 0; i < cloudCubes.size(); i++) {
		cloudCubes[i]->Render();
	}
	textureManager.BindTexture(textureManager.dirtTexture);
	for (int i = 0; i < dirtCubes.size(); i++) {
		dirtCubes[i]->Render();
	}
	for (int i = 0; i < chunks.size(); i++) {
		chunks[i]->Render(textureManager);
	}

	//water still to come
}

World::World()
{
	textureManager.LoadTextures();
	TerrainGenerator terrainGenerator;
	for (int x = -CHUNK_DISTANCE; x <= CHUNK_DISTANCE; x++) {
		for (int z = -CHUNK_DISTANCE; z <= CHUNK_DISTANCE; z++) {
			Chunk* newChunk = terrainGenerator.GenerateChunk(x, z);
			newChunk->SetVisibility();
			chunks.push_back(newChunk);
		}
	}
	
}
