#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <chrono>

#include <GL/glew.h>

#include <src/core/Window.h>


#include <src/scene/Scene.h>

// Window Settings
#define WINDOW_WIDTH	1024
#define WINDOW_HEIGHT	768
#define WINDOW_TITLE	"Conway's Game Of Life"

// Almighty Main
int main(int argc, char** argv)
{
	Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	Scene scene(window);

	while (window.shouldClose() == false)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene.Update();
		scene.Render();

		window.update();
	}

	return 0;
}