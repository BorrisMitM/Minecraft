#pragma once
#include "World.h"
class Raycast
{
	static bool IntersectPoint(Vector3 rayVector, Vector3 rayPoint, Vector3 planeNormal, Vector3 planePoint, Vector3& intersectionPoint);
public:
	struct CollisionInfo {
		Vector3 normal;
		Vector3 point;
		Cube* cube;
	};
	static Cube* Cast(Vector3 startPos, Vector3 dir, int distance, World& world);
	static bool CylinderCast(Vector3 startPos, float upExtend, float downExtend, float radius, World& world, vector<CollisionInfo>& collisionInfo );
	static Cube* GetRelativeCube(int x, int y, int z, Chunk* chunk);
};

