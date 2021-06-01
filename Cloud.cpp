#include "Cloud.h"

#define NOISE_XMUL 4.17f // defines the used section of our perlin noise, higher numbers -> higher frequency of hills
#define NOISE_ZMUL 4.17f

#define BUFFER_OFFSET(i) ((void*)(i))

FastNoiseLite Cloud::noise;

Cloud::Cloud(int _gridPosX, int _gridPosZ, float timeSinceStart)
{
	cloudHeight = 100;
	cloudThreshhold = 0.6f;
	gridPosX = _gridPosX;
	gridPosZ = _gridPosZ;
	GenerateClouds(timeSinceStart);
}


Cloud::~Cloud()
{
}

void Cloud::GenerateClouds(float timeSinceStart)
{
	//create and setup noise class
	//FastNoiseLite noise;
	noise.SetSeed(222);
	noise.SetFractalOctaves(2);
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	float movedDistance = timeSinceStart * windSpeed;
	float flooredMovedDistance = floor(movedDistance);
	float fract = movedDistance - flooredMovedDistance;
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++) //chunk distance * 16
		{
			float noiseValue = noise.GetNoise((float)(x + gridPosX * 16 - flooredMovedDistance) * NOISE_XMUL,
				(float)(z + gridPosZ * 16) * NOISE_ZMUL) * 0.5f + 0.5f; 


			if (noiseValue >= cloudThreshhold)
			{
				Cube* cloudCube = new Cube(x + gridPosX * 16 + movedDistance, cloudHeight, z + gridPosZ * 16);
				cloudCubes[x][z] = cloudCube;
			}
			else cloudCubes[x][z] = NULL;

		}
	}
	FillCloudArrays();
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	if (vertices.size() == 0) return;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::Vertex) * vertices.size(), &vertices[0].x, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices.front(), GL_DYNAMIC_DRAW);
}

void Cloud::Update(float deltaTime, float timeSinceStart)
{
	//clouds only move in x direction
	float movedDistance = timeSinceStart * windSpeed;
	float flooredMovedDistance = floor(movedDistance);
	float fract = modf(movedDistance, &flooredMovedDistance);
	
	if (flooredMovedDistance > lastMovedDistance) {
		for (int z = 0; z < 16; z++)
		{
			Cube* cubeToDelete = cloudCubes[15][z];
			cloudCubes[15][z] = NULL;
			delete(cubeToDelete);
		}
		for (int x = 15; x > 0; x--)
		{
			for (int z = 0; z < 16; z++)
			{
				cloudCubes[x][z] = cloudCubes[x-1][z];
				if(cloudCubes[x][z] != NULL)
					cloudCubes[x][z]->position.x += 1.0f;
			}
		}
		for (int z = 0; z < 16; z++) //chunk distance * 16
		{
			float noiseValue = noise.GetNoise((float)(gridPosX * 16 - flooredMovedDistance) * NOISE_XMUL,
				(float)(z + gridPosZ * 16) * NOISE_ZMUL) * 0.5f + 0.5f;


			if (noiseValue >= cloudThreshhold)
			{
				Cube* cloudCube = new Cube(gridPosX * 16 + fract, cloudHeight, z + gridPosZ * 16);
				cloudCubes[0][z] = cloudCube;
			}
			else cloudCubes[0][z] = NULL;
		}
	}
	lastMovedDistance = movedDistance;
	vertices.clear();
	indices.clear();
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			if (cloudCubes[x][z] != NULL)
			{
				cloudCubes[x][z]->AddToBufferArrays(vertices, indices, fract);
			}
		}
	}

	if (vertices.size() == 0) return;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::Vertex) * vertices.size(), &vertices[0].x, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices.front(), GL_DYNAMIC_DRAW);
	//noiseOffset += windspeed * deltaTime;
	//posOffset += windspeed * deltaTime;
	//move cubes by wind & -playermovement
	//noiseOffset variable(maybeonly in x)
	//if(posOffset > 1) posOffset -= 1; //here you also create a new row of cubes and delete the one on the "right" side
	//destroy the cubes on the right and move each cube one to the right 
	//create on the left with noise foreach (z) if(noise.(gridposX * 16 + noiseOffset, gridposZ * 16 + z)) create cloud or dont


	
}

void Cloud::Render()
{
	if (vertices.size() == 0) return;
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

void Cloud::FillCloudArrays()
{
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			if (cloudCubes[x][z] != NULL)
			{
				cloudCubes[x][z]->AddToBufferArrays(vertices, indices);
			}
		}
	}
}
