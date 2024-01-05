#include "raylib.h"
#include "game.h"

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Consumer");
  SetTraceLogLevel(LOG_INFO);
  SetTargetFPS(60);

  Game *g = SpawnGame();
  InitGame(g);

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    UpdateGame(g);
    DrawGame(g);
    EndDrawing();
  }

  DestroyGame(g);
  CloseWindow();

  return 0;
}
