#pragma once

#include <stdbool.h>
typedef enum {
	DIR_NORTH = (1 << 0), // 0b0001
	DIR_SOUTH = (1 << 1), // 0b0010
	DIR_EAST = (1 << 2),  // 0b0100
	DIR_WEST = (1 << 3)   // 0b1000
} Direction;

// opaque struct
typedef struct Maze Maze;

Maze *maze_create(int width, int height);
void maze_destroy(Maze *maze);
int maze_get_width(const Maze *maze);
int maze_get_height(const Maze *maze);
bool maze_is_valid_cell(const Maze *maze, int x, int y);
bool maze_has_path(const Maze *maze, int x, int y, Direction dir);
void maze_open_path(Maze *maze, int x, int y, Direction dir);
