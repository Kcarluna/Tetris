#pragma once
#include <SDL.h>
#include <vector>

#define BLOCK_PIECES 4

typedef enum {
	UP = 0,
	LEFT,
	DOWN,
	RIGHT,
} Dir;

class Block {
protected:
	SDL_Rect m_block[BLOCK_PIECES];
	int m_x;
	int m_y;
	int m_w;
	int m_h;

	int m_dx;
	int m_dy;
	Dir m_dir = DOWN;
	SDL_Color m_color;
public:
	Block(int x, int y, int w, int h);
	virtual ~Block() = default;
	int get_x(int index) const;
	int get_y(int index) const;

	bool in_lower_x(int x) const;
	bool in_upper_x(int x) const;
	bool in_lower_y(int y) const;
	bool in_upper_y(int y) const;

	virtual void rotate() {};
	void move(Dir dir);
	bool hit (const Block *block) const;
	void update();
	void render(SDL_Renderer *renderer) const;
};

class I_Block: public Block {
public:
	I_Block(int x, int y, int w, int h);

	void rotate();
};

class J_Block: public Block {
public:
	J_Block(int x, int y, int w, int h);

	void rotate();
};

class L_Block: public Block {
public:
	L_Block(int x, int y, int w, int h);

	void rotate();
};

class O_Block: public Block {
public:
	O_Block(int x, int y, int w, int h);
};

class S_Block: public Block {
public:
	S_Block(int x, int y, int w, int h);

	void rotate();
};

class T_Block: public Block {
public:
	T_Block(int x, int y, int w, int h);

	void rotate();
};

class Z_Block: public Block {
public:
	Z_Block(int x, int y, int w, int h);

	void rotate();
};
