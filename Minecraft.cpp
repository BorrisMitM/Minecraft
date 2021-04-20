// --------------------------------------------------------------------------------------
//	OpenGL Triangle 
//	main.cpp
// --------------------------------------------------------------------------------------
#include "GLWindow.h"
#include "World.h"
#include "TerrainGenerator.h"
#include "CameraController.h"
// --------------------------------------------------------------------------------

int main(void)
{
	//Markus stuff

	GLWindow		window(1280, 960, "Window");
	if (window.Init() == false) exit(EXIT_FAILURE);

	GLfloat aspect;

	glClearDepth(1.0); // clear Z Buffer
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glMatrixMode(GL_PROJECTION);
	aspect = (GLfloat)640 / 480;
	gluPerspective(45.0, aspect, 3.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//Move Camera
	//glTranslatef(0.0f, 0.0f, -200.0f);
	//glRotatef(-45, 0, 1, 0);
	//glRotatef(45, 1, 0, 0);

	//Create World
	World world;
	//Generate terrain, comment this out if we use chunks
	//TerrainGenerator terrainGenerator;
	//terrainGenerator.Generate(world);
	//Update and Render World

	glViewport(0, 0, window.m_nWidth, window.m_nHeight);	
	while (window.IsRunning()) {

		world.HandleInput();
		world.Update();
		world.RenderWorld();


		glFlush();
		Sleep(30);
		window.Present();
	}
}
