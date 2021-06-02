#pragma once
#include <SDL.h>

class renderEngine {
	SDL_Window* gWindow;
	SDL_Surface* gSurface;
	SDL_Renderer* gRenderer;
	int height, width;
	bool quit = false;
	bool init();
	void close();

public:
	renderEngine(int width, int height);
	bool start();
	void clearScreen();
};
