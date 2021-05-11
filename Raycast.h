#pragma once
#include "World.h"
class Raycast
{
	static bool IntersectPoint(Vector3 rayVector, Vector3 rayPoint, Vector3 planeNormal, Vector3 planePoint, Vector3& intersectionPoint);
public:
	static Cube* Cast(Vector3 startPos, Vector3 dir, int distance, World& world);
};

