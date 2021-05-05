#include "Cloud.h"
#include "FastNoiseLite.h"

#define NOISE_XMUL 5.17f // defines the used section of our perlin noise, higher numbers -> higher frequency of hills
#define NOISE_ZMUL 5.17f

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

	for (int x = -50; x < 50; x++)
	{
		for (int z = -50; z < 50; z++) //chunk distance * 16
		{
			float noiseValue = noise.GetNoise((float)(x) * NOISE_XMUL,
				(float)(z) * NOISE_ZMUL) * 0.5f + 0.5f; 


			if (noiseValue >= cloudThreshhold)
			{
				Cube* cloudCube = new Cube(x, cloudHeight, z);
				cloudCubes.push_back(cloudCube);
			}

		}
	}
}

void Cloud::Update()
{
	//move clouds etc
}

void Cloud::FillCloudArrays(std::vector<Cube::Vertex>& arrayOfCloudVertices, std::vector<unsigned int>& arrayOfCloudIndices)
{
	
	for (int i = 0; i < cloudCubes.size(); i++)
	{			
		if (cloudCubes[i] != NULL) 
		{
			cloudCubes[i]->AddToBufferArrays(arrayOfCloudVertices, arrayOfCloudIndices);
		}	
	}

	
}
