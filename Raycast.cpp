#include "Raycast.h"
//https://rosettacode.org/wiki/Find_the_intersection_of_a_line_with_a_plane#C.2B.2B but modified
bool Raycast::IntersectPoint(Vector3 rayVector, Vector3 rayPoint, Vector3 planeNormal, Vector3 planePoint, Vector3& intersectionPoint) {
	double prod2 = rayVector.dot(planeNormal);
	if (prod2 >= 0 ) return false;
	Vector3 diff = rayPoint - planePoint;
	double prod1 = diff.dot(planeNormal);
	double prod3 = prod1 / prod2;
	intersectionPoint = rayPoint - rayVector * prod3;
	return true;
}
Cube* Raycast::Cast(Vector3 startPos, Vector3 dir, int distance, World& world)
{
	Vector3 offset = Vector3(.5f, .5f, -.5f);
	vector<Cube*> cubes;
	Vector3i startPosIndex(startPos.x, startPos.y, startPos.z);
	startPosIndex.x = startPosIndex.x - world.currentChunk->gridPosX * 16;
	startPosIndex.z = startPosIndex.z - world.currentChunk->gridPosZ * 16;


	//if (startPosIndex.x < 0) {
	//	startPosIndex.x = 15 + startPosIndex.x % 16;
	//}
	//else startPosIndex.x %= 16;
	//if (startPosIndex.z < 0) {
	//	startPosIndex.z = 15 + startPosIndex.z % 16;
	//}
	//else startPosIndex.z %= 16;


	Chunk* chunkToGetTheCubeFrom;
	Vector3i cubePosInChunk;
	//Get all the cubes in distance
	for (int x = startPosIndex.x - distance; x <= startPosIndex.x + distance; x++) {
		for (int y = startPosIndex.y - distance; y <= startPosIndex.y + distance; y++) {
			for (int z = startPosIndex.z - distance; z <= startPosIndex.z + distance; z++) {
				cubePosInChunk.x = x;
				cubePosInChunk.y = y;
				cubePosInChunk.z = z;
				//check for chunk to get the cube from
				if (x < 0) {
					chunkToGetTheCubeFrom = world.currentChunk->neighbors[3];
					cubePosInChunk.x += 16;
				}
				else if (x >= 16) {
					chunkToGetTheCubeFrom = world.currentChunk->neighbors[1];
					cubePosInChunk.x -= 16;
				}
				else chunkToGetTheCubeFrom = world.currentChunk;

				if (z < 0) {
					chunkToGetTheCubeFrom = chunkToGetTheCubeFrom->neighbors[2];
					cubePosInChunk.z += 16;
				}
				else if (z >= 16) {
					chunkToGetTheCubeFrom = chunkToGetTheCubeFrom->neighbors[0];
					cubePosInChunk.z -= 16;
				}
				Cube* cubeToAdd = chunkToGetTheCubeFrom->cubes[cubePosInChunk.x][cubePosInChunk.y][cubePosInChunk.z];
				if(cubeToAdd != nullptr)
					cubes.push_back(cubeToAdd);
			}
		}
	}
	vector<Cube*> hitCubes;
	//do the math
	for (int i = 0; i < cubes.size(); i++)
	{
		if (cubes[i] == NULL) continue;
		//for the top side
		if (cubes[i]->position.y + 1.0f < startPos.y) {
			Vector3 intersectionPoint(0,0,0);
			if (IntersectPoint(dir, startPos, Vector3(0, 1, 0), cubes[i]->position + Vector3(0, 1, 0), intersectionPoint)) {
				if (intersectionPoint.x >= cubes[i]->position.x && intersectionPoint.x < cubes[i]->position.x + 1.0f &&
					intersectionPoint.z <= cubes[i]->position.z && intersectionPoint.z > cubes[i]->position.z - 1.0f)
					hitCubes.push_back(cubes[i]);
  			}
		}
		//for the bottom side
		if (cubes[i]->position.y > startPos.y) {
			Vector3 intersectionPoint(0, 0, 0);
			if (IntersectPoint(dir, startPos, Vector3(0, -1, 0), cubes[i]->position, intersectionPoint)) {
				if (intersectionPoint.x >= cubes[i]->position.x && intersectionPoint.x < cubes[i]->position.x + 1.0f &&
					intersectionPoint.z <= cubes[i]->position.z && intersectionPoint.z > cubes[i]->position.z - 1.0f)
					hitCubes.push_back(cubes[i]);
			}
		}
		//for the left side
		if (cubes[i]->position.x > startPos.x) {
			Vector3 intersectionPoint(0, 0, 0);
			if (IntersectPoint(dir, startPos, Vector3(-1, 0, 0), cubes[i]->position, intersectionPoint)) {
				if (intersectionPoint.y >= cubes[i]->position.y && intersectionPoint.y < cubes[i]->position.y + 1.0f &&
					intersectionPoint.z <= cubes[i]->position.z && intersectionPoint.z > cubes[i]->position.z - 1.0f)
					hitCubes.push_back(cubes[i]);
			}
		}
		//for the right side
		if (cubes[i]->position.x + 1.0f< startPos.x) {
			Vector3 intersectionPoint(0, 0, 0);
			if (IntersectPoint(dir, startPos, Vector3(1, 0, 0), cubes[i]->position + Vector3(1, 0, 0), intersectionPoint)) {
				if (intersectionPoint.y >= cubes[i]->position.y && intersectionPoint.y < cubes[i]->position.y + 1.0f &&
					intersectionPoint.z <= cubes[i]->position.z && intersectionPoint.z > cubes[i]->position.z - 1.0f)
					hitCubes.push_back(cubes[i]);
			}
		}
		//for the front side
		if (cubes[i]->position.z < startPos.z) {
			Vector3 intersectionPoint(0, 0, 0);
			if (IntersectPoint(dir, startPos, Vector3(0, 0, 1), cubes[i]->position, intersectionPoint)) {
				if (intersectionPoint.y >= cubes[i]->position.y && intersectionPoint.y < cubes[i]->position.y + 1.0f &&
					intersectionPoint.x >= cubes[i]->position.x && intersectionPoint.x < cubes[i]->position.x + 1.0f)
					hitCubes.push_back(cubes[i]);
			}
		}
		//for the back side
		if (cubes[i]->position.z - 1.0f > startPos.z) {
			Vector3 intersectionPoint(0, 0, 0);
			if (IntersectPoint(dir, startPos, Vector3(0, 0, -1), cubes[i]->position + Vector3(0, 0, -1), intersectionPoint)) {
				if (intersectionPoint.y >= cubes[i]->position.y && intersectionPoint.y < cubes[i]->position.y + 1.0f &&
					intersectionPoint.x >= cubes[i]->position.x && intersectionPoint.x < cubes[i]->position.x + 1.0f)
					hitCubes.push_back(cubes[i]);
			}
		}
	}
	if (hitCubes.size() <= 0) return NULL;

	float closestDistance = (startPos - hitCubes[0]->position + offset).sqrdMagnitude();
	int closestIndex = 0;
	for (int i = 0; i < hitCubes.size(); i++)
	{
		float thisDistance = (startPos - hitCubes[i]->position + offset).sqrdMagnitude();
		if (closestDistance > thisDistance) {
			closestDistance = thisDistance;
			closestIndex = i;
		}
	}
	//return closest cube
	return hitCubes[closestIndex];
}
