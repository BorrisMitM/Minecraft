#include "Raycast.h"


Cube* Raycast::Cast(Vector3 startPos, Vector3 dir, int distance, World& world)
{
	vector<Cube*> cubes;
	Vector3i startPosIndex(startPos.x, startPos.y, startPos.z);
	startPosIndex.x %= 16;
	startPosIndex.z %= 16;
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
				cubes.push_back(chunkToGetTheCubeFrom->cubes[cubePosInChunk.x][cubePosInChunk.y][cubePosInChunk.z]);
			}
		}
	}
	//do the math
	//return closest cube
}
