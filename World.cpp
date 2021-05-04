#include "World.h"

#define BUFFER_OFFSET(i) ((void*)(i))

void World::HandleInput(float dt)
{
	camera.HandleInput(dt);
}

void World::Update(float dt)
{
	camera.Update(dt);
	skybox->SetPosition(camera.getPosition());


	//this can be commented in and out, later will be replaced for other player position
	playerPosition = camera.getPosition();
	//calculate if player is still in the current chunk
	//a chunk has a grid position and reaches 16 units into x and z 

	Vector3 chunkOriginWorldPosition = Vector3(currentChunk->gridPosX * 16, 0, currentChunk->gridPosZ * 16);
	if (playerPosition.x < chunkOriginWorldPosition.x 
		|| playerPosition.z < chunkOriginWorldPosition.z 
		|| playerPosition.x >= chunkOriginWorldPosition.x + 16 
		|| playerPosition.z >= chunkOriginWorldPosition.z + 16)
	{
		Vector3i newChunkDirection = Vector3i();
		//find new Chunk 
		for (int i = 0; i < chunks.size(); i++)
		{
			if(playerPosition.x >= chunks[i]->gridPosX * 16
				&& playerPosition.z >= chunks[i]->gridPosZ * 16
				&& playerPosition.x < chunks[i]->gridPosX * 16 + 16
				&& playerPosition.z < chunks[i]->gridPosZ * 16 + 16)
			{
				newChunkDirection = Vector3i(chunks[i]->gridPosX - currentChunk->gridPosX, 0, chunks[i]->gridPosZ - currentChunk->gridPosZ);
				currentChunk = chunks[i];
				//cout << "New Current Chunk Position:" << currentChunk->gridPosX << ", " << currentChunk->gridPosZ << "PlayerPos: " << playerPosition.x << ", " << playerPosition.z << endl;
				break;
			}
		}
		//delete far away chunks
		for (int i = chunks.size()-1; i >= 0; i--)
		{
			if (abs(chunks[i]->gridPosX - currentChunk->gridPosX) > CHUNK_DISTANCE
				|| abs(chunks[i]->gridPosZ - currentChunk->gridPosZ) > CHUNK_DISTANCE) 
			{
				//cout << "Deleted Chunk at: " << chunks[i]->gridPosX << ", " << chunks[i]->gridPosZ << endl;
				Chunk* deleteThisChunk = chunks[i];
				chunks.erase(chunks.begin() + i); // pointer stuff
				delete(deleteThisChunk);
			}
		}

		// add new chunks in
		// get the direction of the new chunk(lets first only do straight ones)
		// add new row of chunks
		//only do it for one direction first
		if (newChunkDirection.x != 0) {
			for (int i = -CHUNK_DISTANCE; i <= CHUNK_DISTANCE; i++) {
				Chunk* newChunk = terrainGenerator.GenerateChunk(currentChunk->gridPosX + newChunkDirection.x * CHUNK_DISTANCE, currentChunk->gridPosZ + i);
				chunks.push_back(newChunk);
			}
		}
		if (newChunkDirection.z != 0) {
			for (int i = -CHUNK_DISTANCE; i <= CHUNK_DISTANCE; i++) {
				Chunk* newChunk = terrainGenerator.GenerateChunk(currentChunk->gridPosX + i, currentChunk->gridPosZ + newChunkDirection.z * CHUNK_DISTANCE);
				chunks.push_back(newChunk);
			}
		}
		CalculateNeighbors();

		GetBufferDataFromChunks();

		UpdateBuffers();
	}
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


	BindBuffer(vboDirt, iboDirt, textureManager.dirtTexture);
	glDrawElements(GL_TRIANGLES, dirtIndices.size(), GL_UNSIGNED_INT, (void*) 0);

	BindBuffer(vboGrass, iboGrass, textureManager.grassTexture);
	glDrawElements(GL_TRIANGLES, grassIndices.size(), GL_UNSIGNED_INT, (void*)0);

	BindBuffer(vboStone, iboStone, textureManager.stoneTexture);
	glDrawElements(GL_TRIANGLES, stoneIndices.size(), GL_UNSIGNED_INT, (void*)0);

	BindBuffer(vboWater, iboWater, textureManager.waterTexture);
	glDrawElements(GL_TRIANGLES, waterIndices.size(), GL_UNSIGNED_INT, (void*)0);
}

World::World()
{
	textureManager.LoadTextures();

	skybox = new Skybox(10.0f);
	//TerrainGenerator terrainGenerator;
	terrainGenerator.GenerateWorms();
	for (int x = -CHUNK_DISTANCE; x <= CHUNK_DISTANCE; x++) {
		for (int z = -CHUNK_DISTANCE; z <= CHUNK_DISTANCE; z++) {
			Chunk* newChunk = terrainGenerator.GenerateChunk(x, z);
			//newChunk->SetVisibility();
			newChunk->SetTransparency();
			chunks.push_back(newChunk);
			if (newChunk->gridPosX == 0 && newChunk->gridPosZ == 0) currentChunk = newChunk;
		}
	}
	CalculateNeighbors();

	GetBufferDataFromChunks();

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::Vertex) * grassVertices.size(), &grassVertices[0].x, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &iboGrass);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboGrass);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * grassIndices.size(), &grassIndices.front(), GL_DYNAMIC_DRAW);


	//stone
	glGenBuffers(1, &vboStone);
	glBindBuffer(GL_ARRAY_BUFFER, vboStone);
	if(stoneVertices.size() > 0)
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::Vertex) * stoneVertices.size(), &stoneVertices[0].x, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &iboStone);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboStone);
	if(stoneIndices.size()>0)
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * stoneIndices.size(), &stoneIndices.front(), GL_DYNAMIC_DRAW);

	//dirt
	glGenBuffers(1, &vboDirt);
	glBindBuffer(GL_ARRAY_BUFFER, vboDirt);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::Vertex) * dirtVertices.size(), &dirtVertices[0].x, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &iboDirt);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboDirt);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * dirtIndices.size(), &dirtIndices.front(), GL_DYNAMIC_DRAW);

	// water
	glGenBuffers(1, &vboWater);
	glBindBuffer(GL_ARRAY_BUFFER, vboWater);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::Vertex) * waterVertices.size(), &waterVertices[0].x, GL_DYNAMIC_DRAW);
	
	glGenBuffers(1, &iboWater);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboWater);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * waterIndices.size(), &waterIndices.front(), GL_DYNAMIC_DRAW);
}

void World::UpdateBuffers()
{
	float startTime = glfwGetTime();
	//grass
	glBindBuffer(GL_ARRAY_BUFFER, vboGrass);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::Vertex) * grassVertices.size(), &grassVertices[0].x, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboGrass);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * grassIndices.size(), &grassIndices.front(), GL_DYNAMIC_DRAW);


	//stone
	glBindBuffer(GL_ARRAY_BUFFER, vboStone);
	if (stoneVertices.size() > 0)
		glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::Vertex) * stoneVertices.size(), &stoneVertices[0].x, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboStone);
	if (stoneIndices.size() > 0)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * stoneIndices.size(), &stoneIndices.front(), GL_DYNAMIC_DRAW);

	//dirt
	glBindBuffer(GL_ARRAY_BUFFER, vboDirt);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::Vertex) * dirtVertices.size(), &dirtVertices[0].x, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboDirt);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * dirtIndices.size(), &dirtIndices.front(), GL_DYNAMIC_DRAW);
	cout << "Time to Update Buffers: " << glfwGetTime() - startTime << endl;
}

void World::CalculateNeighbors()
{
	float startTime = glfwGetTime();
	for (int i = 0; i < chunks.size(); i++)
	{
		//find neighbors for each chunk
		int gridPosX = chunks[i]->gridPosX;
		int gridPosZ = chunks[i]->gridPosZ;
		chunks[i]->neighbors[0] = NULL;
		chunks[i]->neighbors[1] = NULL;
		chunks[i]->neighbors[2] = NULL;
		chunks[i]->neighbors[3] = NULL;
		for (int j = 0; j < chunks.size(); j++)
		{
			// up, right, down, left
			if (gridPosX == chunks[j]->gridPosX && gridPosZ + 1 == chunks[j]->gridPosZ) chunks[i]->neighbors[0] = chunks[j];
			if (gridPosX + 1 == chunks[j]->gridPosX && gridPosZ == chunks[j]->gridPosZ) chunks[i]->neighbors[1] = chunks[j];
			if (gridPosX == chunks[j]->gridPosX && gridPosZ - 1 == chunks[j]->gridPosZ) chunks[i]->neighbors[2] = chunks[j];
			if (gridPosX - 1 == chunks[j]->gridPosX && gridPosZ == chunks[j]->gridPosZ) chunks[i]->neighbors[3] = chunks[j];
		}
	}
	cout << "Time to Calculate Neighbors: " << glfwGetTime() - startTime << endl;
}

void World::GetBufferDataFromChunks()
{
	float startTime = glfwGetTime();
	dirtVertices.clear();
	dirtIndices.clear();
	grassIndices.clear();
	grassVertices.clear();
	stoneVertices.clear();
	stoneIndices.clear();
	for (int i = 0; i < chunks.size(); i++) {
		chunks[i]->SetVisibility();

		// filling in buffer arrays
		chunks[i]->FillDirtArrays(dirtVertices, dirtIndices);
		chunks[i]->FillGrassArrays(grassVertices, grassIndices);
		chunks[i]->FillStoneArrays(stoneVertices, stoneIndices);
		chunks[i]->FillWaterArrays(waterVertices, waterIndices);
	}
	cout << "Time to get the Buffer Data from the chunks: " << glfwGetTime() - startTime << endl;
}

void World::BindBuffer(unsigned int vbo, unsigned int ibo, unsigned int texture)
{
	textureManager.BindTexture(texture);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(0)); // The starting point of the VBO, for the vertices

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(12)); // The starting point of normals, 12 bytes away

	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Cube::Vertex), BUFFER_OFFSET(24)); // The starting point of texcoords, 24 bytes away
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}
