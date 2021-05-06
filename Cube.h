#pragma once

#include "GLWindow.h"
#include <math.h>
#include "Vector3.h"
#include <vector>

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
	void SetVisibilty(int direction, bool isVisible);
	void SetTransparency(bool transparency);
	bool GetTransparency();
	Vector3 position;
	void Render();

	void AddToBufferArrays(std::vector<Cube::Vertex>& arrayOfDirtVertices, std::vector<unsigned int>& arrayOfDirtIndices);
	int GetVisibleSides();
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

