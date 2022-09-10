#pragma once
#include <SDL.h>
#include "Board.h"

#define BOARD_SIZE (COLS * GAP)

class Game {
private:
	Board *m_board;
public:
	Game(int x, int y, int w, int h);

	void update();
	void render(SDL_Renderer *renderer) const;
};
