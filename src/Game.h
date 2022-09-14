#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Board.h"

#define BOARD_SIZE (COLS * GAP)

class Game {
private:
	Board *m_board;

	SDL_Rect m_score_board;
	SDL_Rect m_score_board_dstrect;
	SDL_Surface *m_surface;
	SDL_Texture *m_texture;
	TTF_Font *m_font;
public:
	Game(int x, int y, int w, int h);

	void update();
	void query_text();
	void update_score(SDL_Renderer *renderer);
	void render_score(SDL_Renderer *renderer);
	void render(SDL_Renderer *renderer);
};
