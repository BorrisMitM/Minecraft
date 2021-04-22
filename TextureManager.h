#pragma once
#include <iostream>
#include "Bitmap.h"
#include "glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>
using namespace std;
class TextureManager
{
private:
public:
	GLuint		  grassTexture;
	GLuint		  dirtTexture;
	GLuint		  stoneTexture;
	GLuint		  cloudTexture;
	GLuint		  skyboxTexture;
	GLuint		  waterTexture;
	void LoadTextures();
	void BindTexture(GLuint textureID);
};

