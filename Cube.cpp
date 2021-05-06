#include "Cube.h"


const Cube::Vertex Cube::vertexTemplate[36] = {
	{0.0,0.0,0.0 ,0.0,0.0,1.0 ,0.0,0.33}, // front	
	{1.0,0.0,0.0 ,0.0,0.0,1.0 ,0.0,0.66},
	{0.0,1.0,0.0 ,0.0,0.0,1.0 ,0.25,0.33},
	{1.0,1.0,0.0 ,0.0,0.0,1.0 ,0.25,0.66},

	{1.0,0.0,0.0 ,1.0,0.0,0.0 ,0.25,1.0}, // right
	{1.0,0.0,-1.0 ,1.0,0.0,0.0 ,0.5,1.0},
	{1.0,1.0,0.0 ,1.0,0.0,0.0 ,0.25,0.66},
	{1.0,1.0,-1.0 ,1.0,0.0,0.0 ,0.5,0.66},

	{1.0,0.0,-1.0 ,0.0,0.0,-1.0 ,0.75,0.33}, // back
	{0.0,0.0,-1.0 ,0.0,0.0,-1.0 ,0.75,0.66},
	{1.0,1.0,-1.0 ,0.0,0.0,-1.0 ,0.5,0.33},
	{0.0,1.0,-1.0 ,0.0,0.0,-1.0 ,0.5,0.66},

	{0.0,0.0,-1.0 ,-1.0,0.0,0.0 ,0.25,0.0}, // left
	{0.0,0.0,0.0 ,-1.0,0.0,0.0 ,0.5,0.0},
	{0.0,1.0,-1.0 ,-1.0,0.0,0.0 ,0.25,0.33},
	{0.0,1.0,0.0 ,-1.0,0.0,0.0 ,0.5,0.33},

	{0.0,1.0,0.0 ,0.0,1.0,0.0 ,0.25,0.66}, // top
	{1.0,1.0,0.0 ,0.0,1.0,0.0 ,0.5,0.66},
	{0.0,1.0,-1.0 ,0.0,1.0,0.0 ,0.25,0.33},
	{1.0,1.0,-1.0 ,0.0,1.0,0.0 ,0.5,0.33},

	{0.0,0.0,-1.0 ,0.0,-1.0,0.0 ,0.75,0.66}, // bottom
	{1.0,0.0,-1.0 ,0.0,-1.0,0.0 ,0.75,0.33},
	{0.0,0.0,0.0 ,0.0,-1.0,0.0 ,1.0,0.66},
	{1.0,0.0,0.0 ,0.0,-1.0,0.0 ,1.0,0.33}
};

//see MinecraftAtlas.png for reference
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


void Cube::Render()
{
	//if (!visible) return;
	//glPushMatrix();
	//glTranslatef(position.x, position.y, position.z);
	//glBegin(GL_QUADS);
	//for (int side = 0; side < 6; side++) {
	//	//checks for each side if it is visible and then creates the corresponding quad
	//	if (visible[side]) {
	//		for (int i = side * 4; i < side * 4 + 4; i++) {
	//			glTexCoord2f(uv[i * 2], uv[i * 2 + 1]);
	//			glVertex3f(vert[index[i] * 3], vert[index[i] * 3 + 1], vert[index[i] * 3 + 2]);
	//		}
	//	}
	//}
	//glEnd();
	//glPopMatrix();
}


void Cube::AddToBufferArrays(std::vector<Cube::Vertex>& arrayOfDirtVertices, std::vector<unsigned int>& arrayOfDirtIndices)
{
	unsigned int offsetIndices[6] = { 0, 1, 2, 1, 3, 2 };

	for (int side = 0; side < 6; side++) {
		//checks for each side if it is visible and then creates the corresponding quad
		if (visible[side]) {
			for (int i = side * 4; i < side * 4 + 4; i++) {
				Cube::Vertex vertex = Cube::Vertex{
					vertexTemplate[i].x + position.x,
					vertexTemplate[i].y + position.y,
					vertexTemplate[i].z + position.z,

					vertexTemplate[i].nx,
					vertexTemplate[i].ny,
					vertexTemplate[i].nz,

					vertexTemplate[i].u * 0.5f + GetUVOffsetX(), // could modifiy these depending on block type
					vertexTemplate[i].v * 0.5f + GetUVOffsetY() // would need a block type enum which should be fine
				};
				arrayOfDirtVertices.push_back(vertex);
			}

			unsigned int startingIndexPosition = 4 * arrayOfDirtIndices.size() / 6;
			//cout << "startingIndexPosition " << startingIndexPosition << ": " << endl;
			for (int j = 0; j < 6; j++) {
				unsigned int indexValue = startingIndexPosition + offsetIndices[j];
		/*		cout << "indexValue " << indexValue << endl;

				cout << "arrayOfDirtVertices[indexValue].x " << arrayOfDirtVertices[indexValue].x << endl;
				cout << "arrayOfDirtVertices[indexValue].y " << arrayOfDirtVertices[indexValue].y << endl;
				cout << "arrayOfDirtVertices[indexValue].z " << arrayOfDirtVertices[indexValue].z << endl;*/

				arrayOfDirtIndices.push_back(indexValue);
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
