#include "SDL.h"
#include "GL\gl3w.h"

int main(int argc, char *argv[])
{
	// SDL initialization
	SDL_Window* window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Event* event = new SDL_Event();
	SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	bool quit = false;
	//still not working
	//gl3wInit();


	// Main loop
	while (!quit && event->type != SDL_QUIT) {
		SDL_PollEvent(event);
		SDL_RenderClear(render);

		if (event->type == SDL_KEYDOWN) {
			switch (event->key.keysym.sym) {
			case SDLK_ESCAPE:
				quit = true;
				break;
			default:
				break;
			}
		}

		// Draw some primitives
		SDL_Rect fillRect = { 640 / 4, 480 / 4, 640 / 2, 480 / 2 };
		SDL_SetRenderDrawColor(render, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(render, &fillRect);
		SDL_Rect outlineRect = { 640 / 6, 480 / 6, 640 * 2 / 3, 480 * 2 / 3 };
		SDL_SetRenderDrawColor(render, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawRect(render, &outlineRect);

		// Update SDL screen
		SDL_RenderPresent(render);

	
	}

	return 0;
}