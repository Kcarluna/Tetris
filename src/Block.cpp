#include <iostream>
#include "Block.h"

Block::Block(int x, int y, int w, int h)
	: m_x(x), m_y(y), m_w(w), m_h(h) {
		m_dx = w;
		m_dy = h;
	}

int Block::get_x(int index) const {
	return m_block[index].x;
}

int Block::get_y(int index) const {
	return m_block[index].y;
}


bool Block::in_lower_x(int x) const {
	return (m_block[0].x > x &&
			m_block[1].x > x &&
			m_block[2].x > x &&
			m_block[3].x > x);
}

bool Block::in_upper_x(int x) const {
	return (m_block[0].x + m_block[0].w < x &&
			m_block[1].x + m_block[1].w < x &&
			m_block[2].x + m_block[2].w < x &&
			m_block[3].x + m_block[3].w < x);
}

bool Block::in_lower_y(int y) const {
	return (m_block[0].y >= y &&
			m_block[1].y >= y &&
			m_block[2].y >= y &&
			m_block[3].y >= y);
}

bool Block::in_upper_y(int y) const {
	return (m_block[0].y + m_block[0].h < y &&
			m_block[1].y + m_block[1].h < y &&
			m_block[2].y + m_block[2].h < y &&
			m_block[3].y + m_block[3].h < y);
}

void Block::move(Dir dir) {
	int x, y;
	switch (dir) {
		case LEFT: {
			x = -1;
			y = 0;
		} break;
		case DOWN: {
			x = 0;
			y = 1;
		} break;
		case RIGHT: {
			x = 1;
			y = 0;
		} break;
		default: {
		} break;
	}
	for (auto &block: m_block) {
		if (!SDL_RectEmpty(&block)) {
			block.x += x * m_dx;
			block.y += y * m_dy;
		}
	}
}

void Block::move(int index, Dir dir) {
	switch (dir) {
		case DOWN: {
			m_block[index].y += m_dx;
		} break;
		default: {
		} break;
	}
}

void Block::clear(int index) {
	m_block[index] = {};
}

bool Block::is_empty() const {
	return (SDL_RectEmpty(&m_block[0]) &&
			SDL_RectEmpty(&m_block[1]) &&
			SDL_RectEmpty(&m_block[2]) &&
			SDL_RectEmpty(&m_block[3]));
}

void Block::update() {
	for (auto &block: m_block) {
		block.y += m_dy;
	}
}

void Block::render(SDL_Renderer *renderer) const {
	SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRects(renderer, m_block, BLOCK_PIECES);
}

I_Block::I_Block(int x, int y, int w, int h) 
	: Block(x, y, w, h) {
		m_block[0] = {x + (3 * w), y + (0 * h), w, h};
		m_block[1] = {x + (4 * w), y + (0 * h), w, h};
		m_block[2] = {x + (5 * w), y + (0 * h), w, h};
		m_block[3] = {x + (6 * w), y + (0 * h), w, h};

		m_color = {.r = 0, .g = 255, .b = 255};
}

void I_Block::rotate() {
	switch (m_dir) {
		case UP: {
			m_dir = DOWN;
			m_block[0] = {m_block[0].x - (2 * m_w), m_block[0].y - (2 * m_h), m_w, m_h};
			m_block[1] = {m_block[1].x - (1 * m_w), m_block[1].y - (1 * m_h), m_w, m_h};
			m_block[2] = {m_block[2].x + (0 * m_w), m_block[2].y + (0 * m_h), m_w, m_h};
			m_block[3] = {m_block[3].x + (1 * m_w), m_block[3].y + (1 * m_h), m_w, m_h};
		} break;
		case DOWN: {
			m_dir = UP;
			m_block[0] = {m_block[0].x + (2 * m_w), m_block[0].y + (2 * m_h), m_w, m_h};
			m_block[1] = {m_block[1].x + (1 * m_w), m_block[1].y + (1 * m_h), m_w, m_h};
			m_block[2] = {m_block[2].x + (0 * m_w), m_block[2].y + (0 * m_h), m_w, m_h};
			m_block[3] = {m_block[3].x - (1 * m_w), m_block[3].y - (1 * m_h), m_w, m_h};
		} break;
		default: {
		} break;
	}
}

J_Block::J_Block(int x, int y, int w, int h)
	: Block(x, y, w, h) {
		m_block[0] = {x + (3 * w), y + (0 * h), w, h};
		m_block[1] = {x + (4 * w), y + (0 * h), w, h};
		m_block[2] = {x + (5 * w), y + (0 * h), w, h};
		m_block[3] = {x + (5 * w), y + (1 * h), w, h};

		m_color = {.r = 0, .g = 0, .b = 255};
	}

void J_Block::rotate() {
	switch (m_dir) {
		case UP: {
			m_dir = LEFT;
			m_block[0] = {m_block[0].x + (0 * m_w), m_block[0].y + (0 * m_h), m_w, m_h};
			m_block[1] = {m_block[1].x - (1 * m_w), m_block[1].y - (2 * m_h), m_w, m_h};
			m_block[2] = {m_block[2].x + (0 * m_w), m_block[2].y + (0 * m_h), m_w, m_h};
			m_block[3] = {m_block[3].x + (1 * m_w), m_block[3].y + (0 * m_h), m_w, m_h};
		} break;
		case LEFT: {
			m_dir = DOWN;
			m_block[0] = {m_block[0].x - (1 * m_w), m_block[0].y - (1 * m_h), m_w, m_h};
			m_block[1] = {m_block[1].x + (0 * m_w), m_block[1].y + (1 * m_h), m_w, m_h};
			m_block[2] = {m_block[2].x + (2 * m_w), m_block[2].y - (1 * m_h), m_w, m_h};
			m_block[3] = {m_block[3].x + (1 * m_w), m_block[3].y + (1 * m_h), m_w, m_h};
		} break;
		case DOWN: {
			m_dir = RIGHT;
			m_block[0] = {m_block[0].x + (1 * m_w), m_block[0].y + (1 * m_h), m_w, m_h};
			m_block[1] = {m_block[1].x + (0 * m_w), m_block[1].y + (0 * m_h), m_w, m_h};
			m_block[2] = {m_block[2].x - (1 * m_w), m_block[2].y - (1 * m_h), m_w, m_h};
			m_block[3] = {m_block[3].x + (0 * m_w), m_block[3].y - (2 * m_h), m_w, m_h};
		} break;
		case RIGHT: {
			m_dir = UP;
			m_block[0] = {m_block[0].x + (0 * m_w), m_block[0].y + (0 * m_h), m_w, m_h};
			m_block[1] = {m_block[1].x + (1 * m_w), m_block[1].y + (1 * m_h), m_w, m_h};
			m_block[2] = {m_block[2].x - (1 * m_w), m_block[2].y + (2 * m_h), m_w, m_h};
			m_block[3] = {m_block[3].x - (2 * m_w), m_block[3].y + (1 * m_h), m_w, m_h};
		} break;
	}
}

L_Block::L_Block(int x, int y, int w, int h)
	: Block(x, y, w, h) {
		m_block[0] = {x + (3 * w), y + (0 * h), w, h};
		m_block[1] = {x + (4 * w), y + (0 * h), w, h};
		m_block[2] = {x + (5 * w), y + (0 * h), w, h};
		m_block[3] = {x + (3 * w), y + (1 * h), w, h};

		m_color = {.r = 255, .g = 127, .b = 0};
	}

void L_Block::rotate() {
	switch (m_dir) {
		case UP: {
			m_dir = LEFT;
			m_block[0] = {m_block[0].x + (0 * m_w), m_block[0].y - (1 * m_h), m_w, m_h};
			m_block[1] = {m_block[1].x - (1 * m_w), m_block[1].y - (1 * m_h), m_w, m_h};
			m_block[2] = {m_block[2].x + (0 * m_w), m_block[2].y - (2 * m_h), m_w, m_h};
			m_block[3] = {m_block[3].x - (1 * m_w), m_block[3].y + (0 * m_h), m_w, m_h};
		} break;
		case LEFT: {
			m_dir = DOWN;
			m_block[0] = {m_block[0].x - (1 * m_w), m_block[0].y + (0 * m_h), m_w, m_h};
			m_block[1] = {m_block[1].x + (0 * m_w), m_block[1].y + (1 * m_h), m_w, m_h};
			m_block[2] = {m_block[2].x + (2 * m_w), m_block[2].y + (1 * m_h), m_w, m_h};
			m_block[3] = {m_block[3].x - (1 * m_w), m_block[3].y + (0 * m_h), m_w, m_h};
		} break;
		case DOWN: {
			m_dir = RIGHT;
			m_block[0] = {m_block[0].x + (1 * m_w), m_block[0].y + (1 * m_h), m_w, m_h};
			m_block[1] = {m_block[1].x + (0 * m_w), m_block[1].y + (0 * m_h), m_w, m_h};
			m_block[2] = {m_block[2].x - (1 * m_w), m_block[2].y - (1 * m_h), m_w, m_h};
			m_block[3] = {m_block[3].x + (2 * m_w), m_block[3].y + (0 * m_h), m_w, m_h};
		} break;
		case RIGHT: {
			m_dir = UP;
			m_block[0] = {m_block[0].x + (0 * m_w), m_block[0].y + (0 * m_h), m_w, m_h};
			m_block[1] = {m_block[1].x + (1 * m_w), m_block[1].y + (0 * m_h), m_w, m_h};
			m_block[2] = {m_block[2].x - (1 * m_w), m_block[2].y + (2 * m_h), m_w, m_h};
			m_block[3] = {m_block[3].x + (0 * m_w), m_block[3].y + (0 * m_h), m_w, m_h};
		} break;
	}
}

O_Block::O_Block(int x, int y, int w, int h)
	: Block(x, y, w, h) {
		m_block[0] = {x + (4 * w), y + (0 * h), w, h};
		m_block[1] = {x + (4 * w), y + (1 * h), w, h};
		m_block[2] = {x + (5 * w), y + (0 * h), w, h};
		m_block[3] = {x + (5 * w), y + (1 * h), w, h};

		m_color = {.r = 255, .g = 255, .b = 0};
	}

S_Block::S_Block(int x, int y, int w, int h)
	: Block(x, y, w, h) {
		m_block[0] = {x + (3 * w), y + (1 * h), w, h};
		m_block[1] = {x + (4 * w), y + (1 * h), w, h};
		m_block[2] = {x + (4 * w), y + (0 * h), w, h};
		m_block[3] = {x + (5 * w), y + (0 * h), w, h};

		m_color = {.r = 0, .g = 255, .b = 0};
	}

void S_Block::rotate() {
	switch (m_dir) {
		case UP: {
			m_dir = DOWN;
			m_block[0] = {m_block[0].x - (1 * m_w), m_block[0].y - (1 * m_h), m_w, m_h};
			m_block[1] = {m_block[1].x + (0 * m_w), m_block[1].y + (0 * m_h), m_w, m_h};
			m_block[2] = {m_block[2].x + (1 * m_w), m_block[2].y - (1 * m_h), m_w, m_h};
			m_block[3] = {m_block[3].x + (2 * m_w), m_block[3].y + (0 * m_h), m_w, m_h};
		} break;
		case DOWN: {
			m_dir = UP;
			m_block[0] = {m_block[0].x + (1 * m_w), m_block[0].y + (1 * m_h), m_w, m_h};
			m_block[1] = {m_block[1].x + (0 * m_w), m_block[1].y + (0 * m_h), m_w, m_h};
			m_block[2] = {m_block[2].x - (1 * m_w), m_block[2].y + (1 * m_h), m_w, m_h};
			m_block[3] = {m_block[3].x - (2 * m_w), m_block[3].y + (0 * m_h), m_w, m_h};
		} break;
		default: {
		} break;
	}
}

T_Block::T_Block(int x, int y, int w, int h)
	: Block(x, y, w, h) {
		m_block[0] = {x + (3 * w), y + (0 * h), w, h};
		m_block[1] = {x + (4 * w), y + (0 * h), w, h};
		m_block[2] = {x + (5 * w), y + (0 * h), w, h};
		m_block[3] = {x + (4 * w), y + (1 * h), w, h};

		m_color = {.r = 128, .g = 0, .b = 128};
	}

void T_Block::rotate() {
	switch (m_dir) {
		case UP: {
			m_dir = LEFT;
			m_block[0] = {m_block[0].x + (0 * m_w), m_block[0].y - (1 * m_h), m_w, m_h};
			m_block[1] = {m_block[1].x + (0 * m_w), m_block[1].y + (0 * m_h), m_w, m_h};
			m_block[2] = {m_block[2].x - (1 * m_w), m_block[2].y - (2 * m_h), m_w, m_h};
			m_block[3] = {m_block[3].x + (0 * m_w), m_block[3].y + (0 * m_h), m_w, m_h};
		} break;
		case LEFT: {
			m_dir = DOWN;
			m_block[0] = {m_block[0].x + (0 * m_w), m_block[0].y + (0 * m_h), m_w, m_h};
			m_block[1] = {m_block[1].x + (0 * m_w), m_block[1].y + (0 * m_h), m_w, m_h};
			m_block[2] = {m_block[2].x + (1 * m_w), m_block[2].y + (1 * m_h), m_w, m_h};
			m_block[3] = {m_block[3].x + (0 * m_w), m_block[3].y + (0 * m_h), m_w, m_h};
		} break;
		case DOWN: {
			m_dir = RIGHT;
			m_block[0] = {m_block[0].x + (1 * m_w), m_block[0].y - (1 * m_h), m_w, m_h};
			m_block[1] = {m_block[1].x + (0 * m_w), m_block[1].y + (0 * m_h), m_w, m_h};
			m_block[2] = {m_block[2].x + (0 * m_w), m_block[2].y + (0 * m_h), m_w, m_h};
			m_block[3] = {m_block[3].x + (0 * m_w), m_block[3].y + (0 * m_h), m_w, m_h};
		} break;
		case RIGHT: {
			m_dir = UP;
			m_block[0] = {m_block[0].x - (1 * m_w), m_block[0].y + (2 * m_h), m_w, m_h};
			m_block[1] = {m_block[1].x + (0 * m_w), m_block[1].y + (0 * m_h), m_w, m_h};
			m_block[2] = {m_block[2].x + (0 * m_w), m_block[2].y + (1 * m_h), m_w, m_h};
			m_block[3] = {m_block[3].x + (0 * m_w), m_block[3].y + (0 * m_h), m_w, m_h};
		} break;
	}
}

Z_Block::Z_Block(int x, int y, int w, int h)
	: Block(x, y, w, h) {
		m_block[0] = {x + (3 * w), y + (0 * h), w, h};
		m_block[1] = {x + (4 * w), y + (0 * h), w, h};
		m_block[2] = {x + (4 * w), y + (1 * h), w, h};
		m_block[3] = {x + (5 * w), y + (1 * h), w, h};

		m_color = {.r = 255, .g = 0, .b = 0};
	}

void Z_Block::rotate() {
	switch (m_dir) {
		case UP: {
			m_dir = DOWN;
			m_block[0] = {m_block[0].x - (2 * m_w), m_block[0].y + (1 * m_h), m_w, m_h};
			m_block[1] = {m_block[1].x + (0 * m_w), m_block[1].y + (0 * m_h), m_w, m_h};
			m_block[2] = {m_block[2].x + (0 * m_w), m_block[2].y + (0 * m_h), m_w, m_h};
			m_block[3] = {m_block[3].x + (0 * m_w), m_block[3].y + (1 * m_h), m_w, m_h};
		} break;
		case DOWN: {
			m_dir = UP;
			m_block[0] = {m_block[0].x + (2 * m_w), m_block[0].y - (1 * m_h), m_w, m_h};
			m_block[1] = {m_block[1].x + (0 * m_w), m_block[1].y + (0 * m_h), m_w, m_h};
			m_block[2] = {m_block[2].x + (0 * m_w), m_block[2].y + (0 * m_h), m_w, m_h};
			m_block[3] = {m_block[3].x + (0 * m_w), m_block[3].y - (1 * m_h), m_w, m_h};
		} break;
		default: {
		} break;
	}
}
