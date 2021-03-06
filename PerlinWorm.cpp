#include "PerlinWorm.h"
#include "Vector3i.h"

PerlinWorm::PerlinWorm(Vector3 position, float length, int wormAmount)
{
	//setup noise objects and variables for the perlin worm algorythm
	startPosition = position;
	startPosition.y = 0;

	FastNoiseLite wormRotNoise;
	wormRotNoise.SetSeed(rand());
	wormRotNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	FastNoiseLite radiusNoise;
	radiusNoise.SetSeed(rand());
	radiusNoise.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_Value);
	int radius = round((radiusNoise.GetNoise(0.0f,0.0f)*0.5+0.5f)*3+1);

	int yPosition = rand() % (MIN_HEIGHT - 20) + 20;
	Vector3 currentDirection(0, 1, 0);
	//create wormAmount worms from (0,yPosition,0)
	for (int i = 0; i < wormAmount; i++) {
		Vector3 currentPosition(0,yPosition,0);

		float distance = 0;

		while (distance < length) {
			//vary radius based on distance traveled
			radius = round((radiusNoise.GetNoise(distance + length * i, 0.0f) * 0.5 + 0.5f) * 3 + 1);

			//get pitch and yaw from the x and y axis of the noise
			float pitch = wormRotNoise.GetNoise(distance + length * i, 0.0f) * 90;
			float yaw = wormRotNoise.GetNoise(0.0f, distance + length * i) * 180;

			//calculate new direction
			float cosPitch = cosf(pitch * 3.1415 / 180);
			float cosYaw = cosf(yaw * 3.1415 / 180);

			float sinPitch = sinf(pitch * 3.1415 / 180);
			float sinYaw = sinf(yaw * 3.1415 / 180);

			currentDirection.x = sinYaw * cosPitch;
			currentDirection.y = sinPitch;
			currentDirection.z = cosPitch * -cosYaw;

			//move in direction
			currentPosition += currentDirection;

			distance += 1.0f;
			//currentPosition.Print();

			//try again if currentPosition is outside of the WORM_DISTANCE
			if (currentPosition.x < -(WORM_DISTANCE) * 16
				|| currentPosition.z < -(WORM_DISTANCE) * 16
				|| currentPosition.x >= (WORM_DISTANCE + 1) * 16
				|| currentPosition.z >= (WORM_DISTANCE + 1) * 16
				|| currentPosition.y >= MIN_HEIGHT
				|| currentPosition.y <= radius) continue;
			//calculate position in the grid
			Vector3i positionInGrid(currentPosition.x + (WORM_DISTANCE) * 16, currentPosition.y, currentPosition.z + (WORM_DISTANCE) * 16);

			//carve out radius from currentPosition
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
	//cout << "Created new Worm at ";
	//position.Print();
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
