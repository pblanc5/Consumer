#include "entity.h"

Entity *SpawnEntity(int x, int y) {
  Entity *e = MemAlloc(sizeof(Entity));
  e->position = (Vector2){x, y};
  e->active = true;
  e->radius = GetRandomValue(INITIAL_RADIUS, INITIAL_RADIUS +2);
  e->speed = INITIAL_SPEED;

  return e;
}

void Consume(Entity *e1, Entity *e2) {
  e1->radius += e2->radius;
  e1->speed -= 0.05;
  e2->active = false;
}

void DestroyEntity(Entity *e) {
  MemFree(e);
}

void DrawEntity(Entity *e){
  if (e->active) {
    DrawCircleV(e->position, e->radius, e->color);
  }
}

void DebugEntity(Entity *e, char *msg) {
  TraceLog(LOG_DEBUG, "Entity: pos {%f, %f}; radius %f; speed %f; active %d; Message: %s",e->position.x, e->position.y, e->radius, e->speed, e->active, msg);
}