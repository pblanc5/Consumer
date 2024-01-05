#ifndef ENTITY_H_
#define ENTITY_H_

#include "raylib.h"
#include "raymath.h"

#define MAX_ENTITY_STR 100
#define INITIAL_SPEED 3
#define INITIAL_RADIUS 3

typedef struct Entity {
  Vector2 position;
  float speed;
  float radius;
  bool active;
  Color color;
} Entity;

Entity *SpawnEntity(int, int, int);
void Consume(Entity *, Entity*);
void DrawEntity(Entity *);
void DestroyEntity(Entity *);
void DebugEntity(Entity *, char *);

#endif