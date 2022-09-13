#include <iostream>
#include "Game.h"

Game::Game(int x, int y, int w, int h) {
	m_board = new Board(x, y, w, h);
}

void Game::update() {
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_W]) {
		m_board->rotate_block();
	} else if (state[SDL_SCANCODE_A]) {
		m_board->move_block(LEFT);
	} else if (state[SDL_SCANCODE_S]) {
		m_board->move_block(DOWN);
	} else if (state[SDL_SCANCODE_D]) {
		m_board->move_block(RIGHT);
	}
	m_board->update();
}

void Game::render(SDL_Renderer *renderer) const {
	m_board->render(renderer);
}
