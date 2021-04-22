#include "Skybox.h"

void Skybox::Render(TextureManager& textureManager)
{
	glPushMatrix();
	textureManager.BindTexture(textureManager.skyboxTexture);
	glCullFace(GL_FRONT);
	glScalef(scale, scale, scale);
	glBegin(GL_QUADS);
	for (int i = 0; i < 24; i++) {
		glTexCoord2f(uv[i * 2], uv[i * 2 + 1]);
		glVertex3f(vert[index[i] * 3], vert[index[i] * 3 + 1], vert[index[i] * 3 + 2]);
	}
	glEnd();
	glCullFace(GL_BACK);
	glPopMatrix();
}
