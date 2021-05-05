#pragma once
#include "Cube.h"

class Cloud
{

public:

	int gridPosX, gridPosZ;
	vector<Cube*> cloudCubes;
	int cloudHeight; //y-height of the clouds in the world
	float cloudThreshhold; //ranges from 0 - 1

	Cloud();
	~Cloud();

	void GenerateClouds();
	void Update();
	void FillCloudArrays(std::vector<Cube::Vertex>& arrayOfDirtVertices, std::vector<unsigned int>& arrayOfDirtIndices);
};

