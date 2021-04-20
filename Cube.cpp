#include "Cube.h"

void Cube::SetVisibilty(int direction, bool isVisible)
{
	if (direction >= 6 || direction < 0) {
		cout << "Wrong direction given to SetVisibility. " << endl;
		return;
	}
	visible[direction] = isVisible;
}

void Cube::Render()
{
	if (!visible) return;
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glBegin(GL_QUADS);
	for (int side = 0; side < 6; side++) {
		//checks for each side if it is visible and then creates the corresponding quad
		if (visible[side]) {
			for (int i = side * 4; i < side * 4 + 4; i++) {
				glTexCoord2f(uv[i * 2], uv[i * 2 + 1]);
				glVertex3f(vert[index[i] * 3], vert[index[i] * 3 + 1], vert[index[i] * 3 + 2]);
			}
		}
	}
	glEnd();
	glPopMatrix();
}

Cube::Cube(Vector3 position): position(position)
{
}

Cube::Cube(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

Cube::~Cube()
{

}
