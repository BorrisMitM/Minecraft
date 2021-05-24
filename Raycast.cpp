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
	Vector3 offset = Vector3(.5f, .5f, .5f);
	vector<Cube*> cubes;
	Vector3i startPosIndex(startPos.x, startPos.y, startPos.z);
	startPosIndex.x = startPosIndex.x - world.currentChunk->gridPosX * 16;
	startPosIndex.z = startPosIndex.z - world.currentChunk->gridPosZ * 16;

	//Get all the cubes in distance
	for (int x = startPosIndex.x - distance; x <= startPosIndex.x + distance; x++) {
		for (int y = startPosIndex.y - distance; y <= startPosIndex.y + distance; y++) {
			for (int z = startPosIndex.z - distance; z <= startPosIndex.z + distance; z++) {
				
				Cube* cubeToAdd = GetRelativeCube(x, y, z, world.currentChunk);
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
					intersectionPoint.z >= cubes[i]->position.z && intersectionPoint.z < cubes[i]->position.z + 1.0f)
					hitCubes.push_back(cubes[i]);
  			}
		}
		//for the bottom side
		if (cubes[i]->position.y > startPos.y) {
			Vector3 intersectionPoint(0, 0, 0);
			if (IntersectPoint(dir, startPos, Vector3(0, -1, 0), cubes[i]->position, intersectionPoint)) {
				if (intersectionPoint.x >= cubes[i]->position.x && intersectionPoint.x < cubes[i]->position.x + 1.0f &&
					intersectionPoint.z >= cubes[i]->position.z && intersectionPoint.z < cubes[i]->position.z + 1.0f)
					hitCubes.push_back(cubes[i]);
			}
		}
		//for the left side
		if (cubes[i]->position.x > startPos.x) {
			Vector3 intersectionPoint(0, 0, 0);
			if (IntersectPoint(dir, startPos, Vector3(-1, 0, 0), cubes[i]->position, intersectionPoint)) {
				if (intersectionPoint.y >= cubes[i]->position.y && intersectionPoint.y < cubes[i]->position.y + 1.0f &&
					intersectionPoint.z >= cubes[i]->position.z && intersectionPoint.z < cubes[i]->position.z + 1.0f)
					hitCubes.push_back(cubes[i]);
			}
		}
		//for the right side
		if (cubes[i]->position.x + 1.0f< startPos.x) {
			Vector3 intersectionPoint(0, 0, 0);
			if (IntersectPoint(dir, startPos, Vector3(1, 0, 0), cubes[i]->position + Vector3(1, 0, 0), intersectionPoint)) {
				if (intersectionPoint.y >= cubes[i]->position.y && intersectionPoint.y < cubes[i]->position.y + 1.0f &&
					intersectionPoint.z >= cubes[i]->position.z && intersectionPoint.z < cubes[i]->position.z + 1.0f)
					hitCubes.push_back(cubes[i]);
			}
		}
		//for the front side
		if (cubes[i]->position.z < startPos.z) {
			Vector3 intersectionPoint(0, 0, 0);
			if (IntersectPoint(dir, startPos, Vector3(0, 0, 1), cubes[i]->position + Vector3(0, 0, 1), intersectionPoint)) {
				if (intersectionPoint.y >= cubes[i]->position.y && intersectionPoint.y < cubes[i]->position.y + 1.0f &&
					intersectionPoint.x >= cubes[i]->position.x && intersectionPoint.x < cubes[i]->position.x + 1.0f)
					hitCubes.push_back(cubes[i]);
			}
		}
		//for the back side
		if (cubes[i]->position.z - 1.0f > startPos.z) {
			Vector3 intersectionPoint(0, 0, 0);
			if (IntersectPoint(dir, startPos, Vector3(0, 0, -1), cubes[i]->position, intersectionPoint)) {
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

//radius < 1, upExtends < 1, downExtends < 2
bool Raycast::CylinderCast(Vector3 startPos, float upExtend, float downExtend, float radius, World& world, vector<CollisionInfo>& collisionInfo)
{
	float radiusSqrd = radius * radius;
	Vector3i startPosIndex(floor(startPos.x), floor(startPos.y), floor(startPos.z));
	startPosIndex.x = startPosIndex.x - world.currentChunk->gridPosX * 16;
	startPosIndex.z = startPosIndex.z - world.currentChunk->gridPosZ * 16;
	//calculate max ybottom and ytop we have to check
	int ybottom = startPos.y - downExtend;
	int ytop = startPos.y + upExtend;
	//horizontal collision
	for (int y = ybottom; y <= ytop; y++) {
		for (int x = startPosIndex.x - 1; x <= startPosIndex.x + 1; x++) {
			for (int z = startPosIndex.z - 1; z <= startPosIndex.z + 1; z++) {
				if (z == startPosIndex.z && x == startPosIndex.x) continue;
				Cube* cube = GetRelativeCube(x, y, z, world.currentChunk);
				if (cube != NULL && cube->type != Cube::BlockType::Water) {
					int xOffset = x == startPosIndex.x - 1 ?  1 : 0;
					int zOffset = z == startPosIndex.z - 1 ?  1 : 0;
					Vector3 cubeVertexPosition = cube->position;
					cubeVertexPosition.x += xOffset;
					cubeVertexPosition.z += zOffset;
					//zdirection
					if (z == startPosIndex.z) {
						//zdirection
						float distance = abs(startPos.x - cubeVertexPosition.x);
						if (distance < radius) {
							CollisionInfo colInfo;
							colInfo.cube = cube;
							colInfo.normal = Vector3(startPosIndex.x - x, 0, 0);
							colInfo.point = Vector3(cubeVertexPosition.x, cubeVertexPosition.y, startPos.z);
							collisionInfo.push_back(colInfo);
						}
					} else if (x == startPosIndex.x) {
						//xdirection
						float distance = abs(startPos.z - cubeVertexPosition.z);
						if (distance < radius) {
							CollisionInfo colInfo;
							colInfo.cube = cube;
							colInfo.normal = Vector3(0, 0, startPosIndex.z - z);
							colInfo.point = Vector3(startPos.x, cubeVertexPosition.y, cubeVertexPosition.z);
							collisionInfo.push_back(colInfo);
						}
					}
					else {
						//diagonal
						float zDistance = startPos.z - cubeVertexPosition.z;
						float xDistance = startPos.x - cubeVertexPosition.x;
						float distanceSqrd = xDistance * xDistance + zDistance * zDistance;
						if (distanceSqrd < radiusSqrd) {
							CollisionInfo colInfo;
							colInfo.cube = cube;
							colInfo.normal = startPos - cubeVertexPosition;
							colInfo.normal.y = 0;

							if (!cube->IsVisibleOnThisSide(colInfo.normal.x > 0 ? 1 : 3)) {
								colInfo.normal.x = 0; // no colisions on non visible sides
							}
							if (!cube->IsVisibleOnThisSide(colInfo.normal.z > 0 ? 0 : 2)) {
								colInfo.normal.z = 0; // no colisions on non visible sides
							}
							colInfo.normal.Normalize(); 
							if (colInfo.normal.sqrdMagnitude() < 0.01f) continue;
							colInfo.point = cubeVertexPosition;

							collisionInfo.push_back(colInfo);
						}
					}
				}
			}
		}
	}
	//bottom collision
	for (int x = startPosIndex.x - 1; x <= startPosIndex.x + 1; x++) {
		for (int z = startPosIndex.z - 1; z <= startPosIndex.z + 1; z++) {
			Cube* cube = GetRelativeCube(x, ybottom, z, world.currentChunk);
			if (cube != NULL && cube->type != Cube::BlockType::Water) {
				int xOffset = x == startPosIndex.x - 1 ? 1 : 0;
				int zOffset = z == startPosIndex.z - 1 ? 1 : 0;
				Vector3 cubeVertexPosition = cube->position;
				cubeVertexPosition.x += xOffset;
				cubeVertexPosition.z += zOffset; 
				cubeVertexPosition.y += 1;
 				bool colliding = false;
				//zdirection
				if (z == startPosIndex.z && x == startPosIndex.x) {
					colliding = true;
				}
				else if (z == startPosIndex.z) {
					//zdirection
					float distance = abs(startPos.x - cubeVertexPosition.x);
					if (distance < radius) {
						colliding = true;
					}
				}
				else if (x == startPosIndex.x) {
					//xdirection
					float distance = abs(startPos.z - cubeVertexPosition.z);
					if (distance < radius) {
						colliding = true;
					}
				}
				else {
					//diagonal
					float zDistance = startPos.z - cubeVertexPosition.z;
					float xDistance = startPos.x - cubeVertexPosition.x;
					float distanceSqrd = xDistance * xDistance + zDistance * zDistance;
					if (distanceSqrd < radiusSqrd) {
						colliding = true;
					}
				}
				if (colliding) {
					CollisionInfo colInfo;
					colInfo.cube = cube;
					colInfo.normal = Vector3(0, 1, 0);
					colInfo.point = Vector3(startPos.x, cubeVertexPosition.y, startPos.z);
					collisionInfo.push_back(colInfo);
				}
			}
		}
	}
	//top collision
	for (int x = startPosIndex.x - 1; x <= startPosIndex.x + 1; x++) {
		for (int z = startPosIndex.z - 1; z <= startPosIndex.z + 1; z++) {
			Cube* cube = GetRelativeCube(x, ytop, z, world.currentChunk);
			if (cube != NULL && cube->type != Cube::BlockType::Water) {
				int xOffset = x == startPosIndex.x - 1 ? 1 : 0;
				int zOffset = z == startPosIndex.z + 1 ? -1 : 0;
				Vector3 cubeVertexPosition = cube->position;
				cubeVertexPosition.x += xOffset;
				cubeVertexPosition.z += zOffset;
				bool colliding = false;
				//zdirection
				if (z == startPosIndex.z && x == startPosIndex.x) {
					colliding = true;
				}
				else if (z == startPosIndex.z) {
					//zdirection
					float distance = abs(startPos.x - cubeVertexPosition.x);
					if (distance < radius) {
						colliding = true;
					}
				}
				else if (x == startPosIndex.x) {
					//xdirection
					float distance = abs(startPos.z - cubeVertexPosition.z);
					if (distance < radius) {
						colliding = true;
					}
				}
				else {
					//diagonal
					float zDistance = startPos.z - cubeVertexPosition.z;
					float xDistance = startPos.x - cubeVertexPosition.x;
					float distanceSqrd = xDistance * xDistance + zDistance * zDistance;
					if (distanceSqrd < radiusSqrd) {
						colliding = true;
					}
				}
				if (colliding) {
					CollisionInfo colInfo;
					colInfo.cube = cube;
					colInfo.normal = Vector3(0, -1, 0);
					colInfo.point = Vector3(startPos.x, cubeVertexPosition.y, startPos.z);
					collisionInfo.push_back(colInfo);
				}
			}
		}
	}
	/*for (int i = 0; i < collisionInfo.size(); i++)
	{
		cout << sqrt((startPos - collisionInfo[i].point).sqrdMagnitude()) << endl;
	}*/
	return collisionInfo.size() > 0;
}

Cube* Raycast::GetRelativeCube(int x, int y, int z, Chunk* chunk)
{
	Chunk* chunkToGetTheCubeFrom;
	Vector3i cubePosInChunk(x, y, z);
	//check for chunk to get the cube from
	if (x < 0) {
		chunkToGetTheCubeFrom = chunk->neighbors[3];
		cubePosInChunk.x += 16;
	}
	else if (x >= 16) {
		chunkToGetTheCubeFrom = chunk->neighbors[1];
		cubePosInChunk.x -= 16;
	}
	else chunkToGetTheCubeFrom = chunk;

	if (z < 0) {
		chunkToGetTheCubeFrom = chunkToGetTheCubeFrom->neighbors[2];
		cubePosInChunk.z += 16;
	}
	else if (z >= 16) {
		chunkToGetTheCubeFrom = chunkToGetTheCubeFrom->neighbors[0];
		cubePosInChunk.z -= 16;
	}
	return chunkToGetTheCubeFrom->cubes[cubePosInChunk.x][cubePosInChunk.y][cubePosInChunk.z];
}

