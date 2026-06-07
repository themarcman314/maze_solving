#include "raylib.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

int screenWidth = 800;
int screenHeight = 450;

void UpdateDrawFrame(void); // Update and Draw one frame

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight,
		   "raylib [core] example - basic window");

#if defined(PLATFORM_WEB)
	emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		UpdateDrawFrame();
	}
#endif

	CloseWindow();

	return 0;
}
