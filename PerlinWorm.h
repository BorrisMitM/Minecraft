#pragma once
#include "Vector3.h"
#include "Chunk.h"
#include "FastNoiseLite.h"
#define WORM_DISTANCE 4
class PerlinWorm
{
private:
	bool wormData[(WORM_DISTANCE * 2 + 1) * 16][MIN_HEIGHT][(WORM_DISTANCE * 2 + 1) * 16] = { false }; // data of the worm, generating a cave true means air
	Vector3 startPosition; // starting point of the 
public:
	PerlinWorm(Vector3 position, float length);
	bool IsCaveAt(Vector3 worldPos);
};

