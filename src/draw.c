#include "maze.h"
#include "raylib.h"

#define BACKGROUND_COLOR CLITERAL(Color){31, 31, 31, 255}
#define TEXT_COLOR WHITE
#define GRID_COLOR DARKGRAY
#define CELL_SIZE 50
#define OFFSET_X 50 // Top-left margin from screen border
#define OFFSET_Y 50

static Maze const *g_draw_maze;

void maze_draw(Maze const *maze);

void draw_init(Maze const *maze) { g_draw_maze = maze; }

void maze_draw(Maze const *maze) {
	if (!maze)
		return;

	int width = maze_get_width(maze);
	int height = maze_get_height(maze);

	int x_initial = 50;
	int y_initial = 50;
	int spacing = 50;
	float thickness = 6.0f;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int x1 = x_initial + (x * spacing);
			int y1 = y_initial + (y * spacing);
			int x2 = x1 + spacing;
			int y2 = y1 + spacing;

			if (!maze_has_path(maze, x, y, DIR_NORTH)) {
				// extending by half thickness fixes clipped
				// corners
				DrawLineEx((Vector2){(float)x1 - thickness / 2,
						     (float)y1},
					   (Vector2){(float)x2 + thickness / 2,
						     (float)y1},
					   thickness, GRID_COLOR);
			}
			if (!maze_has_path(maze, x, y, DIR_SOUTH)) {
				DrawLineEx((Vector2){(float)x1 - thickness / 2,
						     (float)y2},
					   (Vector2){(float)x2 + thickness / 2,
						     (float)y2},
					   thickness, GRID_COLOR);
			}
			if (!maze_has_path(maze, x, y, DIR_EAST)) {
				DrawLineEx((Vector2){(float)x2, (float)y1},
					   (Vector2){(float)x2, (float)y2},
					   thickness, GRID_COLOR);
			}
			if (!maze_has_path(maze, x, y, DIR_WEST)) {
				DrawLineEx((Vector2){(float)x1, (float)y1},
					   (Vector2){(float)x1, (float)y2},
					   thickness, GRID_COLOR);
			}
		}
	}
}

void UpdateDrawFrame(void) {
	BeginDrawing();
	ClearBackground(BACKGROUND_COLOR);
	maze_draw(g_draw_maze);

	EndDrawing();
}
