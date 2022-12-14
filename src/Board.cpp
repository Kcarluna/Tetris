#include <iostream>
#include <random>
#include <algorithm>
#include "Board.h"

Board::Board(int x, int y, int w, int h)
	: m_board({x, y, w, h}) {
		for (int i = 0; i < QUEUE_SIZE; i++) {
			m_blocks_queue.push_back(generate_new_block());
		}
		m_queue_rect = {x + w + (QUEUE_RECT_WIDTH / 5), (y + h) - ((4 * QUEUE_RECT_HEIGHT) / 3), QUEUE_RECT_WIDTH, QUEUE_RECT_HEIGHT};
		m_current_block = generate_new_block();
		m_score = 0;
	}

Board::~Board() {
	delete m_current_block;
	for (auto &block: m_active_blocks) {
		delete block;
	}
	for (auto &block: m_blocks_queue) {
		delete block;
	}
}

int Board::get_score() const {
	return m_score;
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

bool Board::game_over() const {
	for (int j = 0; j < COLS; j++) {
		if (m_data[0][j] == 'x') {
			return true;
		}
	}
	return false;
}

void Board::clear_row(int index) {
	for (int j = 0; j < COLS; j++) {
		m_data[index][j] = '\0';
	}
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
	}
	for (size_t i = 0; i < m_active_blocks.size(); i++) {
		if (m_active_blocks[i]->is_empty()) {
			delete m_active_blocks[i];
			m_active_blocks.erase(m_active_blocks.begin() + i);
		}
	}
}

void Board::move_rows(int index) {
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

void Board::update_score(const std::vector<int> &level, int amount) {
	int max_level = (level.size() > 0) ? *std::max_element(level.begin(), level.end()) : 0;
	// NOTE(__LUNA__): Bottom of Board is 0... top is 23
	max_level = ROWS - max_level;
	switch (amount) {
		case 1: {
			m_score += 40 * (max_level + 1);
		} break;
		case 2:  {
			m_score += 100 * (max_level + 1);
		} break;
		case 3: {
			m_score += 300 * (max_level + 1);
		} break;
		case 4: {
			m_score += 1200 * (max_level + 1);
		} break;
		default: {
		} break;
	}
}

void Board::update_board() {
	int lines = 0;
	std::vector<int> level;
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
					clear_row(i);
					move_rows(i - 1);
					lines++;
					level.push_back(i);
				}
			}
		}
	}
	update_score(level, lines);
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

void Board::rotate_block() {
	m_current_block->rotate();
}

void Board::move_block(Dir dir) {
	switch (dir) {
		case LEFT: {
			if (m_current_block->in_lower_x(m_board.x) && can_move(LEFT)) {
				m_current_block->move(LEFT);
			}
		} break;
		case DOWN: {
			if (m_current_block->in_upper_y(m_board.y + m_board.h) && can_move(DOWN)) {
				m_current_block->move(DOWN);
			}
		} break;
		case RIGHT: {
			if (m_current_block->in_upper_x(m_board.x + m_board.w) && can_move(RIGHT)) {
				m_current_block->move(RIGHT);
			}
		} break;
		default: {
		} break;
	}
}

void Board::drop_block() {
	while (m_current_block->in_upper_y(m_board.y + m_board.h) && can_move(DOWN)) {
		m_current_block->move(DOWN);
	}
}

void Board::update() {
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
		m_current_block = m_blocks_queue.front();
		m_blocks_queue.erase(m_blocks_queue.begin());
		m_blocks_queue.push_back(generate_new_block());
		m_hit = false;
	}
	update_board();
}

void Board::render_queue(SDL_Renderer *renderer) const {
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &m_queue_rect);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, m_queue_rect.x, m_queue_rect.y, m_queue_rect.x + m_queue_rect.w, m_queue_rect.y);
	SDL_RenderDrawLine(renderer, m_queue_rect.x + m_queue_rect.w, m_queue_rect.y, m_queue_rect.x + m_queue_rect.w, m_queue_rect.y + m_queue_rect.h);
	SDL_RenderDrawLine(renderer, m_queue_rect.x + m_queue_rect.w, m_queue_rect.y + m_queue_rect.h, m_queue_rect.x, m_queue_rect.y + m_queue_rect.h);
	SDL_RenderDrawLine(renderer, m_queue_rect.x, m_queue_rect.y, m_queue_rect.x, m_queue_rect.y + m_queue_rect.h);

	for (size_t i = 0; i < m_blocks_queue.size(); i++) {
		const auto &ptr = *m_blocks_queue[i];
		const std::string type = typeid(ptr).name();
		SDL_Rect top_block = {.x = 0, .y = 0, .w = 0, .h = 0};
		SDL_Rect bottom_block = {.x = 0, .y = 0, .w = 0, .h = 0};
		if (type == "7I_Block") {
			top_block = {m_queue_rect.x + (2 * QUEUE_BLOCK_SIZE) + (QUEUE_BLOCK_SIZE / 2), static_cast<int>(m_queue_rect.y + (i * 3 * QUEUE_BLOCK_SIZE)), 4 * QUEUE_BLOCK_SIZE, QUEUE_BLOCK_SIZE};
			SDL_Color color = {.r = 0, .g = 255, .b = 255};
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
		} else if (type == "7J_Block") {
			top_block = {m_queue_rect.x + (3 * QUEUE_BLOCK_SIZE), static_cast<int>(m_queue_rect.y + (i * 3 * QUEUE_BLOCK_SIZE)), 3 * QUEUE_BLOCK_SIZE, QUEUE_BLOCK_SIZE};
			bottom_block = {m_queue_rect.x + (5 * QUEUE_BLOCK_SIZE), static_cast<int>(m_queue_rect.y + (i * 3 * QUEUE_BLOCK_SIZE) + QUEUE_BLOCK_SIZE), QUEUE_BLOCK_SIZE, QUEUE_BLOCK_SIZE};
			SDL_Color color = {.r = 0, .g = 0, .b = 255};
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
		} else if (type == "7L_Block") {
			top_block = {m_queue_rect.x + (3 * QUEUE_BLOCK_SIZE), static_cast<int>(m_queue_rect.y + (i * 3 * QUEUE_BLOCK_SIZE)), 3 * QUEUE_BLOCK_SIZE, QUEUE_BLOCK_SIZE};
			bottom_block = {m_queue_rect.x + (3 * QUEUE_BLOCK_SIZE), static_cast<int>(m_queue_rect.y + (i * 3 * QUEUE_BLOCK_SIZE) + QUEUE_BLOCK_SIZE), QUEUE_BLOCK_SIZE, QUEUE_BLOCK_SIZE};
			SDL_Color color = {.r = 255, .g = 127, .b = 0};
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
		} else if (type == "7O_Block") {
			top_block = {m_queue_rect.x + (3 * QUEUE_BLOCK_SIZE) + (QUEUE_BLOCK_SIZE / 2), static_cast<int>(m_queue_rect.y + (i * 3 * QUEUE_BLOCK_SIZE)), 2 * QUEUE_BLOCK_SIZE, 2 * QUEUE_BLOCK_SIZE};
			SDL_Color color = {.r = 255, .g = 255, .b = 0};
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
		} else if (type == "7S_Block") {
			top_block = {m_queue_rect.x + (4 * QUEUE_BLOCK_SIZE), static_cast<int>(m_queue_rect.y + (i * 3 * QUEUE_BLOCK_SIZE)), 2 * QUEUE_BLOCK_SIZE, QUEUE_BLOCK_SIZE};
			bottom_block = {m_queue_rect.x + (3 * QUEUE_BLOCK_SIZE), static_cast<int>(m_queue_rect.y + (i * 3 * QUEUE_BLOCK_SIZE) + QUEUE_BLOCK_SIZE), 2 * QUEUE_BLOCK_SIZE, QUEUE_BLOCK_SIZE};
			SDL_Color color = {.r = 0, .g = 255, .b = 0};
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
		} else if (type == "7T_Block") {
			top_block = {m_queue_rect.x + (3 * QUEUE_BLOCK_SIZE), static_cast<int>(m_queue_rect.y + (i * 3 * QUEUE_BLOCK_SIZE)), 3 * QUEUE_BLOCK_SIZE, QUEUE_BLOCK_SIZE};
			bottom_block = {m_queue_rect.x + (4 * QUEUE_BLOCK_SIZE), static_cast<int>(m_queue_rect.y + (i * 3 * QUEUE_BLOCK_SIZE) + QUEUE_BLOCK_SIZE), QUEUE_BLOCK_SIZE, QUEUE_BLOCK_SIZE};
			SDL_Color color = {.r = 128, .g = 0, .b = 128};
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
		} else if (type == "7Z_Block") {
			top_block = {m_queue_rect.x + (4 * QUEUE_BLOCK_SIZE), static_cast<int>(m_queue_rect.y + (i * 3 * QUEUE_BLOCK_SIZE) + QUEUE_BLOCK_SIZE), 2 * QUEUE_BLOCK_SIZE, QUEUE_BLOCK_SIZE};
			bottom_block = {m_queue_rect.x + (3 * QUEUE_BLOCK_SIZE), static_cast<int>(m_queue_rect.y + (i * 3 * QUEUE_BLOCK_SIZE)), 2 * QUEUE_BLOCK_SIZE, QUEUE_BLOCK_SIZE};
			SDL_Color color = {.r = 255, .g = 0, .b = 0};
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
		}
		SDL_RenderFillRect(renderer, &top_block);
		SDL_RenderFillRect(renderer, &bottom_block);
	}
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
	for (int x = 1; x < 9; x++) {
		SDL_RenderDrawLine(renderer, m_queue_rect.x + (x * QUEUE_BLOCK_SIZE), m_queue_rect.y + 1, m_queue_rect.x + (x * QUEUE_BLOCK_SIZE), (m_queue_rect.y + m_queue_rect.h) - 1);
	}
	for (int y = 1; y < 15; y++) {
		SDL_RenderDrawLine(renderer, m_queue_rect.x + 1, m_queue_rect.y + (y * QUEUE_BLOCK_SIZE), (m_queue_rect.x + m_queue_rect.w) - 1, m_queue_rect.y + (y * QUEUE_BLOCK_SIZE));
	}
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

	render_queue(renderer);
	//print_board();
}
