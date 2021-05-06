#pragma once
#include "Vector3.h"
#include "World.h"
class Raycast
{
public:
	static Cube* Cast(Vector3 startPos, Vector3 dir, int distance, World& world);
};

