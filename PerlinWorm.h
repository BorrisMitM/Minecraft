#pragma once
#include "Vector3.h"
#include "Chunk.h"
#include "FastNoiseLite.h"

//Contains Data of caves

#define WORM_DISTANCE 3
class PerlinWorm
{
private:
	bool wormData[(WORM_DISTANCE * 2 + 1) * 16][MIN_HEIGHT][(WORM_DISTANCE * 2 + 1) * 16] = { false }; // data of the worm, generating a cave true means air
public:
	Vector3 startPosition; // starting point of the worm
	PerlinWorm(Vector3 position, float length, int wormAmount);
	bool IsCaveAt(Vector3 worldPos);//returns true if a cave is at a certain grid World Position
};

