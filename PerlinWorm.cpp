#include "PerlinWorm.h"
#include "Vector3i.h"
PerlinWorm::PerlinWorm(Vector3 position, float length)
{
	startPosition = position;
	startPosition.y = 0;
	//create noise object
	FastNoiseLite wormYawNoise;
	wormYawNoise.SetSeed(rand());
	wormYawNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	FastNoiseLite wormPitchNoise;
	wormPitchNoise.SetSeed(rand());
	wormPitchNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	//FastNoiseLite wormThicknessNoise;
	//wormThicknessNoise.SetSeed(420);
	//wormThicknessNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	Vector3 currentPosition = startPosition;
	currentPosition.y = rand() % MIN_HEIGHT;
	Vector3 currentDirection(0, 1, 0);

	float distance = 0;
	float radius = 3;
	while (distance < length) {
		float pitch = wormPitchNoise.GetNoise(distance, 0.0f) * 90;
		float yaw = wormYawNoise.GetNoise(distance, 0.0f) * 180;

		float cosPitch = cosf(pitch * 3.1415 / 180);
		float cosYaw = cosf(yaw * 3.1415 / 180);

		float sinPitch = sinf(pitch * 3.1415 / 180);
		float sinYaw = sinf(yaw * 3.1415 / 180);

		currentDirection.x = sinYaw * cosPitch;
		currentDirection.y = sinPitch;
		currentDirection.z = cosPitch * -cosYaw;

		currentPosition += currentDirection;

		distance += 1.0f;
		//currentPosition.Print();


		if (currentPosition.x < -(WORM_DISTANCE) * 16 
			|| currentPosition.z < -(WORM_DISTANCE) * 16 
			|| currentPosition.x >= (WORM_DISTANCE + 1) * 16 
			|| currentPosition.z >= (WORM_DISTANCE + 1) * 16
			|| currentPosition.y >= MIN_HEIGHT
			|| currentPosition.y < 0) break;
		Vector3i positionInGrid(currentPosition.x + (WORM_DISTANCE) * 16, currentPosition.y, currentPosition.z + (WORM_DISTANCE) * 16);

		for (int x = -radius; x <= radius; x++) {
			for (int y = -radius; y <= radius; y++) {
				for (int z = -radius; z <= radius; z++) {
					//check if surrounding will get out of the array 
					if (positionInGrid.x + x < 0 || positionInGrid.x + x >= (WORM_DISTANCE * 2 + 1) * 16 ||
						positionInGrid.z + z < 0 || positionInGrid.z + z >= (WORM_DISTANCE * 2 + 1) * 16 ||
						positionInGrid.y + y < 0 || positionInGrid.y + y >= MIN_HEIGHT) continue;

					wormData[positionInGrid.x + x][positionInGrid.y + y][positionInGrid.z + z] = true;

				}
			}
		}
	}
}

bool PerlinWorm::IsCaveAt(Vector3 worldPos)
{
	if (worldPos.y >= MIN_HEIGHT) return false;
	Vector3 positionInWormGridFloat = worldPos - startPosition; // get the relativ distance from the worm to the world position to check
	Vector3i positionInWormGrid(positionInWormGridFloat.x, positionInWormGridFloat.y, positionInWormGridFloat.z);
	//adjust the position to fit into the array ( no negative indicies for arrays)
	positionInWormGrid.x += WORM_DISTANCE * 16;
	positionInWormGrid.z += WORM_DISTANCE * 16;
	
	//check if the position is inside of the worm array
	if (positionInWormGrid.x < (WORM_DISTANCE * 2 + 1) * 16 
		&& positionInWormGrid.z < (WORM_DISTANCE * 2 + 1) * 16 
		&& positionInWormGrid.x >= 0 
		&& positionInWormGrid.z >= 0) 
	{
		if(wormData[positionInWormGrid.x][positionInWormGrid.y][positionInWormGrid.z])
		return wormData[positionInWormGrid.x][positionInWormGrid.y][positionInWormGrid.z];
	}
	else {
		return false;
	}
	return false;
}
