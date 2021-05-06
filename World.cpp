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
		float time = glfwGetTime();
		
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
		cout << "Time to delete far chunks: " << glfwGetTime() - time << endl;
		time = glfwGetTime();
		// add new chunks in
		// get the direction of the new chunk
		// add new row of chunks
		vector<Chunk*> newChunks;
		if (newChunkDirection.x != 0) {
			for (int i = -CHUNK_DISTANCE; i <= CHUNK_DISTANCE; i++) {
				Chunk* newChunk = terrainGenerator.GenerateChunk(currentChunk->gridPosX + newChunkDirection.x * CHUNK_DISTANCE, currentChunk->gridPosZ + i);
				chunks.push_back(newChunk); 
				newChunks.push_back(newChunk);
			}
		}
		if (newChunkDirection.z != 0) {
			for (int i = -CHUNK_DISTANCE; i <= CHUNK_DISTANCE; i++) {
				Chunk* newChunk = terrainGenerator.GenerateChunk(currentChunk->gridPosX + i, currentChunk->gridPosZ + newChunkDirection.z * CHUNK_DISTANCE);
				chunks.push_back(newChunk);
				newChunks.push_back(newChunk);
			}
		}
		cout << "Time to create new Chunks on CPU: " << glfwGetTime() - time << endl;
		time = glfwGetTime();
		CalculateNeighbors();
		//add new chunks to buffer array
		for (int i = 0; i < newChunks.size(); i++) {
			newChunks[i]->CreateAndFillBuffer();
		}


		cout << "Time to create and fill " << newChunks.size() << " new Buffers: " << glfwGetTime() - time << endl;
		//SetChunkBufferData();

		//UpdateBuffers();
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

	textureManager.BindTexture(textureManager.chunkAtlas);
	for (int i = 0; i < chunks.size(); i++) {
		chunks[i]->Render();
	}
	BindBuffer(vboCloud, iboCloud, textureManager.cloudTexture);
	glDrawElements(GL_TRIANGLES, waterIndices.size(), GL_UNSIGNED_INT, (void*)0);
}

World::World()
{
	textureManager.LoadTextures();

	skybox = new Skybox(10.0f);
	terrainGenerator.GenerateWorms();

	cloudGen.GenerateClouds();
	cloudGen.FillCloudArrays(cloudVertices, cloudIndices);
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

	for (int i = 0; i < chunks.size(); i++) {
		chunks[i]->CreateAndFillBuffer();
	}

	CreateCloudBuffers();
}


World::~World()
{
	for (int i = chunks.size() - 1; i >= 0; i--)
	{
		delete(chunks[i]);
	}
}


void World::CreateCloudBuffers()
{
	// cloud
	glGenBuffers(1, &vboCloud);
	glBindBuffer(GL_ARRAY_BUFFER, vboCloud);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::Vertex) * cloudVertices.size(), &cloudVertices[0].x, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &iboCloud);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboCloud);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * cloudIndices.size(), &cloudIndices.front(), GL_DYNAMIC_DRAW);
}

void World::UpdateBuffers()
{
	//clouds
	glBindBuffer(GL_ARRAY_BUFFER, vboCloud);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::Vertex) * cloudVertices.size(), &cloudVertices[0].x, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboCloud);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * cloudIndices.size(), &cloudIndices.front(), GL_DYNAMIC_DRAW);
}

void World::CalculateNeighbors()
{
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
