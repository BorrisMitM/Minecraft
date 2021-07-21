#pragma once
#include "World.h"

// Our own raycast to verify collision with the world.
// Has two types:
// - A normal linear raycast that verifies collision with cubes on a straight line
// - A cylinder cast that verifies collision with cubes around a specific point

// The raycasts assume a world exactly like ours.

class Raycast
{
	static bool IntersectPoint(Vector3 rayVector, Vector3 rayPoint, Vector3 planeNormal, Vector3 planePoint, Vector3& intersectionPoint);
public:
	
	// A struct to hold the cube that was hit by a raycast, the point that was hit and the normal of the face that was hit.
	struct CollisionInfo {
		Vector3 normal;
		Vector3 point;
		Cube* cube;
	};
	static Cube* Cast(Vector3 startPos, Vector3 dir, int distance, World& world);
	static bool CylinderCast(Vector3 startPos, float upExtend, float downExtend, float radius, World& world, vector<CollisionInfo>& collisionInfo );
	static Cube* GetRelativeCube(int x, int y, int z, Chunk* chunk);
};

