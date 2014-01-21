#include "common.h"

#include "framework.h"

#include <GL/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>

Framework::Framework()
	: _window(NULL),
	_running(false),
	_initialized(false)
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		debug::Printf("[Error] SDL_Init failed: %s\n", SDL_GetError());
		return;
	}

	int win_width = 800;
	int win_height = 600;
	_window = SDL_CreateWindow("Framework", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if(!_window)
	{
		debug::Printf("[Error] SDL_CreateWindow failed: %s\n", SDL_GetError());
		return;
	}

	// Create the opengl context for our main window.
	SDL_GL_CreateContext(_window);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set the clear color to black

	// Initialize glew, which handles opengl extensions
	GLenum err = glewInit(); 
	if(err != GLEW_OK)
	{
		debug::Printf("[Error] glewInit failed: %s\n", glewGetErrorString(err));
		return;
	}
	fprintf(stdout, "GLEW: Using version %s\n", glewGetString(GLEW_VERSION));

	_initialized = true;
}
Framework::~Framework()
{
	_initialized = false;

	if(_window)
		SDL_DestroyWindow(_window);

	SDL_Quit();
}

void Framework::Run()
{
	if(!_initialized)
	{
		debug::Printf("[Error] Framework::Run: Framework is not initialized properly.\n");
		return;
	}

	_running = true;

	SDL_Event evt;
	while(_running)
	{
		while(SDL_PollEvent(&evt))
		{
			if(evt.type == SDL_QUIT)
				_running = false;
		}

		// Clear the frame buffer
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap buffers for our main window.
		SDL_GL_SwapWindow(_window);
	}
}