// --------------------------------------------------------------------------------------
//	OpenGL Triangle 
//	main.cpp
// --------------------------------------------------------------------------------------
#include "GLWindow.h"
#include "World.h"
#include "TerrainGenerator.h"
#include "CameraController.h"
#include <algorithm>
// --------------------------------------------------------------------------------

float timeSinceStart= 0, oldTimeSinceStart = 0;
float deltaTime;
float maxDeltaTime = 0.02f;

int main(void)
{
	//Markus stuff

	GLWindow		window(1280, 960, "Window");
	if (window.Init() == false) exit(EXIT_FAILURE);

	GLfloat aspect;

	glClearDepth(1.0); // clear Z Buffer
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	aspect = (GLfloat)640 / 480;
	gluPerspective(45.0, aspect, .2, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCullFace(GL_FRONT);
	//Create World
	World world;

	world.camera.Setup(&window);

	glViewport(0, 0, window.m_nWidth, window.m_nHeight);	
	while (window.IsRunning()) {

		timeSinceStart = glfwGetTime();
		deltaTime = timeSinceStart - oldTimeSinceStart;
		if (deltaTime > maxDeltaTime) deltaTime = maxDeltaTime;
		oldTimeSinceStart = timeSinceStart;
		//cout << 1.0f / deltaTime << endl;
		world.HandleInput(deltaTime);
		world.Update(deltaTime);
		world.RenderWorld();


		glFlush();
		//Sleep(30);
		window.Present();
	}

	
}

