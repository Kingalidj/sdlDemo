#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "renderEngine.h"

int mouseX = 0, mouseY = 0;
int pMouseX = 0, pMouseY = 0;

renderEngine::renderEngine(int width, int height) {
	this->width = width;
	this->height = height;
	gRenderer = NULL;
	gWindow = NULL;
	gSurface = NULL;
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

void renderEngine::clearScreen() {
	SDL_SetRenderDrawColor(gRenderer, 200, 0, 100, 255);
	SDL_RenderClear(gRenderer);
}

bool renderEngine::start() {
	if (!init()) {
		return false;
	}

	clearScreen();
	SDL_Event event;

	SDL_SetEventFilter([](void* userdata, SDL_Event* event) -> int {
		if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_RESIZED) {
			((renderEngine*)userdata)->clearScreen();
			return 0;
		} return 1;}, this);

	while (!quit) {

		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) quit = true;
			else if (event.type == SDL_WINDOWEVENT_EXPOSED) {
				clearScreen();
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					quit = true;
					break;

				case SDLK_r:
					SDL_SetRenderDrawColor(gRenderer, 200, 0, 100, 255);
					SDL_RenderClear(gRenderer);
					break;

				}
			}
			else if (event.type == SDL_MOUSEMOTION) {
				pMouseX = mouseX;
				pMouseY = mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
			}
		}

		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(gRenderer, pMouseX, pMouseY, mouseX, mouseY);

		SDL_RenderPresent(gRenderer);
		SDL_Delay(0);
	}

	renderEngine::close();
	return true;
}