#include "player.h"

void InitPlayer(Entity *e) {
  e->color = BLUE;
  TraceLog(LOG_INFO, "(InitPlayer) Player initialized");
}

void UpdatePlayer(Entity *e) {
  int srcW = GetScreenWidth();
  int srcH = GetScreenHeight();

  if (IsKeyDown(KEY_W)) {
    e->position.y = Clamp(e->position.y - e->speed, e->radius, srcH);
  }

  if (IsKeyDown(KEY_A)) {
    e->position.x = Clamp(e->position.x - e->speed, e->radius, srcW);
  }

  if (IsKeyDown(KEY_S)) {
    e->position.y = Clamp(e->position.y + e->speed, 0, srcH - e->radius);
  }

  if (IsKeyDown(KEY_D)) {
    e->position.x = Clamp(e->position.x + e->speed, 0, srcW - e->radius);
  }
}
