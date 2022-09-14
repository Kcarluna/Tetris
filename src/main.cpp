#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Game.h"

#define WIDTH 1024
#define HEIGHT 768

#define FPS 120

void check_val(int val) {
	if (val < 0) {
		std::cerr << "ERROR: " << SDL_GetError() << std::endl;
		exit(1);
	}
}

void *check_ptr(void *ptr) {
	if (ptr == NULL) {
		std::cerr << "ERROR: " << SDL_GetError() << std::endl;
		exit(1);
	}
	return ptr;
}

int main() {
	check_val(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER));
	check_val(TTF_Init());
	SDL_Window *window = static_cast<SDL_Window *>(check_ptr(SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE)));
	SDL_Renderer *renderer = static_cast<SDL_Renderer *>(check_ptr(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)));

	Game game((WIDTH / 2) - (BOARD_SIZE / 2), 0, BOARD_SIZE, HEIGHT);
	bool quit = false;
	while (!quit) {
		SDL_Event event = {0};
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: {
					quit = true;
				} break;
			}
		}
		game.update();
		game.render(renderer);
		// NOTE(__LUNA__): Am I doing this right?
		SDL_Delay(FPS);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
