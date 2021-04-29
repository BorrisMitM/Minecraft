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

	//float vert[24] = { -0.5,-0.5,0.5, 0.5,-0.5,0.5f, 0.5,0.5,0.5, -0.5,0.5,0.5, -0.5,-0.5,-0.5, 0.5,-0.5,-0.5f, 0.5,0.5,-0.5, -0.5,0.5,-0.5 };
	//float uv[48] = { 0.25,0.0, 0.5,0.0, 0.5,0.33, 0.25,0.33, 0.75,0.33, 0.75,0.66, 0.5,0.66, 0.5,0.33, 0.5,1.0, 0.25,1.0, 0.25,0.66, 0.5,0.66, 0.0,0.66, 0.0,0.33, 0.25,0.33, 0.25,0.66, 0.25,0.33, 0.5,0.33, 0.5,0.66, 0.25,0.66, 1.0,0.33, 1.0,0.66, 0.75,0.66, 0.75,0.33 };
	//int	  index[24] = { 0,1,2,3, 1,5,6,2, 5,4,7,6, 4,0,3,7, 3,2,6,7, 1,0,4,5 };
	//determines if a certain side is visible
	bool visible[6] = { true,true,true,true,true,true }; // back, right, front, left, up, down
public:
	void SetVisibilty(int direction, bool isVisible);
	Vector3 position;
	void Render();

	void AddToBufferArrays(std::vector<Cube::Vertex>& arrayOfDirtVertices, std::vector<unsigned int>& arrayOfDirtIndices);

	Cube(Vector3 position);
	Cube(float x, float y, float z);
	~Cube();

	struct Vertex {
		float x, y, z; // Vertex
		float nx, ny, nz; // Normal
		float u, v; // UV
	};
};

