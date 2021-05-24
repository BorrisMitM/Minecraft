#include "Cloud.h"
#include "FastNoiseLite.h"

#define NOISE_XMUL 4.17f // defines the used section of our perlin noise, higher numbers -> higher frequency of hills
#define NOISE_ZMUL 4.17f

Cloud::Cloud()
{
	cloudHeight = 100;
	cloudThreshhold = 0.6f;
	gridPosX = 0;
	gridPosZ = 0;
}

Cloud::~Cloud()
{
}

void Cloud::GenerateClouds()
{
	//create and setup noise class
	FastNoiseLite noise;
	noise.SetSeed(222);
	noise.SetFractalOctaves(2);
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++) //chunk distance * 16
		{
			float noiseValue = noise.GetNoise((float)(x + gridPosX * 16) * NOISE_XMUL,
				(float)(z + gridPosZ * 16) * NOISE_ZMUL) * 0.5f + 0.5f; 


			if (noiseValue >= cloudThreshhold)
			{
				Cube* cloudCube = new Cube(x, cloudHeight, z);
				cloudCubes[x][z] = cloudCube;
			}

		}
	}
}

void Cloud::Update(float deltaTime)
{
	//noiseOffset += windspeed * deltaTime;
	//posOffset += windspeed * deltaTime;
	//move cubes by wind & -playermovement
	//noiseOffset variable(maybeonly in x)
	//if(posOffset > 1) posOffset -= 1; //here you also create a new row of cubes and delete the one on the "right" side
	//destroy the cubes on the right and move each cube one to the right 
	//create on the left with noise foreach (z) if(noise.(gridposX * 16 + noiseOffset, gridposZ * 16 + z)) create cloud or dont
}

void Cloud::FillCloudArrays(std::vector<Cube::Vertex>& arrayOfCloudVertices, std::vector<unsigned int>& arrayOfCloudIndices)
{
	
	/*for (int i = 0; i < cloudCubes.size(); i++)
	{			
		if (cloudCubes[i] != NULL) 
		{
			cloudCubes[i]->AddToBufferArrays(arrayOfCloudVertices, arrayOfCloudIndices);
		}	
	}*/

	
}
