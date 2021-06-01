#pragma once
#include "Cube.h"

class Cloud
{
private:
	void GenerateClouds();
	std::vector<Cube::Vertex> vertices;
	std::vector<unsigned int> indices;

	unsigned int vbo;
	unsigned int ibo;
public:

	int gridPosX, gridPosZ;
	Cube* cloudCubes[16][16];
	int cloudHeight; //y-height of the clouds in the world
	float cloudThreshhold; //ranges from 0 - 1

	Cloud(int _gridPosX, int _gridPosZ);
	~Cloud();

	void Update(float deltaTime);
	void Render();
	void FillCloudArrays();
};

