#include <iostream>
#include "Game.h"

#define FONT_SIZE 80

TTF_Font *init_font() {
	TTF_Font *font = TTF_OpenFont("../fonts/Roboto-Regular.ttf", FONT_SIZE);
	if (!font) {
		std::cerr << "ERROR: " << TTF_GetError() << std::endl;
		exit(1);
	}
	return font;
}

#define SCORE_BOARD_WIDTH 175
#define SCORE_BOARD_HEIGHT 88
#define PADDING 10

Game::Game(int x, int y, int w, int h) 
	: m_font(init_font()) {
		m_board = new Board(x, y, w, h);
		m_score_board = {(x + w) +  (SCORE_BOARD_WIDTH / 2), y + PADDING, SCORE_BOARD_WIDTH, SCORE_BOARD_HEIGHT};
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
	} else if (state[SDL_SCANCODE_SPACE]) {
		m_board->drop_block();
	}
	if (!m_board->game_over()) {
		m_board->update();
	} else {
		std::cout << "GGS" << std::endl;
	}
}

void Game::query_text() {
	int w, h;
	SDL_QueryTexture(m_texture, NULL, NULL, &w, &h);
	m_score_board_dstrect = {(m_score_board.x + (m_score_board.w / 2)) - (w / 2), m_score_board.y, w, h};
}

void Game::update_score(SDL_Renderer *renderer) {
	SDL_Color color = {.r = 255, .g = 255, .b = 255};
	m_surface = TTF_RenderText_Solid(m_font, std::to_string(m_board->get_score()).c_str(), color);
	m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
	SDL_FreeSurface(m_surface);
	query_text();
}

void Game::render_score(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &m_score_board);
	SDL_RenderCopy(renderer, m_texture, NULL, &m_score_board_dstrect);
	SDL_DestroyTexture(m_texture);
}

void Game::render(SDL_Renderer *renderer) {
	m_board->render(renderer);
	update_score(renderer);
	render_score(renderer);

	SDL_RenderPresent(renderer);
}
