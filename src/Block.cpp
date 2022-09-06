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
			// NOTE(__LUNA__): Accelerate block... so fix it
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
		block.x += x * m_dx;
		block.y += y * m_dy;
	}
}

bool Block::hit (const Block *block) const {
	if ((m_block[0].x == block->m_block[0].x ||
		 m_block[1].x == block->m_block[1].x ||
		 m_block[2].x == block->m_block[2].x ||
		 m_block[3].x == block->m_block[3].x) &&
		(m_block[0].y + (2 * m_block[0].h) > block->m_block[0].y ||
		 m_block[1].y + (2 * m_block[1].h) > block->m_block[1].y ||
		 m_block[2].y + (2 * m_block[2].h) > block->m_block[2].y ||
		 m_block[3].y + (2 * m_block[3].h) > block->m_block[3].y)) {
			return true;
		 }
	return false;
}

void Block::update() {
	for (auto &block: m_block) {
		block.y += m_dy;
	}
}

void Block::render(SDL_Renderer *renderer) const {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRects(renderer, m_block, BLOCK_PIECES);
}

I_Block::I_Block(int x, int y, int w, int h) 
	: Block(x, y, w, h) {
		m_block[0] = {x + (0 * w), y + (0 * h), w, h};
		m_block[1] = {x + (1 * w), y + (0 * h), w, h};
		m_block[2] = {x + (2 * w), y + (0 * h), w, h};
		m_block[3] = {x + (3 * w), y + (0 * h), w, h};
}

void I_Block::rotate() {
	std::cout << "I ROTIAITION" << std::endl;
}

J_Block::J_Block(int x, int y, int w, int h)
	: Block(x, y, w, h) {
		m_block[0] = {x + (0 * w), y + (0 * h), w, h};
		m_block[1] = {x + (0 * w), y + (1 * h), w, h};
		m_block[2] = {x + (1 * w), y + (1 * h), w, h};
		m_block[3] = {x + (2 * w), y + (1 * h), w, h};
	}

void J_Block::rotate() {
	std::cout << "ROTTIES" << std::endl;
}

L_Block::L_Block(int x, int y, int w, int h)
	: Block(x, y, w, h) {
		m_block[0] = {x + (0 * w), y + (0 * h), w, h};
		m_block[1] = {x + (1 * w), y + (0 * h), w, h};
		m_block[2] = {x + (2 * w), y + (0 * h), w, h};
		m_block[3] = {x + (0 * w), y + (1 * h), w, h};
	}

void L_Block::rotate() {
	std::cout << "SKTRA" << std::endl;

}

O_Block::O_Block(int x, int y, int w, int h)
	: Block(x, y, w, h) {
		m_block[0] = {x + (0 * w), y + (0 * h), w, h};
		m_block[1] = {x + (0 * w), y + (1 * h), w, h};
		m_block[2] = {x + (1 * w), y + (0 * h), w, h};
		m_block[3] = {x + (1 * w), y + (1 * h), w, h};
	}

S_Block::S_Block(int x, int y, int w, int h)
	: Block(x, y, w, h) {
		m_block[0] = {x + (0 * w), y + (1 * h), w, h};
		m_block[1] = {x + (1 * w), y + (1 * h), w, h};
		m_block[2] = {x + (1 * w), y + (0 * h), w, h};
		m_block[3] = {x + (2 * w), y + (0 * h), w, h};
	}

void S_Block::rotate() {
	std::cout << "RSTTIES" << std::endl;
}

T_Block::T_Block(int x, int y, int w, int h)
	: Block(x, y, w, h) {
		m_block[0] = {x + (0 * w), y + (1 * h), w, h};
		m_block[1] = {x + (1 * w), y + (1 * h), w, h};
		m_block[2] = {x + (1 * w), y + (0 * h), w, h};
		m_block[3] = {x + (2 * w), y + (1 * h), w, h};
	}

void T_Block::rotate() {
	std::cout << "RTTTIET" << std::endl;
}

Z_Block::Z_Block(int x, int y, int w, int h)
	: Block(x, y, w, h) {
		m_block[0] = {x + (0 * w), y + (0 * h), w, h};
		m_block[1] = {x + (1 * w), y + (0 * h), w, h};
		m_block[2] = {x + (1 * w), y + (1 * h), w, h};
		m_block[3] = {x + (2 * w), y + (1 * h), w, h};
	}

void Z_Block::rotate() {
	std::cout << "RZZZIEZ" << std::endl;
}
