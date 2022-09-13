#pragma once
#include <SDL.h>
#include <vector>
#include "Block.h"

#define ROWS 24
#define COLS 10
#define GAP 32

#define QUEUE_SIZE 5
#define QUEUE_BLOCK_SIZE 28
#define QUEUE_RECT_WIDTH 252
#define QUEUE_RECT_HEIGHT 420

class Board {
private:
	SDL_Rect m_board;
	Block *m_current_block;
	std::vector<Block *> m_active_blocks;
	SDL_Rect m_queue_rect;
	std::vector<Block *> m_blocks_queue;

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
	void rotate_block();
	void move_block(Dir dir);
	void update();
	void render_queue(SDL_Renderer *renderer) const;
	void render(SDL_Renderer *renderer) const;
};
