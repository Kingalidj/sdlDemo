#pragma once

class renderEngine {
private:
	SDL_Window* gWindow = NULL;
	SDL_Surface* gSurface = NULL;
	SDL_Renderer* gRenderer = NULL;
	int height, width;
	bool quit = false;
	bool init();
	void close();

public:
	renderEngine(int width, int height);
	bool start();
};
