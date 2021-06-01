#pragma once

#include "GLWindow.h"
#include <math.h>
#include "Vector3.h"
#include <vector>

//contains all information a cube needs to be rendered
class Chunk;
class Cube
{
	struct Vertex;
	static const Vertex vertexTemplate[36];

protected:

	//determines if a certain side is visible
	bool visible[6] = { true,true,true,true,true,true }; // back, right, front, left, up, down
	bool transparency_;
	float GetUVOffsetX();
	float GetUVOffsetY();
public:
	Vector3 position;
	Chunk* chunk;

	//getter setter
	void SetVisibilty(int direction, bool isVisible);
	void SetTransparency(bool transparency);
	bool GetTransparency();
	int IsVisibleOnThisSide(int side);
	int GetVisibleSides();

	// deletes this cube and sets the visibility of the surrounding cubes
	void Delete(); 

	void AddToBufferArrays(std::vector<Cube::Vertex>& vertices, std::vector<unsigned int>& indices, float offset = 0);
	Cube(Vector3 position);
	Cube(float x, float y, float z);
	~Cube();

	struct Vertex {
		float x, y, z; // Vertex
		float nx, ny, nz; // Normal
		float u, v; // UV
	};

	enum BlockType {
		Grass, 
		Dirt,
		Stone, 
		Water
	};

	BlockType type;
};

