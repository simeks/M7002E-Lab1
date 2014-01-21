#include "common.h"

#include "framework.h"

#include <SDL.h>

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
	_window = SDL_CreateWindow("Framework", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN);
	if(!_window)
	{
		debug::Printf("[Error] SDL_CreateWindow failed: %s\n", SDL_GetError());
		return;
	}

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
	}
}