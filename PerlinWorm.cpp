#include "PerlinWorm.h"

PerlinWorm::PerlinWorm()
{
	startPosition = new Vector3(8,15,8);
	//create noise object
	FastNoiseLite wormYawNoise;
	wormYawNoise.SetSeed(420);
	wormYawNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	FastNoiseLite wormPitchNoise;
	wormPitchNoise.SetSeed(69);
	wormPitchNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	//FastNoiseLite wormThicknessNoise;
	//wormThicknessNoise.SetSeed(420);
	//wormThicknessNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	Vector3 currentPosition = *startPosition;
	Vector3 currentDirection(0, 1, 0);

	float distance = 0;
	float radius = 3;
	while (distance < 50) {
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


		if (currentPosition.x < -(WORM_DISTANCE) * 16 || currentPosition.z < -(WORM_DISTANCE) * 16 
			|| currentPosition.x >= (WORM_DISTANCE + 1) * 16 || currentPosition.z >= (WORM_DISTANCE + 1) * 16
			|| currentPosition.y >= MIN_HEIGHT) break;
		Vector3 positionInGrid(currentPosition.x + (WORM_DISTANCE) * 16, currentPosition.y, currentPosition.z + (WORM_DISTANCE) * 16);

		for (int x = -radius; x <= radius; x++) {
			for (int y = -radius; y <= radius; y++) {
				for (int z = -radius; z <= radius; z++) {
					//check if surrounding will get out of the array 
					if (positionInGrid.x + x < 0 || positionInGrid.x >= (WORM_DISTANCE * 2 + 1) * 16 ||
						positionInGrid.z + z < 0 || positionInGrid.z >= (WORM_DISTANCE * 2 + 1) * 16 ||
						positionInGrid.y + y < 0 || positionInGrid.y >= MIN_HEIGHT) continue;

					wormData[(int)positionInGrid.x + x][(int)positionInGrid.y + y][(int)positionInGrid.z + z] = true;

				}
			}
		}
	}
}

bool PerlinWorm::IsCaveAt(Vector3 worldPos)
{
	//if (worldPos.y >= MIN_HEIGHT) return false;
	//Vector3 positionInWormGrid = worldPos - *startPosition; // get the relativ distance from the worm to the world position to check
	//
	////adjust the position to fit into the array ( no negative indicies for arrays)
	//positionInWormGrid.x += WORM_DISTANCE * 16;
	//positionInWormGrid.z += WORM_DISTANCE * 16;
	//
	////check if the position is inside of the worm array
	//if (positionInWormGrid.x < (WORM_DISTANCE * 2 + 1) * 16 || positionInWormGrid.z < (WORM_DISTANCE * 2 + 1) * 16 || positionInWormGrid.x >= 0 || positionInWormGrid.z >= 0) {
	//	if(wormData[(int)positionInWormGrid.x][(int)positionInWormGrid.y][(int)positionInWormGrid.z])
	//	return wormData[(int)positionInWormGrid.x][(int)positionInWormGrid.y][(int)positionInWormGrid.z];
	//}
	//else {
	//	return false;
	//}
	return false;
}
