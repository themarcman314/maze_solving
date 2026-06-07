#include "raylib.h"

typedef struct {
	unsigned size;
	Color c;
	float space_between_rectangles;
	float rectangle_short_width;
} maze_grid;

typedef struct {
	unsigned x;
	unsigned y;
} coords;

coords center;

void maze_square_grid_draw(maze_grid const *maze_g);

void UpdateDrawFrame(void) {
	BeginDrawing();

	center.x = GetScreenWidth() / 2;
	center.y = GetScreenHeight() / 2;

	maze_grid maze_grid = {10, GRAY, 50.f, 5.f};

	ClearBackground(BLACK);
	maze_square_grid_draw(&maze_grid);

	EndDrawing();
}

void maze_square_grid_draw(maze_grid const *maze_grid) {

	float long_length =
	    maze_grid->space_between_rectangles * maze_grid->size +
	    maze_grid->rectangle_short_width;

	float offset_x = center.x - long_length / 2;
	float offset_y = center.y - long_length / 2;

	for (unsigned i = 0; i <= maze_grid->size; i++) {
		Rectangle maze_wall = {
		    .x = offset_x,
		    .y = offset_y + maze_grid->space_between_rectangles * i,
		    .width = long_length,
		    .height = maze_grid->rectangle_short_width};

		DrawRectangleRec(maze_wall, maze_grid->c);
	}
	for (unsigned i = 0; i <= maze_grid->size; i++) {
		Rectangle maze_wall = {
		    .x = offset_x + maze_grid->space_between_rectangles * i,
		    .y = offset_y,
		    .width = maze_grid->rectangle_short_width,
		    .height = long_length};

		DrawRectangleRec(maze_wall, maze_grid->c);
	}
}
