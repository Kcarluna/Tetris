CC=clang++
CFLAGS=-std=c++20 -Wall -Wextra -pedantic `pkg-config sdl2 --cflags`
LIBS=`pkg-config sdl2_ttf --libs`

Tetris: main.cpp Game.cpp Board.cpp Block.cpp
		$(CC) $(CFLAGS) $(LIBS) main.cpp Game.cpp Board.cpp Block.cpp -o Tetris
