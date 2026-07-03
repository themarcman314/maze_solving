#include "maze.h"
#include <stdint.h>
#include <stdlib.h>

struct Maze {
	int width;
	int height;
	uint8_t *cells;
};

static inline int get_index(const Maze *maze, int x, int y) {
	return y * maze->width + x;
}

Maze *maze_create(int width, int height) {
	Maze *maze = malloc(sizeof(Maze));
	if (!maze)
		return NULL;

	maze->width = width;
	maze->height = height;

	maze->cells = calloc(width * height, sizeof(uint8_t));
	if (!maze->cells) {
		free(maze);
		return NULL;
	}
	maze_open_path(maze, 0, 0, DIR_SOUTH);
	return maze;
}

void maze_destroy(Maze *maze) {
	if (maze) {
		free(maze->cells);
		free(maze);
	}
}

int maze_get_width(const Maze *maze) { return maze ? maze->width : 0; }
int maze_get_height(const Maze *maze) { return maze ? maze->height : 0; }

bool maze_is_valid_cell(const Maze *maze, int x, int y) {
	if (!maze)
		return false;
	return (x >= 0 && x < maze->width && y >= 0 && y < maze->height);
}

bool maze_has_path(const Maze *maze, int x, int y, Direction dir) {
	if (!maze_is_valid_cell(maze, x, y))
		return false;
	return (maze->cells[get_index(maze, x, y)] & dir) != 0;
}

void maze_open_path(Maze *maze, int x, int y, Direction dir) {
	// clear on current coords
	maze->cells[get_index(maze, x, y)] |= dir;

	// where should adjacent cell be ?
	int x_adj = x;
	int y_adj = y;
	Direction dir_adjacent_to_clear;

	switch (dir) {
	case DIR_NORTH:
		y_adj -= 1;
		dir_adjacent_to_clear = DIR_SOUTH;
		break;
	case DIR_SOUTH:
		y_adj += 1;
		dir_adjacent_to_clear = DIR_NORTH;
		break;
	case DIR_EAST:
		x_adj += 1;
		dir_adjacent_to_clear = DIR_WEST;
		break;
	case DIR_WEST:
		x_adj -= 1;
		dir_adjacent_to_clear = DIR_EAST;
		break;
	}
	// does it exist ?
	if (maze_is_valid_cell(maze, x_adj, y_adj)) {
		// clear adjacent cell with opposite dir
		maze->cells[get_index(maze, x_adj, y_adj)] |=
		    dir_adjacent_to_clear;
	}
}
