#pragma once
#include "Cube.h"
#include "FastNoiseLite.h"

class Cloud
{
private:
	void GenerateClouds(float timeSinceStart);
	std::vector<Cube::Vertex> vertices;
	std::vector<unsigned int> indices;

	unsigned int vbo;
	unsigned int ibo;
	float windSpeed = 1.0f;
	float lastMovedDistance;
	static FastNoiseLite noise;
public:

	int gridPosX, gridPosZ;
	Cube* cloudCubes[16][16];
	int cloudHeight; //y-height of the clouds in the world
	float cloudThreshhold; //ranges from 0 - 1

	Cloud(int _gridPosX, int _gridPosZ, float timeSinceStart);
	~Cloud();

	void Update(float deltaTime, float timeSinceStart);
	void Render();
	void FillCloudArrays();
};

