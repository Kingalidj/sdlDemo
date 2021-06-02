#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "renderEngine.h"

renderEngine::renderEngine(int width, int height) {
	this->width = width;
	this->height = height;
}

bool renderEngine::init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("sdlDemo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gSurface = SDL_GetWindowSurface(gWindow);
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		}
	}

	return success;
}

void renderEngine::close() {
	gSurface = NULL;

	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;

	SDL_Quit();
}

bool renderEngine::start() {
	if (!init()) {
		return false;
	}

	SDL_Event event;

	while (!quit) {

		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) quit = true;
			else {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					quit = true;
					break;
				}
			}
		}

		SDL_SetRenderDrawColor(gRenderer, 200, 0, 100, 255);
		SDL_RenderClear(gRenderer);

		SDL_RenderPresent(gRenderer);
		SDL_Delay(0);

	}

	renderEngine::close();
	return true;
}