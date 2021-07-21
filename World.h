#pragma once
#include "Cube.h"
#include <vector>
#include "TextureManager.h"
#include "Chunk.h"
#include "Cloud.h"
#include "CameraController.h" 
#include "GLWindow.h"
#include "Skybox.h"
#include "Vector3i.h"
#include "TerrainGenerator.h"
#include <algorithm>
//for older generation
//#define XSIZE 20
//#define ZSIZE 20
//#define HEIGHT 7


// Main class where our application lives.
// Holds the game's main Update method, as well as the calls to input handling and rendering.
// Instantiates and contains all necessary objects for the game.

class World
{
private:
	TextureManager textureManager; // Instance used to manage the textures of the game.
	vector<Chunk*> chunks;	// Collection of all visible chunks.
	Skybox* skybox;	// Reference to the game's skybox.

	TerrainGenerator terrainGenerator;	// Instance of the game's terrain generator.

	void CalculateNeighbors(); // Calculates and sets the neighbours for every chunk.

	void BindBuffer(unsigned int vbo, unsigned int ibo, unsigned int texture); // Binds a buffer to be rendered.

	Vector3 playerPosition;	// Position of the player in world coordinates.
public: 
	Chunk* currentChunk;	// Reference to the Chunk the player is currently in.
	CameraController camera; // Reference to the games camera.

	void HandleInput(float dt);	// Checks incoming inputs
	void Update(float dt, float timeSinceStart); // Propagates the passage of time to all game objects.
	void RenderWorld();	// Renders all world objects.
	void DeleteCube(Cube* cube); // Deletes a given cube from the world.
	World(float timeSinceStart);
	~World();
};
