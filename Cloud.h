#pragma once
#include "Cube.h"

class Cloud
{

public:

	int gridPosX, gridPosZ;
	Cube* cloudCubes[16][16];
	int cloudHeight; //y-height of the clouds in the world
	float cloudThreshhold; //ranges from 0 - 1

	Cloud();
	~Cloud();

	void GenerateClouds();
	void Update(float deltaTime);
	void FillCloudArrays(std::vector<Cube::Vertex>& arrayOfDirtVertices, std::vector<unsigned int>& arrayOfDirtIndices);
};

