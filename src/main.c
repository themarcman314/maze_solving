#include "maze.h"
#include "raylib.h"
#include <stdio.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

int screenWidth = 800;
int screenHeight = 450;

void UpdateDrawFrame(void); // Update and Draw one frame
void draw_init(Maze const *maze);

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight,
		   "raylib [core] example - basic window");

	Maze *maze = maze_create(5, 5);
	printf("maze size:\nwidth: %u, height: %u\n", maze_get_width(maze),
	       maze_get_height(maze));

	draw_init(maze);

#if defined(PLATFORM_WEB)
	emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		UpdateDrawFrame();
	}
#endif

	maze_destroy(maze);
	CloseWindow();

	return 0;
}
