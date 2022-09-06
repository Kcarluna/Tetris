#include <iostream>
#include <random>
#include "Board.h"

Board::Board(int x, int y, int w, int h)
	: m_board({x, y, w, h}) {
		m_current_block = new L_Block(m_board.x, m_board.y, GAP, GAP);
	}

Board::~Board() {
	delete m_current_block;
	for (auto &block: m_active_blocks) {
		delete block;
	}
}

int random_num() {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist7(0, 6);
	return dist7(rng);
}

Block *Board::generate_new_block() {
	Block *temp = NULL;
		switch (random_num()) {
			case 0: {
				temp = new I_Block(m_board.x, m_board.y, GAP, GAP);
			} break;
			case 1: {
				temp = new J_Block(m_board.x, m_board.y, GAP, GAP);
			} break;
			case 2: {
				temp = new L_Block(m_board.x, m_board.y, GAP, GAP);
			} break;
			case 3: {
				temp = new O_Block(m_board.x, m_board.y, GAP, GAP);
			} break;
			case 4: {
				temp = new S_Block(m_board.x, m_board.y, GAP, GAP);
			} break;
			case 5: {
				temp = new T_Block(m_board.x, m_board.y, GAP, GAP);
			} break;
			case 6: {
				temp = new Z_Block(m_board.x, m_board.y, GAP, GAP);
			} break;
		}
	return temp;
}

void Board::update_board() {
	for (const auto &block: m_active_blocks) {
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				if ((block->get_x(0) == m_board.x + (j * GAP) && block->get_y(0) == m_board.y + (i * GAP)) ||
					(block->get_x(1) == m_board.x + (j * GAP) && block->get_y(1) == m_board.y + (i * GAP)) ||
					(block->get_x(2) == m_board.x + (j * GAP) && block->get_y(2) == m_board.y + (i * GAP)) ||
					(block->get_x(3) == m_board.x + (j * GAP) && block->get_y(3) == m_board.y + (i * GAP))) {
						m_data[i][j] = 1;
					}
			}
		}
	}
}

void Board::update() {
	for (int i = 0; i < ROWS - 1; i++) {
		for (int j = 0; j < COLS - 1; j++) {
			if ((m_current_block->get_x(0) == m_board.x + (j * GAP) && m_current_block->get_y(0) == m_board.y + (i * GAP)) ||
				(m_current_block->get_x(1) == m_board.x + (j * GAP) && m_current_block->get_y(1) == m_board.y + (i * GAP)) ||
				(m_current_block->get_x(2) == m_board.x + (j * GAP) && m_current_block->get_y(2) == m_board.y + (i * GAP)) ||
				(m_current_block->get_x(3) == m_board.x + (j * GAP) && m_current_block->get_y(3) == m_board.y + (i * GAP))) {
					if (m_data[i + 1][j] == 1) {
						m_hit = true;
						goto endloop;
					}
				}
		}
	}

endloop:
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_W]) {
		m_current_block->rotate();
	} else if (state[SDL_SCANCODE_A] && m_current_block->in_lower_x(m_board.x)) {
		m_current_block->move(LEFT);
	} else if (state[SDL_SCANCODE_S] && m_current_block->in_upper_y(m_board.y + m_board.h)) {
		m_current_block->move(DOWN);
	} else if (state[SDL_SCANCODE_D] && m_current_block->in_upper_x(m_board.x + m_board.w)) {
		m_current_block->move(RIGHT);
	}
	if (m_current_block->in_upper_y(m_board.y + m_board.h) && !m_hit) {
		m_current_block->update();
	} else {
		m_active_blocks.push_back(m_current_block);
		m_current_block = generate_new_block();
		m_hit = false;
	}
	update_board();
}

void Board::print_board() const {
	std::cout << "-----------------------" << std::endl;
	std::cout << "   ";
	for (int i = 0; i < COLS; i++) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < ROWS; i++) {
		if (i > 9) {
			std::cout << i << " ";
		} else {
			std::cout << i << "  ";
		}
		for (int j = 0; j < COLS; j++) {
			std::cout << m_data[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "-----------------------" << std::endl;

}

void Board::render(SDL_Renderer *renderer) const {
	SDL_SetRenderDrawColor(renderer, 150, 150, 150, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 150, 100, 50, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &m_board);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	for (int x = 0; x <= COLS; x++) {
		SDL_RenderDrawLine(renderer, m_board.x + (x * GAP), 0, m_board.x + (x * GAP), m_board.h);
	}
	for (int y = 0; y <= ROWS; y++) {
		SDL_RenderDrawLine(renderer, m_board.x, m_board.y + (y * GAP), m_board.x + m_board.w, m_board.y + (y * GAP));
	}
	for (const auto &block: m_active_blocks) {
		block->render(renderer);
	}
	m_current_block->render(renderer);
	//print_board();
	SDL_RenderPresent(renderer);
}
