#pragma once
#include <iostream>
#include "Bitmap.h"
#include "glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>
using namespace std;

// Helper class to facilitate texture management.
// Responsible for loading all textures, as well as binding them when necessary

class TextureManager
{
private:
public:
	GLuint		cloudTexture;
	GLuint		skyboxTexture;
	GLuint		chunkAtlas; // Atlas of cube textures

	void LoadTextures(); // Load all texture into memory
	void BindTexture(GLuint textureID); // Bind a given texture
};

