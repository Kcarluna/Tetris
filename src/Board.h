#pragma once
#include <SDL.h>
#include <vector>
#include "Block.h"

#define ROWS 24
#define COLS 10

#define GAP 32

class Board {
private:
	SDL_Rect m_board;
	Block *m_current_block;
	std::vector<Block *> m_active_blocks;

	char m_data[ROWS][COLS] = {{0}};
	bool m_hit = false;
public:
	Board() = default;
	Board(int x, int y, int w, int h);
	~Board();

	Block *generate_new_block();
	void clear_row(int index);
	void move_rows(int index);
	void update_board();
	void print_board() const;
	bool can_move(Dir dir) const;
	void update();
	void render(SDL_Renderer *renderer) const;
};
