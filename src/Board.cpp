#include <iostream>
#include <random>
#include "Board.h"

Board::Board(int x, int y, int w, int h)
	: m_board({x, y, w, h}) {
		m_current_block = generate_new_block(); 
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

void Board::clear_row(int index) {
	for (int j = 0; j < COLS; j++) {
		m_data[index][j] = '\0';
	}
	auto it = m_active_blocks.begin();
	for (auto &block: m_active_blocks) {
		for (int j = 0; j < COLS; j++) {
			if (block->get_x(0) == m_board.x + (j * GAP) && block->get_y(0) == m_board.y + (index * GAP)) {
				block->clear(0);
			}
			if (block->get_x(1) == m_board.x + (j * GAP) && block->get_y(1) == m_board.y + (index * GAP)) {
				block->clear(1);
			}
			if (block->get_x(2) == m_board.x + (j * GAP) && block->get_y(2) == m_board.y + (index * GAP)) {
				block->clear(2);
			}
			if (block->get_x(3) == m_board.x + (j * GAP) && block->get_y(3) == m_board.y + (index * GAP)) {
				block->clear(3);
			}
		}
		if (block->is_empty()) {
			m_active_blocks.erase(it);
		}
		it++;
	}
}

void Board::move_row(int index) {
	for (int i = index; i > -1; i--) {
		for (int j = 0; j < COLS; j++) {
			if (m_data[i][j] == 'x') {
				m_data[i][j] = '\0';
				m_data[i + 1][j] = 'x';
			}
			for (auto &block: m_active_blocks) {
				if (block->get_x(0) == m_board.x + (j * GAP) && block->get_y(0) == m_board.y + (i * GAP)) {
					block->move(0, DOWN);
				}
				if (block->get_x(1) == m_board.x + (j * GAP) && block->get_y(1) == m_board.y + (i * GAP)) {
					block->move(1, DOWN);
				}
				if (block->get_x(2) == m_board.x + (j * GAP) && block->get_y(2) == m_board.y + (i * GAP)) {
					block->move(2, DOWN);
				}
				if (block->get_x(3) == m_board.x + (j * GAP) && block->get_y(3) == m_board.y + (i * GAP)) {
					block->move(3, DOWN);
				}
			}
		}
	}
}

void Board::update_board() {
	for (const auto &block: m_active_blocks) {
		for (int i = 0; i < ROWS; i++) {
			int count = 0;
			for (int j = 0; j < COLS; j++) {
				if ((block->get_x(0) == m_board.x + (j * GAP) && block->get_y(0) == m_board.y + (i * GAP) && m_data[i][j] != 'x') ||
					(block->get_x(1) == m_board.x + (j * GAP) && block->get_y(1) == m_board.y + (i * GAP) && m_data[i][j] != 'x') ||
					(block->get_x(2) == m_board.x + (j * GAP) && block->get_y(2) == m_board.y + (i * GAP) && m_data[i][j] != 'x') ||
					(block->get_x(3) == m_board.x + (j * GAP) && block->get_y(3) == m_board.y + (i * GAP) && m_data[i][j] != 'x')) {
						m_data[i][j] = 'x';
					}
				if (m_data[i][j] == 'x') {
					count++;
				}
				if (count == COLS) {
					// NOTE(__LUNA__): Move from top to bottom
					clear_row(i);
					move_row(i - 1);
				}
			}
		}
	}
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
			if (!m_data[i][j]) {
				std::cout << "- ";
			} else {
				std::cout << m_data[i][j] << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << "-----------------------" << std::endl;
}

bool Board::can_move(Dir dir) const {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if ((m_current_block->get_x(0) == m_board.x + (j * GAP) && m_current_block->get_y(0) == m_board.y + (i * GAP)) ||
				(m_current_block->get_x(1) == m_board.x + (j * GAP) && m_current_block->get_y(1) == m_board.y + (i * GAP)) ||
				(m_current_block->get_x(2) == m_board.x + (j * GAP) && m_current_block->get_y(2) == m_board.y + (i * GAP)) ||
				(m_current_block->get_x(3) == m_board.x + (j * GAP) && m_current_block->get_y(3) == m_board.y + (i * GAP))) {
					if (dir == LEFT) {
						if (m_data[i][j - 1] == 'x') {
							return false;
						}
					} else if (dir == DOWN) {
						if (m_data[i + 2][j] == 'x') {
							return false;
						}
					} else if (dir == RIGHT) {
						if (m_data[i][j + 1] == 'x') {
							return false;
						}
					}
				}
		}
	}
	return true;
}

void Board::update() {
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_W]) {
		m_current_block->rotate();
	} else if (state[SDL_SCANCODE_A] && m_current_block->in_lower_x(m_board.x) && can_move(LEFT)) {
		m_current_block->move(LEFT);
	} else if (state[SDL_SCANCODE_S] && m_current_block->in_upper_y(m_board.y + m_board.h) && can_move(DOWN)) {
		m_current_block->move(DOWN);
	} else if (state[SDL_SCANCODE_D] && m_current_block->in_upper_x(m_board.x + m_board.w) && can_move(RIGHT)) {
		m_current_block->move(RIGHT);
	}
	for (int i = 0; i < ROWS - 1; i++) {
		for (int j = 0; j < COLS; j++) {
			if ((m_current_block->get_x(0) == m_board.x + (j * GAP) && m_current_block->get_y(0) == m_board.y + (i * GAP)) ||
				(m_current_block->get_x(1) == m_board.x + (j * GAP) && m_current_block->get_y(1) == m_board.y + (i * GAP)) ||
				(m_current_block->get_x(2) == m_board.x + (j * GAP) && m_current_block->get_y(2) == m_board.y + (i * GAP)) ||
				(m_current_block->get_x(3) == m_board.x + (j * GAP) && m_current_block->get_y(3) == m_board.y + (i * GAP))) {
					if (m_data[i + 1][j] == 'x') {
						m_hit = true;
						goto endloop;
					}
				}
		}
	}
	endloop:
	if (m_current_block->in_upper_y(m_board.y + m_board.h) && !m_hit) {
		m_current_block->update();
	} else {
		m_active_blocks.push_back(m_current_block);
		m_current_block = generate_new_block();
		m_hit = false;
	}
	update_board();
}

void Board::render(SDL_Renderer *renderer) const {
	SDL_SetRenderDrawColor(renderer, 150, 150, 150, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 150, 100, 50, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &m_board);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	for (const auto &block: m_active_blocks) {
		block->render(renderer);
	}
	m_current_block->render(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	for (int x = 0; x <= COLS; x++) {
		SDL_RenderDrawLine(renderer, m_board.x + (x * GAP), 0, m_board.x + (x * GAP), m_board.h);
	}
	for (int y = 0; y <= ROWS; y++) {
		SDL_RenderDrawLine(renderer, m_board.x, m_board.y + (y * GAP), m_board.x + m_board.w, m_board.y + (y * GAP));
	}
	//print_board();
	SDL_RenderPresent(renderer);
}
