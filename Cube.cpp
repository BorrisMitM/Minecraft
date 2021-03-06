#include "Cube.h"
#include "Chunk.h"
#include "Vector3i.h"
//vertices of a cube 
const Cube::Vertex Cube::vertexTemplate[36] = {
	// vertices		normals		uvs
	{0.0,0.0,1.0 ,0.0,0.0,1.0 ,0.0,0.33}, // front	
	{1.0,0.0,1.0 ,0.0,0.0,1.0 ,0.0,0.66},
	{0.0,1.0,1.0 ,0.0,0.0,1.0 ,0.25,0.33},
	{1.0,1.0,1.0 ,0.0,0.0,1.0 ,0.25,0.66},

	{1.0,0.0,1.0 ,1.0,0.0,0.0 ,0.25,1.0}, // right
	{1.0,0.0,0.0 ,1.0,0.0,0.0 ,0.5,1.0},
	{1.0,1.0,1.0 ,1.0,0.0,0.0 ,0.25,0.66},
	{1.0,1.0,0.0 ,1.0,0.0,0.0 ,0.5,0.66},

	{1.0,0.0,0.0 ,0.0,0.0,-1.0 ,0.75,0.33}, // back
	{0.0,0.0,0.0 ,0.0,0.0,-1.0 ,0.75,0.66},
	{1.0,1.0,0.0 ,0.0,0.0,-1.0 ,0.5,0.33},
	{0.0,1.0,0.0 ,0.0,0.0,-1.0 ,0.5,0.66},

	{0.0,0.0,0.0 ,-1.0,0.0,0.0 ,0.25,0.0}, // left
	{0.0,0.0,1.0 ,-1.0,0.0,0.0 ,0.5,0.0},
	{0.0,1.0,0.0 ,-1.0,0.0,0.0 ,0.25,0.33},
	{0.0,1.0,1.0 ,-1.0,0.0,0.0 ,0.5,0.33},

	{0.0,1.0,1.0 ,0.0,1.0,0.0 ,0.25,0.66}, // top
	{1.0,1.0,1.0 ,0.0,1.0,0.0 ,0.5,0.66},
	{0.0,1.0,0.0 ,0.0,1.0,0.0 ,0.25,0.33},
	{1.0,1.0,0.0 ,0.0,1.0,0.0 ,0.5,0.33},

	{0.0,0.0,0.0 ,0.0,-1.0,0.0 ,0.75,0.66}, // bottom
	{1.0,0.0,0.0 ,0.0,-1.0,0.0 ,0.75,0.33},
	{0.0,0.0,1.0 ,0.0,-1.0,0.0 ,1.0,0.66},
	{1.0,0.0,1.0 ,0.0,-1.0,0.0 ,1.0,0.33}
};

//see MinecraftAtlas.png for reference
//Gets the correct offset of the uv coordinates for the texture atlas
float Cube::GetUVOffsetX()
{
	float offset = 0;
	if (type == BlockType::Dirt || type == BlockType::Water) offset = 0.5f;
	return offset;
}

float Cube::GetUVOffsetY()
{
	float offset = 0;
	if (type == BlockType::Dirt || type == BlockType::Grass) offset = 0.5f;
	return offset;
}

void Cube::SetVisibilty(int direction, bool isVisible)
{
	if (direction >= 6 || direction < 0) {
		cout << "Wrong direction given to SetVisibility. " << endl;
		return;
	}
	visible[direction] = isVisible;
}

void Cube::SetTransparency(bool transparency)
{
	transparency_ = transparency;
}

bool Cube::GetTransparency()
{
	return transparency_;
}

int Cube::IsVisibleOnThisSide(int side)
{
	return visible[side];
}

void Cube::Delete()
{
	Vector3i cubeIndex(0, position.y, 0);

	//calculate local x and z coordinates
	cubeIndex.x = position.x - chunk->gridPosX * 16;
	cubeIndex.z = position.z - chunk->gridPosZ * 16;

	//set the position of the cube in the chunk to NULL
	chunk->cubes[cubeIndex.x][cubeIndex.y][cubeIndex.z] = NULL;


	vector<int> modifiedNeighbors;

	//recalculate neighbors visibility, taking into account if the neighbor is in the neighbor chunk
	if (cubeIndex.x > 0) {
		chunk->SetVisibility(cubeIndex.x - 1, cubeIndex.y, cubeIndex.z);
	}
	else if (chunk->neighbors[3] != NULL) {
		chunk->neighbors[3]->SetVisibility(15, cubeIndex.y, cubeIndex.z);
		modifiedNeighbors.push_back(3);
	}

	if (cubeIndex.x < 15) {
		chunk->SetVisibility(cubeIndex.x + 1, cubeIndex.y, cubeIndex.z);
	}
	else if (chunk->neighbors[1] != NULL) {
		chunk->neighbors[1]->SetVisibility(0, cubeIndex.y, cubeIndex.z);
		modifiedNeighbors.push_back(1);
	}

	if (cubeIndex.y > 0) {
		chunk->SetVisibility(cubeIndex.x, cubeIndex.y - 1, cubeIndex.z);
	}

	if (cubeIndex.y < 255) {
		chunk->SetVisibility(cubeIndex.x, cubeIndex.y + 1, cubeIndex.z);
	}

	if (cubeIndex.z > 0) {
		chunk->SetVisibility(cubeIndex.x, cubeIndex.y, cubeIndex.z - 1);
	}
	else if (chunk->neighbors[2] != NULL) {
		chunk->neighbors[2]->SetVisibility(cubeIndex.x, cubeIndex.y, 15);
		modifiedNeighbors.push_back(2);
	}

	if (cubeIndex.z < 15) {
		chunk->SetVisibility(cubeIndex.x, cubeIndex.y, cubeIndex.z + 1);
	}
	else if (chunk->neighbors[0] != NULL) {
		chunk->neighbors[0]->SetVisibility(cubeIndex.x, cubeIndex.y, 0);
		modifiedNeighbors.push_back(0);
	}

	
	//update buffers, for this chunk and modified neighborchunks
	chunk->CreateAndFillBuffer();
	for (int i = 0; i < modifiedNeighbors.size(); i++) {
		chunk->neighbors[modifiedNeighbors[i]]->CreateAndFillBuffer();
	}
	delete(this);
}


void Cube::AddToBufferArrays(std::vector<Cube::Vertex>& vertices, std::vector<unsigned int>& indecies, float offset)
{
	//index order
	unsigned int offsetIndices[6] = { 0, 1, 2, 1, 3, 2 };

	for (int side = 0; side < 6; side++) {
		//checks for each side if it is visible and then creates the corresponding quad
		if (visible[side]) {
			for (int i = side * 4; i < side * 4 + 4; i++) {
				Cube::Vertex vertex = Cube::Vertex{
					vertexTemplate[i].x + position.x + offset,
					vertexTemplate[i].y + position.y,
					vertexTemplate[i].z + position.z,

					vertexTemplate[i].nx,
					vertexTemplate[i].ny,
					vertexTemplate[i].nz,

					vertexTemplate[i].u * 0.5f + GetUVOffsetX(), // could modifiy these depending on block type
					vertexTemplate[i].v * 0.5f + GetUVOffsetY() // would need a block type enum which should be fine
				};
				vertices.push_back(vertex);
			}

			//calculate starting index in indice array
			unsigned int startingIndexPosition = 4 * indecies.size() / 6;

			//add inidicies to the array
			for (int j = 0; j < 6; j++) {
				unsigned int indexValue = startingIndexPosition + offsetIndices[j];
				indecies.push_back(indexValue);
			}
		}
	}
}

int Cube::GetVisibleSides()
{
	int visibleSides = 0;
	for (int i = 0; i < 6; i++) if (visible[i]) visibleSides++;
	return visibleSides;
}

Cube::Cube(Vector3 position) : position(position)
{
	transparency_ = false;
}

Cube::Cube(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;

	transparency_ = false;
}

Cube::~Cube()
{

}
