#include <iostream>
#include "Game.h"

Game::Game(int x, int y, int w, int h) {
	m_board = new Board(x, y, w, h);
}

void Game::update() {
	m_board->update();
}

void Game::render(SDL_Renderer *renderer) const {
	m_board->render(renderer);
}
